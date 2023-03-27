#ifndef PINS_H
#define PINS_H
#include <Arduino.h>

class Pins{
  #define LOCK_PIN 6
  #define STOP_BUTTON 7
  
  #define RESET_NOTOR2_BUTTON 47
  #define RESET_NOTOR1_BUTTON 10
  
  #define MOTOR_2_MAINS 31 //13  //mains power to motor #1
  #define MOTOR_2_UP 29     //mains to motor #1 up
  #define MOTOR_2_DOWN 34   //mains to motor #1 up
  
  #define MOTOR_1_MAINS 25  //mains power to motor #1
  #define MOTOR_1_UP 23      //mains to motor #1 up
  #define MOTOR_1_DOWN 27    //mains to motor #1 up

  public:
    void Setup(){
      //lock
      pinMode(LOCK_PIN, OUTPUT);
      digitalWrite(LOCK_PIN, HIGH);

      //reset buttons
      pinMode(RESET_NOTOR1_BUTTON, INPUT_PULLUP);
      pinMode(RESET_NOTOR2_BUTTON, INPUT_PULLUP);

      //motor #1
      pinMode(MOTOR_1_MAINS, OUTPUT);
      pinMode(MOTOR_1_UP, OUTPUT);
      pinMode(MOTOR_1_DOWN, OUTPUT);
    
    
      digitalWrite(MOTOR_1_MAINS, HIGH);
      digitalWrite(MOTOR_1_UP, HIGH);
      digitalWrite(MOTOR_1_DOWN, HIGH);
    
      //motor #2
      pinMode(MOTOR_2_MAINS, OUTPUT);
      pinMode(MOTOR_2_UP, OUTPUT);
      pinMode(MOTOR_2_DOWN, OUTPUT);
    
    
      digitalWrite(MOTOR_2_MAINS, HIGH);
      digitalWrite(MOTOR_2_UP, HIGH);
      digitalWrite(MOTOR_2_DOWN, HIGH);

      //stop button
      pinMode(STOP_BUTTON, INPUT_PULLUP);
      Serial.println("Pins setup complete!");
    }

    void EnableLock(){
      digitalWrite(LOCK_PIN, LOW);  //open lock      
    }
    void DisableLock(){
      digitalWrite(LOCK_PIN, HIGH); // close lock
    }
};

#endif