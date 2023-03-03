#include "Timer.h"


Timer::Timer(unsigned int currentTimer, unsigned long previousMillis, int interval){
  m_currentTimer = currentTimer;
  m_previousMillis = previousMillis;
  m_interval = interval;
}

Timer::UpdateTimer(){

  unsigned long currentMillis = millis();

  unsigned int currentTimer = Timer::GetCurrentTimer();

  if(millis() - Timer::GetPreviousMillis() >= Timer::GetInterval() && Timer::GetCurrentTimer() >= Timer::GetInterval()){
    Timer::SetPreviousMillis(currentMillis);
    Timer::SetCurrentTimer(currentTimer -= Timer::GetInterval());

    if(m_showLogger)
      Serial.println("CurrentTimer = " + String(Timer::GetCurrentTimer()));
  }
}