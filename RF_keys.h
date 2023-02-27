#ifndef RF_KEYS_H
#define RF_KEYS_H
#include <Arduino.h>

class RF_keys{
  private:
    int a_previousVal = 0;
    int b_previousVal = 0;
    int c_previousVal = 0;
    int d_previousVal = 0;

    bool a_key_down = false;
    bool b_key_down = false;
    bool c_key_down = false;
    bool d_key_down = false;

  public: 
    #define A_KEY 5
    #define B_KEY 4
    #define C_KEY 2
    #define D_KEY 3
    
    RF_keys::Setup();
    RF_keys::RF_INPUT_LOOP();

    bool GETKEYDOWN(int KEY){
      switch(KEY){
        case 5:
          return a_key_down;
        case 4:
          return b_key_down;
        case 2:
          return c_key_down;
        case 3:
          return d_key_down;
        default:
          return 0;
      }
    }

    int KEY_A(){ return A_KEY; }
    int KEY_B(){ return B_KEY; }
    int KEY_C(){ return C_KEY; }
    int KEY_D(){ return D_KEY; }
};


#endif