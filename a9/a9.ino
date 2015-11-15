#include <math.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include "hcsr04.h";

Adafruit_PCD8544 *display;
HCSR04 *sonar;
float distanceCm;

void setup() {
  setupDisplay();
  sonar = new HCSR04(8, 9, 0);
}

void setupDisplay() {
  display = new Adafruit_PCD8544(7, 6, 5, 4, 3);
  display->begin();
  display->setContrast(30);
  display->setTextSize(1);
  display->setTextColor(BLACK);
}

void loop() {
  distanceCm = sonar->getDistanceCm();
  loopDisplay();
  delay(500);
}

void loopDisplay() {
  display->clearDisplay();
  display->setCursor((int)floor(distanceCm) % 50,18);
  display->print("w00f!");
  display->display();
}

