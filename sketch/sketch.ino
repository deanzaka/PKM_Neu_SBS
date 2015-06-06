#include <LiquidCrystal.h>
#include <DynamixelSerial.h>

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
int value;

void setup() {
  // initialize digital pin 13 as an output.
  pinMode(13, OUTPUT); //aux led
  lcd.begin(16, 2);
  Dynamixel.begin(1000000,2);  // Inicialize the servo at 1Mbps and Pin Control 2
}

// the loop function runs over and over again forever
void loop() {
  lcd.print("Servo 1:");
  lcd.setCursor(0, 1);
  lcd.print("Servo 2:");
  
  lcd.setCursor(11, 0);
  value = random(0,4096);
  Dynamixel.move(13,value);  // Move the Servo radomly from 200 to 800
  lcd.print(value);
  
  lcd.setCursor(11, 1);
  value = random(0,4096);
  Dynamixel.move(14,value);  // Move the Servo radomly from 200 to 800
  lcd.print(value);
  
  delay(1000);
  lcd.clear();
}
