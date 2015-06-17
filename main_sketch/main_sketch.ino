#include <LiquidCrystal.h>
#include <DynamixelSerial.h>
#include <Wire.h>
#include "srf10.h"

#define LED 13
#define ENCODERPIN 4 //  pin interupt 4 di p digital 19
#define PHI 3.14 
#define RADIUS 0.035 // r dari roda encoder

// checksum variables
byte generatedChecksum = 0;
byte checksum = 0; 
int payloadLength = 0;
byte payloadData[64] = {0};
byte poorQuality = 0;
byte attention = 0;
byte meditation = 0;

// system variables
long lastReceivedPacket = 0;
boolean bigPacket = false;
boolean waitFlag = false;

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
int value, servo;
unsigned int brainVal;
byte dist;
srf10 srf;

long coder= 0;
float freq,omega,kecepatan;

void setup() {
  // initialize digital pin 13 as an output.
  pinMode(13, OUTPUT); //aux led
  lcd.begin(16, 2);
  Dynamixel.begin(1000000,8);  // Init servo at 1Mbps and Pin Control 2
  Serial2.begin(57600);
  Serial3.begin(115200);
  attachInterrupt(ENCODERPIN, wheelSpeed, CHANGE);    //init the interrupt mode for the digital pin 19
}

byte ReadOneByte() {
  int ByteRead;

  while(!Serial2.available());
  ByteRead = Serial2.read();

  return ByteRead;
}

void wheelSpeed()
{
  coder ++;  //count the left wheel encoder interrupts
}

// the loop function runs over and over again forever
void loop() {
  
  static unsigned long timer = 0;  //print manager timer
  static unsigned long timer1 = 0;  //print manager timer
  
  if(millis() - timer1 > 1000){
    
    freq=coder;
    omega=2*PHI*freq;
    kecepatan= 3.6*omega*RADIUS; //dalam km/jam
    
    Serial3.print("Coder value per detik : ");
    Serial3.print(coder);
    Serial3.print("\n");
    
    Serial3.print("kecepatan per km/jam: ");
    Serial3.print(kecepatan);
    Serial3.print("\n");
    
    if(attention < 100) {
      Serial3.print("attention: ");
      Serial3.print(attention/10);
      Serial3.print("\n");
    }
    
    lcd.setCursor(0,1);
    lcd.print("V km/h : ");
    lcd.print(kecepatan);
    //lcd.clear();    
    timer1=millis(); 
  }
  
  
  // ---------------------------------------- BRAINBAND -------------------------------- //
  if(ReadOneByte() == 170) {
    if(ReadOneByte() == 170) {

      payloadLength = ReadOneByte();
      if(payloadLength > 169)                      //Payload length can not be greater than 169
          return;

      generatedChecksum = 0;        
      for(int i = 0; i < payloadLength; i++) {  
        payloadData[i] = ReadOneByte();            //Read payload into memory
        generatedChecksum += payloadData[i];
      }   

      checksum = ReadOneByte();                      //Read checksum byte from stream      
      generatedChecksum = 255 - generatedChecksum;   //Take one's compliment of generated checksum

        if(checksum == generatedChecksum) {    

        poorQuality = 200;
        attention = 0;
        meditation = 0;

        for(int i = 0; i < payloadLength; i++) {    // Parse the payload
          switch (payloadData[i]) {
          case 2:
            i++;            
            poorQuality = payloadData[i];
            bigPacket = true;            
            break;
          case 4:
            i++;
            attention = payloadData[i];                        
            break;
          case 5:
            i++;
            meditation = payloadData[i];
            break;
          case 0x80:
            i = i + 3;
            break;
          case 0x83:
            i = i + 25;      
            break;
          default:
            break;
          } // switch
        } // for loop

        // *** Add your code here ***

        if(bigPacket) {
          if(poorQuality == 0)
            digitalWrite(LED, HIGH);
          else
            digitalWrite(LED, LOW);

          switch(attention / 10) {
          case 0:
            lcd.setCursor(0,0);
            lcd.print("Focus: MIN      ");
            break;
          case 1:
            lcd.setCursor(0,0);
            lcd.print("Focus: |        ");
            break;
          case 2:
            lcd.setCursor(0,0);
            lcd.print("Focus: ||       ");
            break;
          case 3:              
            lcd.setCursor(0,0);
            lcd.print("Focus: |||      ");
            break;
          case 4:
            lcd.setCursor(0,0);
            lcd.print("Focus: ||||     ");
            break;
          case 5:
            lcd.setCursor(0,0);
            lcd.print("Focus: |||||    ");
            break;
          case 6:              
            lcd.setCursor(0,0);
            lcd.print("Focus: ||||||   ");
            break;
          case 7:
            lcd.setCursor(0,0);
            lcd.print("Focus: |||||||  ");
            break;    
          case 8:
            lcd.setCursor(0,0);
            lcd.print("Focus: |||||||| ");
            break;
          case 9:
            lcd.setCursor(0,0);
            lcd.print("Focus: |||||||||");
            break;
          case 10:
            lcd.setCursor(0,0);
            lcd.print("Focus: MAX      ");
            break;           
          }          
        }
        bigPacket = false;        
      }
      else {
        // Checksum Error
      }  // end if else for checksum
    } // end if read 0xAA byte
  } // end if read 0xAA byte
  
  // ---------------------------------------- brainband -------------------------------- //
  
  if(kecepatan > 30) {
    if(waitFlag == false) {
      if(attention < 20) {
        waitFlag = true;
        timer = millis();
      }
    }
    else {
      if(attention > 20) waitFlag = false;
      else {
        if ((millis() - timer) > 3000) {
          // kasih buzzer
          
          // kurangi kecepatan
          Dynamixel.move(13,1000); // value nya 0 - 4096
          Dynamixel.move(14,1000);
        }
      }
    }
  }
  
//  // cek srf
//  dist = srf.ping(112);
//  dist = srf.ping(113);
//  // lakukan pengereman
  if(dist < 10 && servo != 20) { // in cm
    Dynamixel.move(13,2000); // value nya 0 - 4096
    Dynamixel.move(14,2000);
    servo = 20;
  }
  
}
