//******************************************************************
// Copyright (c) 2016, Carlos Rafael Gimenes das Neves
// This projected is licensed under the terms of the FreeBSD
// License. See LICENSE.txt for more details.
//
// https://github.com/carlosrafaelgn/ArduinoCountdownTimer
//******************************************************************

// If, for some reason, you are already using millis() or other
// function to control global timing, you can both save memory
// and improve performance if you define ArduinoCountdownTimerGlobalClock
// before including the library

unsigned long myGlobalTimeCounter;

#define ArduinoCountdownTimerGlobalClock myGlobalTimeCounter
#include <ArduinoCountdownTimer.h>

#define LED 13

CountdownTimer timerOn, timerOff;

void setup()
{
  pinMode(LED, OUTPUT);
  
  // Update your global time counter before starting your countdown timers
  myGlobalTimeCounter = millis();
  
  timerOn.setLimit(1000);
  timerOn.setCallback(onCallback);
  timerOn.start();
  
  timerOff.setLimit(1500);
  timerOff.setCallback(offCallback);
  timerOff.start();
  
  // reset() resets the internal timer's counter to 0
  // pause() pauses the timer (call start() to resume the timer)
  // isStarted() and isPaused() indicate timer's current state
}

void loop()
{
  // Update your global time counter before processing your countdown timers
  myGlobalTimeCounter = millis();
  
  timerOn.process();
  timerOff.process();
  
  // Do your actions here!
}

void onCallback()
{
  digitalWrite(LED, 1);
}

void offCallback()
{
  digitalWrite(LED, 0);
}
