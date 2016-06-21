//
// CountdownTimer is distributed under the FreeBSD License
//
// Copyright (c) 2016, Carlos Rafael Gimenes das Neves
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// 1. Redistributions of source code must retain the above copyright notice, this
//    list of conditions and the following disclaimer.
// 2. Redistributions in binary form must reproduce the above copyright notice,
//    this list of conditions and the following disclaimer in the documentation
//    and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
// ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// The views and conclusions contained in the software and documentation are those
// of the authors and should not be interpreted as representing official policies,
// either expressed or implied, of the FreeBSD Project.
//
// https://github.com/carlosrafaelgn/ArduinoCountdownTimer
//
#ifndef ArduinoCountdownTimer_h
#define ArduinoCountdownTimer_h

#include <Arduino.h>
#include <inttypes.h>

typedef void (*CountdownTimerCallback)();

class CountdownTimer {
private:
  uint32_t counter, limit, lastTime;
  CountdownTimerCallback callback;
  uint8_t running;
public:
  inline CountdownTimer() {
    counter = 0;
    callback = 0;
    running = false;
  }
  inline void setLimit(uint32_t limit) {
    this->limit = limit;
  }
  inline void setCallback(CountdownTimerCallback callback) {
    this->callback = callback;
  }
  inline void reset() {
    counter = 0;
  }
  inline void start() {
    running = true;
#ifdef ArduinoCountdownTimerGlobalClock
    lastTime = ArduinoCountdownTimerGlobalClock;
#else
    lastTime = millis();
#endif
  }
  inline uint8_t isStarted() {
    return running;
  }
  inline void pause() {
    running = false;
  }
  inline uint8_t isPaused() {
    return !running;
  }
  bool process() {
    if (!running) return false;
#ifdef ArduinoCountdownTimerGlobalClock
    counter += (ArduinoCountdownTimerGlobalClock - lastTime);
    lastTime = ArduinoCountdownTimerGlobalClock;
#else
    uint32_t now = millis();
    counter += (now - lastTime);
    lastTime = now;
#endif
    if (counter >= limit) {
      do {
        counter -= limit;
      } while (counter >= limit);
      if (callback) callback();
      return true;
    }
    return false;
  }
};

#endif
