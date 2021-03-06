// Wire Master Writer
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Writes data to an I2C/TWI slave device
// Refer to the "Wire Slave Receiver" example for use with this

// Created 29 March 2006
// This example code is in the public domain.
/*  <ol>Todo:
 *  <li>change hardware address on LCD to match code 
 *  </li><li>add code for initialising LCD screen 
 *  </li><li>send data to LCD screen
 *  </li>
 *  </ol>
 */

#include <Wire.h>
#define LCDadd 0// x27   // check this out - maybe incorrect
void setup() {
//  Wire.begin(); // join i2c bus (address optional for master)
}

byte x = 0;

void loop() {

  for (int l = LCDadd; l < LCDadd+16 ; l ++) {
  Wire.begin(l); // join i2c bus (address optional for master)
  Wire.beginTransmission(l); // transmit to device #l
  Wire.write("x is ");        // sends five bytes
  Wire.write(x);              // sends one byte
  Wire.endTransmission();    // stop transmitting

  x++;
  delay(500);
  }

  
}
