#include "Motors.h"
#include "Pins.h"

Motors::Motors(){
  Motors::OpenMotor_1_Off();
  Motors::CloseMotor_1_Off();
  Motors::OpenMotor_2_Off();
  Motors::CloseMotor_2_Off();

  MOTOR_1_MAINS_BOOL = false;
  MOTOR_1_UP_BOOL = false;
  MOTOR_1_DOWN_BOOL = false;

  MOTOR_2_MAINS_BOOL = false;
  MOTOR_2_UP_BOOL = false;
  MOTOR_2_DOWN_BOOL = false;
}

Motors::OpenMotor_1_On() {
  MOTOR_1_MAINS_BOOL = true;
  Toggles(MOTOR_1_MAINS_BOOL, MOTOR_1_MAINS);
 
  MOTOR_1_UP_BOOL = true;
  Toggles(MOTOR_1_UP_BOOL, MOTOR_1_UP);
}
 
Motors::OpenMotor_1_Off() {
  MOTOR_1_MAINS_BOOL = false;
  Toggles(MOTOR_1_MAINS_BOOL, MOTOR_1_MAINS);
 
  MOTOR_1_UP_BOOL = false;
  Toggles(MOTOR_1_UP_BOOL, MOTOR_1_UP);
}
 
Motors::OpenMotor_2_On() {
  MOTOR_2_MAINS_BOOL = true;
  Toggles(MOTOR_2_MAINS_BOOL, MOTOR_2_MAINS);
 
  MOTOR_2_UP_BOOL = true;
  Toggles(MOTOR_2_UP_BOOL, MOTOR_2_UP);
}
 
Motors::OpenMotor_2_Off() {
  MOTOR_2_MAINS_BOOL = false;
  Toggles(MOTOR_2_MAINS_BOOL, MOTOR_2_MAINS);
 
  MOTOR_2_UP_BOOL = false;
  Toggles(MOTOR_2_UP_BOOL, MOTOR_2_UP);
}
 
Motors::CloseMotor_1_On() {
  MOTOR_1_MAINS_BOOL = true;
  Toggles(MOTOR_1_MAINS_BOOL, MOTOR_1_MAINS);
 
  MOTOR_1_DOWN_BOOL = true;
  Toggles(MOTOR_1_DOWN_BOOL, MOTOR_1_DOWN);
}
 
Motors::CloseMotor_1_Off() {
  MOTOR_1_MAINS_BOOL = false;
  Toggles(MOTOR_1_MAINS_BOOL, MOTOR_1_MAINS);
 
  MOTOR_1_DOWN_BOOL = false;
  Toggles(MOTOR_1_DOWN_BOOL, MOTOR_1_DOWN);
}
 
Motors::CloseMotor_2_On() {
  MOTOR_2_MAINS_BOOL = true;
  Toggles(MOTOR_2_MAINS_BOOL, MOTOR_2_MAINS);
 
  MOTOR_2_DOWN_BOOL = true;
  Toggles(MOTOR_2_DOWN_BOOL, MOTOR_2_DOWN);
}
 
Motors::CloseMotor_2_Off() {
  MOTOR_2_MAINS_BOOL = false;
  Toggles(MOTOR_2_MAINS_BOOL, MOTOR_2_MAINS);
 
  MOTOR_2_DOWN_BOOL = false;
  Toggles(MOTOR_2_DOWN_BOOL, MOTOR_2_DOWN);
}

Motors::Toggles(bool toggleBool, int pinNumber) {
  //true bool in = high = turn off LED = turn of relay power
  if (toggleBool) {
    //true
    digitalWrite(pinNumber, LOW);
  }
  if (!toggleBool) {
    //false
    digitalWrite(pinNumber, HIGH);
  }
}

Motors::EmergencyStop(){
  Serial.println(String(MOTOR_1_UP_BOOL) + String(MOTOR_1_DOWN_BOOL) + String(MOTOR_2_UP_BOOL) + String(MOTOR_2_DOWN_BOOL));

  if(MOTOR_1_UP_BOOL == true || MOTOR_1_DOWN_BOOL == true || MOTOR_2_UP_BOOL == true || MOTOR_2_DOWN_BOOL == true){ 
    Serial.println("Called emergency stop...");
    Motors::OpenMotor_1_Off();
    Motors::CloseMotor_1_Off();
 
    Motors::OpenMotor_2_Off();
    Motors::CloseMotor_2_Off();
  }else{
    Serial.println("No motors on no point to emergency stop...");
  }
  
}
