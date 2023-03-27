#include "Pins.h"
#include "Motors.h"
#include "RF_keys.h"
#include "Timer.h"
#include "Memory.h"

Pins pins;
Motors motors;
RF_keys rf_keys;
Memory memory;

Timer OpenTimer = {0, 0, 100};
Timer CloseTimer = {0, 0, 100};

bool MUST_STOP = false;

bool isOpeningGate = false;
bool isClosingGate = false;

bool isGateClosedState = true;
bool isGateOpenState = false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("---------------------------------");
  Serial.println("Setup init.");

  /*          Gate State loading from memory        */
  String gateState = memory.ReadGateStates();

  Serial.println(String(gateState));

  isGateOpenState = memory.returnBool(String(gateState)[0]);
  isGateClosedState = memory.returnBool(String(gateState)[1]);

  Serial.println("isGateOpenState = " + String(isGateOpenState));
  Serial.println("isGateClosedState = " + String(isGateClosedState));
  /*          Gate State loading from memory        */


  pins.Setup();
  rf_keys.Setup();

  delay(500);
  Serial.println("Setup complete!");
  Serial.println("---------------------------------");


 
  pins.EnableLock();

  motors.CloseMotor_1_Off();
  motors.CloseMotor_2_Off();
  motors.OpenMotor_1_Off();
  motors.OpenMotor_2_Off();
}

void loop() {
  // put your main code here, to run repeatedly:
  
  CommandLoop();

  Inputs();

  ResetButtons();

  EmergencyStopButtonLoop();
}

void EmergencyStopButtonLoop(){
  if(motors.EmergencyStopPressed() && motors.canCallEmergencyStop()){      
    Serial.println("Emergency Stop button pressed..");
    pins.DisableLock();
    MUST_STOP = true;
    isOpeningGate = false;
    isClosingGate = false;  
    Serial.println("MUST_STOP = " + String(MUST_STOP));
    Serial.println("isOpeningGate"+ String(isOpeningGate));
    Serial.println("isClosingGate"+ String(isClosingGate));
    motors.EmergencyStop();
  }
}

void Inputs(){
    rf_keys.RF_INPUT_LOOP();

    //if A key down...
    if(rf_keys.GETKEYDOWN(rf_keys.KEY_A())){
        Serial.println("A Button down.");
        if(isGateClosedState){
          OpenGates();
        }
       //motors.OpenMotor_2_On();
    }

    //if B key down...
    if(rf_keys.GETKEYDOWN(rf_keys.KEY_B())){
        Serial.println("B Button down.");
        if(isGateOpenState){
          CloseGates();
        }
        
        //motors.OpenMotor_2_Off();
    }

    //if D Key..
    if(rf_keys.GETKEYDOWN(rf_keys.KEY_D())){ 
        Serial.println("D Button down.");
        Serial.println("Emergency Stop button from D key..");
        pins.DisableLock();
        MUST_STOP = true;
        isOpeningGate = false;
        isClosingGate = false;  
        Serial.println("MUST_STOP = " + String(MUST_STOP));
        Serial.println("isOpeningGate"+ String(isOpeningGate));
        Serial.println("isClosingGate"+ String(isClosingGate));
        motors.EmergencyStop();
    }
}

void ResetButtons(){

    //button 1

    if(motors.ResetMotor1Pressed()){  
      //button down
      motors.SetMotor1PreviousVal(true);
      motors.CloseMotor_1_On();
      Serial.println("Reset Motor1 button pressed..");
    }

    if(!motors.ResetMotor1Pressed()){  
      if(motors.GetMotor1PreviousVal()){
          //button released.
          motors.CloseMotor_1_Off();
          isGateClosedState = true;
          isGateOpenState = false;
          MUST_STOP = false;
          isOpeningGate = false;
          isClosingGate = false; 
          pins.EnableLock();
          motors.SetMotor1PreviousVal(false);  
          memory.SetGateStateClosed();
      }
    }

    //button 2

    if(motors.ResetMotor2Pressed()){  
      //button down
      motors.SetMotor2PreviousVal(true);
      motors.CloseMotor_2_On();
      Serial.println("Reset Motor2 button pressed..");
    }

    if(!motors.ResetMotor2Pressed()){  
      if(motors.GetMotor2PreviousVal()){
          //button released.
          motors.CloseMotor_2_Off();
          isGateClosedState = true;
          isGateOpenState = false; 
          MUST_STOP = false; 
          isOpeningGate = false;
          isClosingGate = false;      
          pins.EnableLock();
          motors.SetMotor2PreviousVal(false);  
          memory.SetGateStateClosed();
      }
    }

}


void OpenGates(){
  Serial.println("Open gates init.");

  unsigned int delayBetweenOpening = 8000;  
  unsigned int leftGateOpeningTime = 16600;
  unsigned int rightGateOpeningTime = 16100;
  unsigned int delayForLock = 2000;

  unsigned int fullOpenTime = delayForLock + leftGateOpeningTime + (rightGateOpeningTime - (rightGateOpeningTime - delayBetweenOpening)) + 1000;
  OpenTimer.SetCurrentTimer(fullOpenTime);
  OpenTimer.SetShowLogger(false);
  Serial.println(fullOpenTime);
  isOpeningGate = true;
  memory.SetGateStateOpen();

  while (isOpeningGate && !MUST_STOP) {
    OpenTimer.UpdateTimer();
    rf_keys.RF_INPUT_LOOP();
    EmergencyStopButtonLoop();

    if(OpenTimer.GetCurrentTimer() == (fullOpenTime - 100)){
      Serial.println(String(100) + " ms into timer, Disable Lock.");
      pins.DisableLock();
    }

    if(OpenTimer.GetCurrentTimer() == (fullOpenTime - delayForLock)){    
      Serial.println(String(delayForLock) + " ms into timer, can start Motor 1.");
      motors.OpenMotor_1_On();
    }

    if(OpenTimer.GetCurrentTimer() == (fullOpenTime - (delayBetweenOpening + delayForLock))){    
      Serial.println(String(delayBetweenOpening + delayForLock) + " ms into timer, can start Motor 2.");
      motors.OpenMotor_2_On();
    }

    if(OpenTimer.GetCurrentTimer() == (fullOpenTime - (leftGateOpeningTime + delayForLock))){    
      Serial.println(String(leftGateOpeningTime + delayForLock) + " ms into timer, can stop Motor 1.");
      motors.OpenMotor_1_Off();
    }
    
    if(OpenTimer.GetCurrentTimer() == (fullOpenTime - (rightGateOpeningTime + delayForLock + delayBetweenOpening))){    
      Serial.println(String((fullOpenTime - (rightGateOpeningTime + delayForLock + delayBetweenOpening))) + " ms into timer, can stop Motor 2.");
      motors.OpenMotor_2_Off();
    }
    
    if(OpenTimer.GetCurrentTimer() == 0 || OpenTimer.GetCurrentTimer() <= 99){
      isOpeningGate = false;

      isGateOpenState = true;
      isGateClosedState = false;
      Serial.println(String(fullOpenTime) + " ms into timer, Opening gate operation over. Timer ended..");
    }
  }
}

void CloseGates(){
  Serial.println("Close gates init.");

  unsigned int delayBetweenClosing = 20000;  
  unsigned int leftGateClosingTime = 28000;
  unsigned int rightGateClosingTime = 26000;
  unsigned int delayForLock = 2000;

  unsigned int fullCloseTime = delayForLock + leftGateClosingTime + (rightGateClosingTime - (rightGateClosingTime - delayBetweenClosing)) + 1000;
  Serial.println(fullCloseTime);
  CloseTimer.SetCurrentTimer(fullCloseTime);
  CloseTimer.SetShowLogger(false);
  //Serial.print(fullOpenTime);
  isClosingGate = true; 
  memory.SetGateStateClosed();

  Serial.println(fullCloseTime - (leftGateClosingTime + delayForLock + delayBetweenClosing) + 1400);
  while (isClosingGate && !MUST_STOP){
    CloseTimer.UpdateTimer();
    rf_keys.RF_INPUT_LOOP();
    EmergencyStopButtonLoop();

    if(CloseTimer.GetCurrentTimer() == (fullCloseTime - 100)){
      Serial.println(String(100) + " ms into timer, Enable Magnet.");
      pins.EnableLock();
    }
    if(CloseTimer.GetCurrentTimer() == (fullCloseTime - delayForLock)){    
      Serial.println(String(delayForLock) + " ms into timer, can start Motor 2.");
      motors.CloseMotor_2_On();
    }

    if(CloseTimer.GetCurrentTimer() == (fullCloseTime - (delayBetweenClosing + delayForLock))){    
      Serial.println(String(delayBetweenClosing + delayForLock) + " ms into timer, can start Motor 1.");
      motors.CloseMotor_1_On();
    }

    if(CloseTimer.GetCurrentTimer() == (fullCloseTime - (rightGateClosingTime + delayForLock))){    
      Serial.println(String(rightGateClosingTime + delayForLock) + " ms into timer, can stop Motor 2.");
      motors.CloseMotor_2_Off();
    }

    if(CloseTimer.GetCurrentTimer() == (fullCloseTime - (leftGateClosingTime + delayForLock + delayBetweenClosing) + 1400)){    
      Serial.println(String(leftGateClosingTime + delayForLock + delayBetweenClosing) + " ms into timer, can stop Motor 1.");
      motors.CloseMotor_1_Off();
    }

    if(CloseTimer.GetCurrentTimer() == 0 || CloseTimer.GetCurrentTimer() <= 99){
      isClosingGate = false;

      isGateOpenState = false;
      isGateClosedState = true;

      Serial.println(String(fullCloseTime) + " ms into timer, Closing gate operation over. Timer ended..");
    }

  }
}

String command;

void CommandLoop(){
  
    if(Serial.available()){
        command = Serial.readStringUntil('\n');
         
        Serial.println("You sent command {" + command + "}");

        if(command == "init"){            
            Serial.println("init command function");
        }
        else if(command.equals("stop")){       
                Serial.println("Emergency Stop command..");
                pins.DisableLock();
                MUST_STOP = true;
                isOpeningGate = false;
                isClosingGate = false;  
                Serial.println("MUST_STOP = " + String(MUST_STOP));
                Serial.println("isOpeningGate"+ String(isOpeningGate));
                Serial.println("isClosingGate"+ String(isClosingGate));
                motors.EmergencyStop();
        }   
        else if(command.equals("opengate")){
            Serial.println("OpenGates..");
            if(isGateClosedState){
              OpenGates();
            }
        }
        else if(command.equals("closegate")){
            Serial.println("received command  reboot");
            if(isGateOpenState){
              CloseGates();
            }
        }else if(command.equals("setStateClosed.")){
            Serial.println("received command  setStateClosed.");
            motors.CloseMotor_1_Off();
            motors.CloseMotor_2_Off();
            isGateClosedState = true;
            isGateOpenState = false;
            MUST_STOP = false;
            isOpeningGate = false;
            isClosingGate = false; 
            pins.EnableLock();
            motors.SetMotor1PreviousVal(false); 
            motors.SetMotor2PreviousVal(false);  
            memory.SetGateStateClosed();
        }

        else{
            Serial.println("Invalid command");
        }
    }
}

