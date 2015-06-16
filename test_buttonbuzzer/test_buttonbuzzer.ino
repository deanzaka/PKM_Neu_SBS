#include <LiquidCrystal.h>
LiquidCrystal lcd(7,6,5,4,3,2);

const int PB13 = 13, PB12 = 12, PB11 = 11, PB10 = 10, buz=A0;
int buttonState13 = 0, buttonState12 =0, buttonState11 =0, buttonState10 =0;

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16,2);
  pinMode(PB13,INPUT);
  pinMode(PB12,INPUT);
  pinMode(PB11,INPUT);
  pinMode(PB10,INPUT);
  digitalWrite(PB13,HIGH);
  digitalWrite(PB12,HIGH);
  digitalWrite(PB11,HIGH);
  digitalWrite(PB10,HIGH);
  pinMode(buz,OUTPUT);
}

void loop() {
  digitalWrite(buz,HIGH);
  lcd.setCursor(3,0);
  lcd.print("Nunggu input");
  buttonState13 = digitalRead(PB13);
  buttonState12 = digitalRead(PB12);
  buttonState11 = digitalRead(PB11);
  buttonState10 = digitalRead(PB10);
  
  while(buttonState13==LOW){
    lcd.setCursor(3,1);
    lcd.print("B13 kepencet");
    digitalWrite(buz,LOW);
    delay(100);
    buttonState13 = digitalRead(PB13);
    if(buttonState13 == HIGH){
      lcd.clear();
      break;  
    }  
  }
  
  while(buttonState12==LOW){
    lcd.setCursor(3,1);
    lcd.print("B12 kepencet");
    delay(100);
    buttonState12 = digitalRead(PB12);
    if(buttonState12 == HIGH){
      lcd.clear();
      break;  
    }  
  }
  
  while(buttonState11==LOW){
    lcd.setCursor(3,1);
    lcd.print("B11 kepencet");
    delay(100);
    buttonState11 = digitalRead(PB11);
    if(buttonState11 == HIGH){
      lcd.clear();
      break;  
    }  
  }
  
  while(buttonState10==LOW){
    lcd.setCursor(3,1);
    lcd.print("B10 kepencet");
    delay(100);
    buttonState10 = digitalRead(PB10);
    if(buttonState10 == HIGH){
      lcd.clear();
      break;  
    }  
  }

}
