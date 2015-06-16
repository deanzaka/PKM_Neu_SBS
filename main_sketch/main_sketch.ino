#include <LiquidCrystal.h>
#include <DynamixelSerial.h>
#include <Wire.h>
#include "srf10.h"

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
int value;
byte dist;
srf10 srf;

void setup() {
  // initialize digital pin 13 as an output.
  pinMode(13, OUTPUT); //aux led
  lcd.begin(16, 2);
  Dynamixel.begin(1000000,2);  // Inicialize the servo at 1Mbps and Pin Control 2
}

// the loop function runs over and over again forever
void loop() {
  lcd.print("Servo:");
  
  lcd.setCursor(7, 0);
  value = random(0,4096);
  Dynamixel.move(13,value);  // Move the Servo radomly from 200 to 800
  lcd.print(value);
  
  lcd.setCursor(12, 0);
  value = random(0,4096);
  Dynamixel.move(14,value);  // Move the Servo radomly from 200 to 800
  lcd.print(value);
  
  lcd.setCursor(0,1);
  lcd.print("SRF:");
  
  dist = srf.ping(113);
  lcd.setCursor(5,1);
  lcd.print(dist);
  
  dist = srf.ping(112);
  lcd.setCursor(9,1);
  lcd.print(dist);
  
  delay(1000);
  lcd.clear();
}
