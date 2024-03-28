#include "ramping.h"
#include "GLOBAL.h"
#include "Arduino.h"

Ramping::Ramping():m_currentSpd(MIN_SPEED), m_desiredSpd(MIN_SPEED){}
void Ramping::setCurrentSpd(byte spd)      {  m_currentSpd = spd; }
void Ramping::setDesiredSpd(byte spd)      {  m_desiredSpd = spd; }
byte Ramping::getCurrentSpd() const {  return m_currentSpd; }
byte Ramping::getDesiredSpd() const {  return m_desiredSpd; }

bool Ramping::isTimeToChangeSpd(long timeMillis){
  if(timeMillis - m_time >= m_maxWaitTime){
    m_time = timeMillis;
    return true;
  }
  else{
    return false;
  }
}

void Ramping::spdUp(byte amount){
  if(m_currentSpd + amount >= MAX_SPEED)
    m_currentSpd = MAX_SPEED;
  else
    m_currentSpd += amount;
}

void Ramping::spdDown(byte amount){
  if(m_currentSpd - amount <= MIN_SPEED)
    m_currentSpd = MIN_SPEED;
  else
    m_currentSpd -= amount; 
}

byte Linear::newSpd(int throttle, long timeMillis){
  //setDesiredSpd(map(throttle, 0, MAX_THROTTLE, MIN_SPEED, MAX_SPEED));
  setDesiredSpd(throttle);
  
  if(isTimeToChangeSpd(timeMillis)){
    if(abs(getCurrentSpd()-getDesiredSpd()) > RAMP_SPEED){
      if(getCurrentSpd() < getDesiredSpd())
        spdUp(6*RAMP_SPEED);
      else
        spdDown(10*RAMP_SPEED); 
    }
  }
  return getCurrentSpd();
}
