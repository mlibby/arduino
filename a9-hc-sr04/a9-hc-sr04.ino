#include "hcsr04.h";

HCSR04 *sonar;

void setup() {
  Serial.begin(9600);
  sonar = new HCSR04(8, 9, 0);
}

void loop() {
  Serial.println(sonar->getDistanceCm());
  delay(500);
}

