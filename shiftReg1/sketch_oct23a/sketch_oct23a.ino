//#include <genieArduino.h>

// 14 november 2023 
// modify this in prep for Colorduino - LED matrix from analogue port connector

//pinMode(A0, OUTPUT);
//digitalWrite(A0, HIGH);
//pinMode(A0, INPUT_PULLUP);  // set pull-up on analog pin 0
//https://docs.arduino.cc/learn/microcontrollers/analog-input


#define DATA 6
#define LATCH 8
#define CLOCK 10

// setup the array
int digits [] = {252, 96, 218, 242, 102, 182, 190, 224, 254, 246, 238, 62, 156, 122, 158, 142};


void setup() {
  // put your setup code here, to run once:
  pinMode(LATCH, OUTPUT);
  pinMode(CLOCK, OUTPUT);
  pinMode(DATA, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:

  int i ;
  for ( i = 0; i < 16; i++) {
    digitalWrite(LATCH, LOW);
    shiftOut(DATA, CLOCK, LSBFIRST, digits[i]);
    digitalWrite(LATCH, HIGH);
    delay(250);
  }
  for ( i = 0; i < 16; i++) {
    digitalWrite(LATCH, LOW);
    shiftOut(DATA, CLOCK, LSBFIRST, digits[i] + 1);
    digitalWrite(LATCH, HIGH);
    delay(250);
  }
}
