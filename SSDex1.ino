/* Arduino UNO with SSD1306 128x64 I2C OLED display and 10K Ohm pot on A0
 * Tony Goodhew  4 June 2020
 */
//#include <SPI.h>  // Not needed if device is I2C
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int sensorPin = A0;   // select the input pin for the potentiometer
int ledPin = 13;      // select the pin for the LED
int sensorValue = 0;  // variable to store the value coming from the sensor
int counter = 0;      // Seconds counter
unsigned long int currentTime,nextTime;

void setup() {
  Serial.begin(9600);
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  // declare the ledPin as an OUTPUT:
  pinMode(ledPin, OUTPUT);
  }
  display.clearDisplay();
  display.setTextSize(1);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setCursor(0,0);             // Start at top-left corner
  display.println("SSD1306 Demo");
  display.setCursor(80,34);
  display.println("Turn Pot");
  display.setTextSize(2);             // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(80,5);  
  counter = 0;
  align3(counter);
  display.drawRect(0, 10, 70, 35, SSD1306_WHITE);  // RAW pot value box
  nextTime = millis() + 1000;  // 1 second in the future
  display.println(counter);
  display.display();
}
// Functions for right alignment of integers
int align2(int q){  // Space in 100s and 10s
  if (q < 100) {display.print(" ");}
    if (q < 10) {display.print(" ");}    
}
int align3(int q){  // Space in 1000s
  if (q < 1000) {display.print(" ");}
  align2(q);
}
// ++++++++++++Main Loop ++++++++++++++
// 1 second timer
void loop() {                   
  currentTime = millis();
  if (currentTime >= nextTime) {  // Then update one   second timer
    display.setTextSize(2);             // Draw 2X-scale text
    display.setTextColor(SSD1306_BLACK);
    display.setCursor(80,5);
    align3(counter);          // Right align value
    display.println(counter); // Overwrite current value in black - rub out
    counter = counter + 1;
    if (counter >= 10000){counter = 0;} // Reset befor overflows space
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(80,5);
    align3(counter);
    display.println(counter);  // Write new value in white
    nextTime = nextTime + 1000;
  }
  // Read pot and display values
  sensorValue = analogRead(sensorPin); // read the value from the sensor
  int perCent = float(sensorValue * 100.0/1018);
  display.drawLine(0,47,0,62, SSD1306_WHITE);
  display.fillRect(1, 50, perCent, 10, SSD1306_WHITE);
  display.setTextSize(1);               // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);  // Draw white text
  display.setCursor(102,50);
  align2(perCent);    
  display.print(perCent);
  display.println("%");
  display.fillRect(1, 11, 68, 33, SSD1306_BLACK); // Clear box
  display.setCursor(10,20);
  display.setTextSize(2);
  align3(sensorValue);  
  display.println(sensorValue);
  display.setTextSize(1);
  display.display();
  delay(100);
  display.fillRect(1, 50, perCent, 10, SSD1306_BLACK);
  display.setTextColor(SSD1306_BLACK); 
  display.setCursor(102,50);
  align2(perCent);     
  display.print(perCent);
  display.println("%");
}
