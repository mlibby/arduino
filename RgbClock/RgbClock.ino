#include <SoftwareSerial.h>
#include "InputMode.h"

int const latchPin = 10;
int const clockPin = 9;
int const dataPin = 11;

const int blueRxPin = 2;
const int blueTxPin = 3;
SoftwareSerial bluetooth(blueTxPin, blueRxPin);

int const rowMask[] = {
    B01100000,
    B10100000,
    B11000000
};
int blueGreen;
int groundRed;

int currentTimeHours = 15;
int currentTimeMinutes = 59;
int currentTimeSeconds = 33;
int changeTimeHours;
int changeTimeMinutes;

InputMode inputMode = noInput;
char inputChar;
int inputNumber = 0;

void setup() {
    pinMode(latchPin, OUTPUT);
    pinMode(clockPin, OUTPUT);
    pinMode(dataPin, OUTPUT);
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, LSBFIRST, 0);
    shiftOut(dataPin, clockPin, LSBFIRST, 0);
    digitalWrite(latchPin, HIGH);
    bluetooth.begin(9600);
}

void loop() {
  if( bluetooth.available()) {
    inputChar = bluetooth.read();
    handleInput();
  }

  writeTime(currentTimeHours, 0);
  writeTime(currentTimeMinutes, 1);
  writeTime(currentTimeSeconds, 2);
}

void changeInputMode(InputMode newMode) {
  inputMode = newMode;
  inputNumber = 0;
}

void handleInput() {
  if(inputMode == noInput) {
    if(inputChar == 't') {
      changeInputMode(setTimeHours);
    }
  }
  else {
    switch(inputMode) {
      case setTimeHours:
        if(inputChar >= '0' && inputChar <= '9') {
          inputNumber = (inputNumber * 10) + (inputChar - '0') ;    
        } else if (inputChar == ':') {
          changeTimeHours = inputNumber;
          changeInputMode(setTimeMinutes);
        } else {
          changeInputMode(noInput);
        }
      break;
      case setTimeMinutes:
        if(inputChar >= '0' && inputChar <= '9') {
          inputNumber = (inputNumber * 10) + (inputChar - '0');      
        } else if (inputChar == ':') {
          changeTimeMinutes = inputNumber;
          changeInputMode(setTimeSeconds);
        } else {
          changeInputMode(noInput);
        }
      break;
      case setTimeSeconds:
        if(inputChar >= '0' && inputChar <= '9') {
          inputNumber = (inputNumber * 10) + (inputChar - '0');      
        } else if (inputChar == '.') {
          currentTimeHours = changeTimeHours;
          currentTimeMinutes = changeTimeMinutes;
          currentTimeSeconds = inputNumber;
          changeInputMode(noInput);
        } else {
          changeInputMode(noInput);
        }
      break;
    }
  }
}

void addValueToColorMask(int col, int val) {
  int led = 0;

  switch(val) {
    case 0:
      led = 1 << (4 - col);
      groundRed |= led;
      break;
    case 1:
      led = 1 << (3 - col);
      blueGreen |= led;
      break;
    case 2:
      led = 1 << (7 - col);
      blueGreen |= led;
      break;
  }
}

void setLeds(int row, int twoSevens, int nines, int threes, int ones) {
  blueGreen = 0;
  groundRed = rowMask[row];

  addValueToColorMask(0, twoSevens);
  addValueToColorMask(1, nines);
  addValueToColorMask(2, threes);
  addValueToColorMask(3, ones);
  
  writeOut(blueGreen, groundRed);
}

void writeTime(int timeValue, int row)
{
    int twoSevens = timeValue / 27;
    int nines = (timeValue % 27) / 9;
    int threes = ((timeValue % 27) % 9) / 3;
    int ones = ((timeValue % 27) % 9) % 3;

    if(row == 0) {
      twoSevens = nines;
      nines = threes;
      threes = ones;
      ones = 0;
    }
    
    setLeds(row, twoSevens, nines, threes, ones);
}

void writeOut(int gb, int rc)
{
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, LSBFIRST, gb);
    shiftOut(dataPin, clockPin, LSBFIRST, rc);
    digitalWrite(latchPin, HIGH);
//    delay(1);
//    digitalWrite(latchPin, LOW);
//    shiftOut(dataPin, clockPin, LSBFIRST, 0);
//    shiftOut(dataPin, clockPin, LSBFIRST, B11100000);
//    digitalWrite(latchPin, HIGH);
//    delay(2);
}  

