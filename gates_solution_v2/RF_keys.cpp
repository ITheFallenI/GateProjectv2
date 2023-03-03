#include "RF_keys.h"

RF_keys::Setup(){

  a_key_down = false;
  b_key_down = false;
  c_key_down = false;
  d_key_down = false;

  if(a_previousVal == 1)
    a_previousVal = 0;
 
  if(b_previousVal == 1)
    b_previousVal = 0;
 
  if(c_previousVal == 1)
    c_previousVal = 0;
 
  if(d_previousVal == 1)
    d_previousVal = 0;

  
  Serial.println("RF keys setup complete!");
}

RF_keys::RF_INPUT_LOOP() {
  if (a_previousVal == 0 && digitalRead(A_KEY) == 1) {
    a_previousVal = 1;
    a_key_down = true;
  } else if (a_previousVal == 1 && digitalRead(A_KEY) == 0) {
    a_key_down = false;
    a_previousVal = 0;
  }
 
  if (b_previousVal == 0 && digitalRead(B_KEY) == 1) {
    b_previousVal = 1;
    b_key_down = true;
  } else if (b_previousVal == 1 && digitalRead(B_KEY) == 0) {
    b_key_down = false;
    b_previousVal = 0;
  }
 
  if (c_previousVal == 0 && digitalRead(C_KEY) == 1) {
    c_previousVal = 1;
    c_key_down = true;
  } else if (c_previousVal == 1 && digitalRead(C_KEY) == 0) {
    c_previousVal = 0;
    c_key_down = false;
  }
  if (d_previousVal == 0 && digitalRead(D_KEY) == 1) {
    d_previousVal = 1;
    d_key_down = true;
  } else if (d_previousVal == 1 && digitalRead(D_KEY) == 0) {
    d_previousVal = 0;
    d_key_down = false;
  }
}
