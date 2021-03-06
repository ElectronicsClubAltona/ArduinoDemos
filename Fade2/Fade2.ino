/*
  Fade

  This example shows how to fade an LED on pin 9 using the analogWrite()
  function.

  The analogWrite() function uses PWM, so if you want to change the pin you're
  using, be sure to use another PWM capable pin. On most Arduino, the PWM pins
  are identified with a "~" sign, like ~3, ~5, ~6, ~9, ~10 and ~11.

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Fade
*/

#define red 9
#define green 11
#define blue 10

boolean flip = false;
int led = 9;           // the PWM pin the LED is attached to
int brightness = 0;    // how bright the LED is
int fadeAmount = 3;    // how many points to fade the LED by
int counter = 1;

// the setup routine runs once when you press reset:
void setup() {
  // declare pin 9 to be an output:
  pinMode(led, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
}
/*
   Does not work as expected due to loop() being a continuous loop
   need to test at the zero crossing point of brightness
   Fixed and operational on Black Tower

*/
int swap (boolean v) {
  if (v )
    return green;
  else
    return blue;
}
int cycleLED (int counterz ) {

  int tv = counterz % 3;
  if (tv == 0)
    return red;
  if (tv == 1)
    return green;
  if (tv == 2)
    return blue;

}

// the loop routine runs over and over again forever:
void loop() {
  // set the brightness of pin 9:
  if (brightness <= 0)
  { counter = counter + 1 ;
    led = cycleLED (counter);
    Serial.print( led);
    Serial.print( " ");   
  }
  /*  { flip = ! flip;
        led = swap(flip);
      }
  */
  analogWrite(led, brightness);

  // change the brightness for next time through the loop:
  brightness = brightness + fadeAmount;

  // reverse the direction of the fading at the ends of the fade:
  if (brightness <= 0 || brightness >= 255) {
    fadeAmount = -fadeAmount;
  }
  // wait for 30 milliseconds to see the dimming effect
  delay(30);




}
