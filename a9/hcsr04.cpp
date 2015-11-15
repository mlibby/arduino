#include "hcsr04.h"

const int triggerPin = 8;
const int echoPin = 9;
const float HCSR04::usPerCm = 58.3;
const int HCSR04::maxDistanceCm = 400;
const int HCSR04::maxWaitUs = HCSR04::usPerCm * HCSR04::maxDistanceCm;

HCSR04::HCSR04(uint8_t trigger_pin, uint8_t echo_pin, uint8_t reset_pin) {
  pinMode(triggerPin, OUTPUT);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
}

float HCSR04::getDistanceCm() {
  startPing();
  long startUs = micros();
  long wait = pulseIn(echoPin, HIGH, HCSR04::maxWaitUs);

  return wait / HCSR04::usPerCm;
}

void HCSR04::startPing() {
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
}

