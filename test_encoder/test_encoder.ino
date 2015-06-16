#include <LiquidCrystal.h>

#define ENCODERPIN 4 //  pin interupt 4 di p digital 19
#define PHI 3.14 
#define RADIUS 0.035 // r dari roda encoder

LiquidCrystal lcd(7,6,5,4,3,2);

long coder= 0;
float freq,omega,kecepatan;



void setup(){

  Serial.begin(9600);                            //init the Serial port to print the data
  attachInterrupt(ENCODERPIN, wheelSpeed, CHANGE);    //init the interrupt mode for the digital pin 19
  //attachInterrupt(RIGHT, RwheelSpeed, CHANGE);   //init the interrupt mode for the digital pin 3
  lcd.begin(16,2);
}

void loop(){

  static unsigned long timer = 0;  //print manager timer
  static unsigned long timer1 = 0;  //print manager timer
  
     

  if(millis() - timer > 100){                   
    
    Serial.print("Coder value per detik : ");
    Serial.print(coder);
    Serial.print("\n");
    
    Serial.print("kecepatan per km/jam: ");
    Serial.print(kecepatan);
    Serial.print("\n");
    
    lcd.setCursor(0,0);
    lcd.print("Coder : ");
    lcd.print(coder);
    
    lcd.setCursor(0,1);
    lcd.print("V km/h : ");
    lcd.print(kecepatan);
     
    coder= 0;                 //clear the data buffer
    timer = millis();

  }
  
  if(millis() - timer1 > 1000){
    
    freq=coder;
    omega=2*PHI*freq;
    kecepatan= 3.6*omega*RADIUS; //dalam km/jam
    
    Serial.print("Coder value per detik : ");
    Serial.print(coder);
    Serial.print("\n");
    
    Serial.print("kecepatan per km/jam: ");
    Serial.print(kecepatan);
    Serial.print("\n");
    
    lcd.setCursor(0,0);
    lcd.print("Coder : ");
    lcd.print(coder);
    
    lcd.setCursor(0,1);
    lcd.print("V km/h : ");
    lcd.print(kecepatan);
  //lcd.clear();    
  timer1=millis(); 
  }
   
}


void wheelSpeed()
{
  coder ++;  //count the left wheel encoder interrupts
}



