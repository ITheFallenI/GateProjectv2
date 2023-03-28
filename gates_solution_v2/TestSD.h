#ifndef TESTSD_H
#define TESTSD_H

#include <Arduino.h>
#include <SD.h>
#include <SPI.h>

class TestSD{
  private:
    int pinCS = 53;

  public:
    void TestMySD(){      
      pinMode(pinCS, OUTPUT);

      if(SD.begin()){
        Serial.println("SD card ready to use.");
      }else{
        Serial.println("SD card failed...");
        return;
      }
    }
};

#endif