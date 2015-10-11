int const latchPin = 10;
int const clockPin = 9;
int const dataPin = 11;

int const hoursRow = 64 + 32;
int const minRow = 128 + 32;
int const secRow = 128 + 64;

void setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, 0);
  shiftOut(dataPin, clockPin, LSBFIRST, 0);
  digitalWrite(latchPin, HIGH);
}

void loop() {
  writeHours();
  writeMinutes();
  writeSeconds();
}

void writeHours()
{
  
  writeOut(B10000000, hoursRow);
  writeOut(B00000100, hoursRow);
  writeOut(B00000000, hoursRow + 4);
  //writeOut(B00000000, B01100010);
}

void writeMinutes()
{
  writeOut(0, minRow + 16);
  writeOut(0, minRow + 8);
  writeOut(0, minRow + 4);
  writeOut(0, minRow + 2);
}

void writeSeconds()
{
  writeOut(0, secRow + 16);
  writeOut(0, secRow + 8);
  writeOut(0, secRow + 4);
  writeOut(0, secRow + 2);
}

void writeOut(int gb, int rc)
{
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, gb);
  shiftOut(dataPin, clockPin, LSBFIRST, rc);
  digitalWrite(latchPin, HIGH);
}  

