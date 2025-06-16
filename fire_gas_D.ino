
#include <Wire.h>
#include <U8g2lib.h>

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0);
// the itemsdefine 
const int lm35Pin = A0; //analog
const int mq6Pin  = A1; // analog 

const int buzzerPin = 8;  //digital
const int ledGreenPin = 7;
const int ledRedPin = 2;

// the limits to made beeb noise 
const float tempThreshold = 35.0;
const float gasVoltThreshold = 1.5;

// for o/p pins in Arduino 
void setup() {
  u8g2.begin();

  pinMode(buzzerPin, OUTPUT);
  pinMode(ledGreenPin, OUTPUT);
  pinMode(ledRedPin, OUTPUT);

  digitalWrite(buzzerPin, LOW);
  digitalWrite(ledGreenPin, HIGH);
  digitalWrite(ledRedPin, LOW);
}
// loop 
void loop() {
  int tempRaw = analogRead(lm35Pin);
  int gasRaw  = analogRead(mq6Pin);

  float temperature = (tempRaw / 1023.0) * 3.3 * 100.0;  // Equation of temp. read 
  float gasVoltage  = (gasRaw / 1023.0) * 5.0;           // Equation of gas read
 //boolean
  bool danger = (temperature > tempThreshold || gasVoltage > gasVoltThreshold);
  digitalWrite(buzzerPin, danger);
  digitalWrite(ledRedPin, danger);
  digitalWrite(ledGreenPin, !danger);

  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_ncenB08_tr);

  u8g2.setCursor(0, 25);
  u8g2.print("Temp: ");
  u8g2.print(temperature, 1);
  u8g2.print(" C");

  u8g2.setCursor(0, 45);
  u8g2.print("Gas: ");
  u8g2.print(gasVoltage, 2);
  u8g2.print(" V");

  u8g2.sendBuffer();
  delay(300);
}
