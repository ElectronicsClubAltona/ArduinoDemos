//YWROBOT
//Compatible with the Arduino IDE 1.0
//Library version:1.1

// adapted on 30April 2019
/*
 * why two lcd.init() ?
 * why lcd.cursor(3,0) ?
 * what backlight and can we reduce brightness ?
 */
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4); 
// set the LCD address to 0x27 for a 16 chars and 2 line display

void setup()
{
  lcd.init();                      // initialize the lcd
  lcd.init();
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(1, 0);  // ist arg for offset from LHS
  lcd.print("Hello, world! M");
  lcd.setCursor(2, 1);
  lcd.print("Ywrobot Arduino!");
  lcd.setCursor(0, 2);
  lcd.print("Arduino LCM IIC 2004");
  lcd.setCursor(2, 3);
  lcd.print("Power By Ec-yuan!");
}


void loop()
{
}
