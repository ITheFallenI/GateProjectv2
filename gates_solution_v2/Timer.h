#ifndef TIMER_H
#define TIMER_H
#include <Arduino.h>

class Timer{
  unsigned int m_MaxCurrentTimer;
  unsigned int m_currentTimer;
  unsigned long m_previousMillis;
  int m_interval;
  bool m_showLogger;

  public:
    Timer(unsigned int currentTimer, unsigned long previousMillis, int interval);
    Timer::UpdateTimer();
    
    unsigned int GetCurrentTimer(){ return m_currentTimer; }
    unsigned long GetPreviousMillis(){ return m_previousMillis; }
    int GetInterval(){ return m_interval; }
    unsigned int GetMaxCurrentTimer(){ return m_MaxCurrentTimer; }

    void SetPreviousMillis(unsigned long millis){ m_previousMillis = millis; }
    void SetCurrentTimer(unsigned int currentTimer){ m_currentTimer = currentTimer; m_MaxCurrentTimer = currentTimer; }
    void ResetTimer(){ m_currentTimer = m_MaxCurrentTimer; }
    void SetShowLogger(bool show){ m_showLogger = show; }
};

#endif