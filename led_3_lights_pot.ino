// Lab 7: Knob Meter

const int redLedPin = 7;
const int yellowLedPin = 8;
const int greenLedPin = 9;
const int knobPin = A0;

void setup() {
  pinMode(greenLedPin, OUTPUT);
  pinMode(yellowLedPin, OUTPUT);
  pinMode(redLedPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int green = LOW;
  int yellow = LOW;
  int red = LOW;
  int sensorValue = analogRead(knobPin);
  Serial.println(sensorValue);

  if (sensorValue > 100) {
    green = HIGH;
  }
  if (sensorValue > 400) {
    yellow = HIGH;
  }
  if (sensorValue > 800) {
    red = HIGH;
  }
  
  digitalWrite(greenLedPin, green);
  digitalWrite(yellowLedPin, yellow);
  digitalWrite(redLedPin, red);
}
