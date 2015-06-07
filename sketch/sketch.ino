#include <LiquidCrystal.h>
#include <Wire.h>
#include <DynamixelSerial.h>

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
int value, reading = 0;
byte dist;

void setup() {
  // initialize digital pin 13 as an output.
  pinMode(13, OUTPUT); //aux led
  Wire.begin();
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
  
  dist = ping(113);
  lcd.setCursor(5,1);
  lcd.print(dist);
  
  dist = ping(112);
  lcd.setCursor(9,1);
  lcd.print(dist);
  
  delay(1000);
  lcd.clear();
}

byte ping(byte address){
// step 1: instruct sensor to read echoes
  Wire.beginTransmission(address); // transmit to device #112 (0x70)
  // the address specified in the datasheet is 224 (0xE0)
  // but i2c adressing uses the high 7 bits so it's 112
  Wire.write(byte(0x00));      // sets register pointer to the command register (0x00)
  Wire.write(byte(0x51));      // command sensor to measure in "inches" (0x50)
  // use 0x51 for centimeters
  // use 0x52 for ping microseconds
  Wire.endTransmission();      // stop transmitting
  // step 2: wait for readings to happen
  delay(70);                   // datasheet suggests at least 65 milliseconds

  // step 3: instruct sensor to return a particular echo reading
  Wire.beginTransmission(address); // transmit to device #112
  Wire.write(byte(0x02));      // sets register pointer to echo #1 register (0x02)
  Wire.endTransmission();      // stop transmitting
  
  // step 4: request reading from sensor
  Wire.requestFrom(address, 2);    // request 2 bytes from slave device #112

  // step 5: receive reading from sensor
  if (2 <= Wire.available())   // if two bytes were received
  {
    reading = Wire.read();  // receive high byte (overwrites previous reading)
    reading = reading << 8;    // shift high byte to be high 8 bits
    reading |= Wire.read(); // receive low byte as lower 8 bits
    return(reading);   // print the reading
  }
}
