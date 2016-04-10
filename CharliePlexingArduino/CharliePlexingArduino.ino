/*
  AnalogReadSerial
  Reads an analog input on pin 0, prints the result to the serial monitor.
  Graphical representation is available using serial plotter (Tools > Serial Plotter menu)
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.
*/

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  Serial.println( "CharliePlexing");
}

// the loop routine runs over and over again forever:
void loop() {
  int n;

  for ( n = 0; n < 17; n++ ) {
    // Serial.print( "wires= %3d LEDs = %3d\n", n); //,
    Serial.print( "Wires= ");
    Serial.print(n);
    Serial.print(" ");
    Serial.print( "LEDs= ");
    Serial.println(n * n - n);

  }
  Serial.println(" ");
  delay(1000);
}
