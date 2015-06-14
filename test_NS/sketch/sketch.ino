////////////////////////////////////////////////////////////////////////
// Arduino Bluetooth Interface with Mindwave
// 
// This is example code provided by NeuroSky, Inc. and is provided
// license free.
////////////////////////////////////////////////////////////////////////

#include <LiquidCrystal.h>

#define LED 13
#define BAUDRATE 57600
#define DEBUGOUTPUT 0

// checksum variables
byte generatedChecksum = 0;
byte checksum = 0; 
int payloadLength = 0;
byte payloadData[64] = {
  0};
byte poorQuality = 0;
byte attention = 0;
byte meditation = 0;

// system variables
long lastReceivedPacket = 0;
boolean bigPacket = false;

LiquidCrystal lcd(7,6,5,4,3,2);

//////////////////////////
// Microprocessor Setup //
//////////////////////////
void setup() {
  lcd.begin(16,2);
  pinMode(LED, OUTPUT);
  Serial2.begin(BAUDRATE);           // USB
  Serial.begin(BAUDRATE);
}

////////////////////////////////
// Read data from Serial UART //
////////////////////////////////
byte ReadOneByte() {
  int ByteRead;

  while(!Serial2.available());
  ByteRead = Serial2.read();

#if DEBUGOUTPUT  
  Serial2.print((char)ByteRead);   // echo the same byte out the USB serial (for debug purposes)
#endif

  return ByteRead;
}

/////////////
//MAIN LOOP//
/////////////
void loop() {


  // Look for sync bytes
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
          Serial.print("PoorQuality: ");
          Serial.print(poorQuality, DEC);
          Serial.print(" Attention: ");
          Serial.print(attention, DEC);
          Serial.print(" Time since last packet: ");
          Serial.print(millis() - lastReceivedPacket, DEC);
          lastReceivedPacket = millis();
          Serial.print("\n");

          switch(attention / 10) {
          case 0:
            lcd.setCursor(0,0);
            lcd.print("Value: MIN      ");
            break;
          case 1:
            lcd.setCursor(0,0);
            lcd.print("Value: |        ");
            break;
          case 2:
            lcd.setCursor(0,0);
            lcd.print("Value: ||       ");
            break;
          case 3:              
            lcd.setCursor(0,0);
            lcd.print("Value: |||      ");
            break;
          case 4:
            lcd.setCursor(0,0);
            lcd.print("Value: ||||     ");
            break;
          case 5:
            lcd.setCursor(0,0);
            lcd.print("Value: |||||    ");
            break;
          case 6:              
            lcd.setCursor(0,0);
            lcd.print("Value: ||||||   ");
            break;
          case 7:
            lcd.setCursor(0,0);
            lcd.print("Value: |||||||  ");
            break;    
          case 8:
            lcd.setCursor(0,0);
            lcd.print("Value: |||||||| ");
            break;
          case 9:
            lcd.setCursor(0,0);
            lcd.print("Value: |||||||||");
            break;
          case 10:
            lcd.setCursor(0,0);
            lcd.print("Value: MAX      ");
            break;           
          }
          switch(meditation / 10) {
          case 0:
            lcd.setCursor(0,1);
            lcd.print("Value: MIN      ");
            break;
          case 1:
            lcd.setCursor(0,1);
            lcd.print("Value: |        ");
            break;
          case 2:
            lcd.setCursor(0,1);
            lcd.print("Value: ||       ");
            break;
          case 3:              
            lcd.setCursor(0,1);
            lcd.print("Value: |||      ");
            break;
          case 4:
            lcd.setCursor(0,1);
            lcd.print("Value: ||||     ");
            break;
          case 5:
            lcd.setCursor(0,1);
            lcd.print("Value: |||||    ");
            break;
          case 6:              
            lcd.setCursor(0,1);
            lcd.print("Value: ||||||   ");
            break;
          case 7:
            lcd.setCursor(0,1);
            lcd.print("Value: |||||||  ");
            break;    
          case 8:
            lcd.setCursor(0,1);
            lcd.print("Value: |||||||| ");
            break;
          case 9:
            lcd.setCursor(0,1);
            lcd.print("Value: |||||||||");
            break;
          case 10:
            lcd.setCursor(0,1);
            lcd.print("Value: MAX      ");
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
}



