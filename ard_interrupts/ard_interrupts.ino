int interruptPin = 2;
int ledPin = 13;
int period = 500;

void setup() {

  pinMode(ledPin, OUTPUT);
  pinMode(interruptPin, INPUT);
  digitalWrite(interruptPin, HIGH); // pull-up
  attachInterrupt(0, goFast, FALLING);


}

void loop() {
  digitalWrite(ledPin, HIGH);
  delay(period);
  digitalWrite(ledPin, HIGH);
  delay(period);
  // put your main code here, to run repeatedly:

}

void goFast() {
  period = 100;
}


