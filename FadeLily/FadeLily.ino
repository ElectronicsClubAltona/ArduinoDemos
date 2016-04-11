/*
 Fade
 
 This example shows how to fade an LED on pin 9
 using the analogWrite() function.
 
 This example code is in the public domain.
 */

int led = 9;           // the pin that the LED is attached to
int brightness = 0;    // how bright the LED is
int fadeAmount = 5;    // how many points to fade the LED by

int ledarray [3] ; 

// the setup routine runs once when you press reset:
void setup()  { 
     ledarray[0] = 13;
  ledarray[1] = 9;
   ledarray[2] = 10; 
  
  // declare pin 9 to be an output:
  pinMode(led, OUTPUT);
} 

// the loop routine runs over and over again forever:
void loop()  { 
  
  for (int l=0; l<3; l++) {
  // set the brightness of pin 9:
  analogWrite(ledarray[l], brightness);    // this effect - all three together same 

  // change the brightness for next time through the loop:
  brightness = brightness + fadeAmount;

  // reverse the direction of the fading at the ends of the fade: 
  if (brightness == 0 || brightness == 255) {
    fadeAmount = -fadeAmount ; 
  }     
  // wait for 30 milliseconds to see the dimming effect    
  delay(30);                            
  }
  
}

