#include <LiquidCrystal.h>
#include <DynamixelSerial.h>
#include <Wire.h>
#include "srf10.h"
#include "brainband.h"

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
int value;
unsigned int brainVal;
byte dist;
srf10 srf;
brainband brain;

void setup() {
  // initialize digital pin 13 as an output.
  pinMode(13, OUTPUT); //aux led
  lcd.begin(16, 2);
  Dynamixel.begin(1000000,2);  // Init servo at 1Mbps and Pin Control 2
}

// the loop function runs over and over again forever
void loop() {
//  lcd.clear();
//  lcd.setCursor(0,0);
//  lcd.print("waiting for");
//  lcd.setCursor(0,1);
//  lcd.print("brainband");
  brainVal = brain.getAtt();
  lcd.clear();
  lcd.print(brainVal);
  delay(1000);
}
