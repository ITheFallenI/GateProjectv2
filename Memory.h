#ifndef MEMORY_H
#define MEMORY_H
#include <Arduino.h>
#include <EEPROM.h>

class Memory{
  private:
    int MemoryStorageAddress = 2;

  public:
    void SetGateStateClosed(){ 
      EEPROM.write(MemoryStorageAddress, 21); 
    }

    void SetGateStateOpen(){ 
      EEPROM.write(MemoryStorageAddress, 12); 
    }

    String ReadGateStates(){
        return String(EEPROM.read(MemoryStorageAddress));
    }

    bool returnBool(char state){
      switch(state){
        case '2':
          return false;
        case '1': 
          return true;
        default:
          return false;
      }
    }
};
#endif