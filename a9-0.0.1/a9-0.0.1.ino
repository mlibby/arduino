#include <Stepper.h>

const int buttonPin = 30;   
const int ledPin = 28; 

int ledState = HIGH;
int buttonState;
int lastButtonState = LOW;

long lastDebounceTime = 0;
long debounceDelay = 50;

const int stepsPerRevolution = 2048;
int stepperRpms = 15;
int stepSize = 1;
Stepper leftStepper(stepsPerRevolution, 23, 27, 25, 29);
Stepper rightStepper(stepsPerRevolution, 47, 51, 49, 53);

void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, ledState);

  leftStepper.setSpeed(stepperRpms);
  rightStepper.setSpeed(stepperRpms);
}

void checkButton() {
  int reading = digitalRead(buttonPin);
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;

      if (buttonState == HIGH) {
        ledState = !ledState;
      }
    }
  }

  digitalWrite(ledPin, ledState);
  lastButtonState = reading;
}

int driveMode = 0;
int driveStepTarget = 2048 * 5;
int driveStep = 0;

void drive() {
  int leftStep = 0;
  int rightStep = 0;

  driveStep++;
  if(0 == driveMode) { // straight
    leftStep = -stepSize;
    rightStep = stepSize;
    if(driveStep == driveStepTarget) {
      driveMode = 1;
      driveStepTarget = 2048 / 4;
      driveStep = 0;
    }
  }
  
  if (1 == driveMode) { // turn left
    leftStep = stepSize;
    rightStep = stepSize * 2;    
    if(driveStep == driveStepTarget) {
      driveMode = 0;
      driveStepTarget = 2048 * 5;
      driveStep = 0;
    }
  }
  
  leftStepper.step(leftStep);
  rightStepper.step(rightStep);
}

void loop() {
  checkButton();
  if(HIGH == ledState) {
    drive();
  }
}

