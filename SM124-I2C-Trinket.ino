/**************************************************************************************
Trinket displays NVE SM12x I²C Smart Sensor output on a COM-11441 7-segment display
Use with AG958 or AG961 breakout boards (see https://www.nve.com/webstore/catalog ) 
SDA=#0; SCL=#2; LED=#1; USB for programming=#3/#4 
**************************************************************************************/ 
#include <TinyWireM.h> //ATTiny85 I²C Master library
//Use Wire.h for Arduino and replace "TinyWireM." with "Wire."
int sensor, digit; //Sensor output; digit counter
void setup() {TinyWireM.begin();}

void loop() {
  TinyWireM.requestFrom(36,1); //Request one byte from I²C address 72 (36 = 72/2)
  sensor = TinyWireM.read(); //Read sensor

//Display sensor output
  TinyWireM.beginTransmission(0x71); //Write to 7-segment display (I²C address 0x71)
  TinyWireM.write(0x76); //Clear display
  TinyWireM.write(0x77); //Set decimal point
  TinyWireM.write(0b010); //Displays xx.x mT
  TinyWireM.write(0x79); //Set cursor
  TinyWireM.write(1); //Set cursor to 2nd digit for 3-digit output
for(digit=100; digit>0; digit/=10) { //Start at 100s digit
  TinyWireM.write((sensor%(digit*10))/digit); //Scan through display digits
  }
  TinyWireM.endTransmission();
delay(100); //10 samples/second
}
