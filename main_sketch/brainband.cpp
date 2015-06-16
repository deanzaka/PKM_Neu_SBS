#include "Arduino.h"
#include "brainband.h"
#include <LiquidCrystal.h>

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

brainband::brainband() {
  Serial2.begin(57600);
}

brainband::~brainband() {}

byte brainband::ReadOnce(){
  int ByteRead;
  
  while(!Serial2.available());
  ByteRead = Serial2.read();
  
  return ByteRead;
}

unsigned int brainband::getAtt() {
  if(ReadOnce() == 170) {
    if(ReadOnce() == 170) {
      payloadLength = ReadOnce();
      if(payloadLength > 169) return 0;
      
      generatedChecksum = 0;
      for(int i = 0; i < payloadLength; i++) {  
        payloadData[i] = ReadOnce();            //Read payload into memory
        generatedChecksum += payloadData[i];
      }
      
      checksum = ReadOnce();                      //Read checksum byte from stream      
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
      }
      if(bigPacket) return attention/10;
    }
  }
}

unsigned int brainband::getMed() {
  if(ReadOnce() == 170) {
    if(ReadOnce() == 170) {
      payloadLength = ReadOnce();
      if(payloadLength > 169) return 0;
      
      generatedChecksum = 0;
      for(int i = 0; i < payloadLength; i++) {  
        payloadData[i] = ReadOnce();            //Read payload into memory
        generatedChecksum += payloadData[i];
      }
      
      checksum = ReadOnce();                      //Read checksum byte from stream      
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
      }
      if(bigPacket) return meditation/10;
    }
  }
}
