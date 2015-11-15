// ---------------------------------------------------------------------------
// HC-SR04 Library
// Copyright 2015, Michael C. Libby
//
// This is a library designed to support ONLY the HC-SR04 ultrasonic distance
// sensors -- specifically the ones with a faulty firmware that  causes the 
// echo pin to "lock" whenever a ping fails to return.
//
// This library allows the option of using a transister to cycle the power to
// the sensor to reset the echo pin.
// ---------------------------------------------------------------------------

#ifndef NewPing_h
#define NewPing_h

#include <Arduino.h>

class HCSR04 {
  public:
    HCSR04(uint8_t trigger_pin, uint8_t echo_pin, uint8_t reset_pin);
    
    float getDistanceCm();

  private:
    static const float usPerCm;
    static const int maxDistanceCm;
    static const int maxWaitUs;
    
    void startPing();
};

#endif

