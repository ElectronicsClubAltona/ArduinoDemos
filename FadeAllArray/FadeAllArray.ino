/*
 Fade

 This example shows how to fade an LED on pin 9
 using the analogWrite() function.

 This example code is in the public domain.

 mod to allow a group of LEDs as defined in an array to be faded
 Mike Hewitt 20-Aug-2015
 remember to use Ctrl-T to auto format
 */

// change fadeArrayLen to reflect number in array - executing this shows which LEDs are PWMable
// seems different for Arduino
// trying to fade a non-fadeable LED displays a JUMP in brightness  e.g. pin 2

int fadeArray[] = {3, 9, 10, 11, 2, 13}; // array of all PWM capable LEDs
int fadeArrayLen = 6;

int led = 3;           // the pin that the LED is attached to
int brightness = 0;    // how bright the LED is
int fadeAmount = 5;    // how many points to fade the LED by

// the setup routine runs once when you press reset:
void setup() {
  // declare pin 9 to be an output:
  //   original line   pinMode(led, OUTPUT);
  for (int f = 0; f < fadeArrayLen; f++) {
    pinMode(fadeArray[f], OUTPUT);
  }
}
// the loop routine runs over and over again forever:
void loop() {
  // fadeAmount = 5;

  //  fadeAll();
  //   temp fadeAmount = 5;

  fadeAll();
  // set the brightness of pin 9:
  //x analogWrite(led, brightness);
}

void fadeAll() {
  for (int f = 0; f < fadeArrayLen; f++) {
    analogWrite(fadeArray[f], brightness);
  }
  brightness = brightness + fadeAmount;
  // notice that fadeAmount is set (written to) twice in loop() 
  // brightness = brightness + fadeAmount;
  // brightness = brightness + fadeAmount;
  if (brightness <= 1 || brightness >= 255) {
    fadeAmount = -fadeAmount ;
  }
  delay(30);  // a delay here slows down the WHOLE loop
}


