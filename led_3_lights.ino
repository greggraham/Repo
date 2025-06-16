// Lab 6: Traffic Light

#include "Button2.h"

const int redLedPin = 7;
const int yellowLedPin = 8;
const int greenLedPin = 9;
const int switchPin = 2;
int state = 0;
Button2 button;

void tapped() {
  if (state == 0) {
    state = 1;
  } else if (state == 1) {
    state = 2;
  } else if (state == 2) {
    state = 0;
  }
}

void setup() {
  pinMode(greenLedPin, OUTPUT);
  pinMode(yellowLedPin, OUTPUT);
  pinMode(redLedPin, OUTPUT);
  button.begin(switchPin);
  button.setTapHandler(tapped);
}

void loop() {
  button.loop(); // MUST call the loop() function first

  if (state == 0) {
    digitalWrite(greenLedPin, HIGH);
    digitalWrite(yellowLedPin, LOW);
    digitalWrite(redLedPin, LOW);
  } else if (state == 1) {
    digitalWrite(greenLedPin, LOW);
    digitalWrite(yellowLedPin, HIGH);
    digitalWrite(redLedPin, LOW);
  } else if (state == 2) {
    digitalWrite(greenLedPin, LOW);
    digitalWrite(yellowLedPin, LOW);
    digitalWrite(redLedPin, HIGH);
  }
}
