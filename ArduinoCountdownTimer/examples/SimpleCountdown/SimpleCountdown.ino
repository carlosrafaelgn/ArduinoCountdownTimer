//******************************************************************
// Copyright (c) 2016, Carlos Rafael Gimenes das Neves
// This projected is licensed under the terms of the FreeBSD
// License. See LICENSE.txt for more details.
//
// https://github.com/carlosrafaelgn/ArduinoCountdownTimer
//******************************************************************

#include <ArduinoCountdownTimer.h>

#define LED 13

CountdownTimer timerOn, timerOff;

void setup()
{
  pinMode(LED, OUTPUT);
  
  timerOn.setLimit(1000);
  timerOn.start();
  
  timerOff.setLimit(1500);
  timerOff.start();
  
  // reset() resets the internal timer's counter to 0
  // pause() pauses the timer (call start() to resume the timer)
  // isStarted() and isPaused() indicate timer's current state
}

void loop()
{
  if (timerOn.process())
  {
    digitalWrite(LED, 1);
  }
  
  if (timerOff.process())
  {
    digitalWrite(LED, 0);
  }
  
  // Do your actions here!
}
