void setup() {
  // put your setup code here, to run once:
  // to show the Show Timestamp feature in Arduino IDE 1.8.8
  Serial.begin(9600);
}

void loop() {
  // transmit word and wait a while
  // then, using the 'Show Timestamp' feature in Arduino IDE 1.8.8 
  // watch the time stamps 
  // this is useful for testing logging type programs
  Serial.println("tick");
  delay(5000);
}
