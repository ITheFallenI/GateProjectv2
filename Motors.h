#ifndef MOTORS_H
#define MOTORS_H
#include <Arduino.h>

class Motors{
  bool MOTOR_1_MAINS_BOOL;
  bool MOTOR_1_UP_BOOL;
  bool MOTOR_1_DOWN_BOOL;

  bool MOTOR_2_MAINS_BOOL;
  bool MOTOR_2_UP_BOOL;
  bool MOTOR_2_DOWN_BOOL;


  #define STOP_BUTTON 7
  #define RESET_NOTOR1_BUTTON 38
  #define RESET_NOTOR2_BUTTON 34

  private:
    Motors::Toggles(bool toggleBool, int pinNumber);
    bool resetMotor1_previousVal = false;
    bool resetMotor2_previousVal = false;
  public:
    Motors::Motors();

    Motors::OpenMotor_1_On();
    Motors::OpenMotor_1_Off();    
    Motors::OpenMotor_2_On();
    Motors::OpenMotor_2_Off();

    Motors::CloseMotor_1_On();
    Motors::CloseMotor_1_Off();    
    Motors::CloseMotor_2_On();
    Motors::CloseMotor_2_Off();

    Motors::EmergencyStop();

    bool EmergencyStopPressed(){ int buttonValue = digitalRead(STOP_BUTTON); if (buttonValue == LOW){ return true; }else { return false; } }
    bool canCallEmergencyStop(){ return MOTOR_1_UP_BOOL == true || MOTOR_1_DOWN_BOOL == true || MOTOR_2_UP_BOOL == true || MOTOR_2_DOWN_BOOL == true; }

    bool ResetMotor1Pressed(){ int buttonValue = digitalRead(RESET_NOTOR1_BUTTON); if (buttonValue == HIGH){ return true; }else { return false; } }
    bool ResetMotor2Pressed(){ int buttonValue = digitalRead(RESET_NOTOR2_BUTTON); if (buttonValue == HIGH){ return true; }else { return false; } }


    void SetMotor1PreviousVal(bool value){ resetMotor1_previousVal = value; }
    bool GetMotor1PreviousVal(){ return resetMotor1_previousVal; }

    void SetMotor2PreviousVal(bool value){ resetMotor2_previousVal = value; }
    bool GetMotor2PreviousVal(){ return resetMotor2_previousVal; }

};

#endif