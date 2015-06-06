#include <LiquidCrystal.h>

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

void setup() {
  // initialize digital pin 13 as an output.
  pinMode(13, OUTPUT);
  lcd.begin(16, 2);
  lcd.print("hello, world!");
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);              // wait for a second
  lcd.setCursor(0, 1);
  lcd.print(millis()/1000);
  digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);              // wait for a second
  lcd.setCursor(0, 1);
  lcd.print(millis()/1000);
}
