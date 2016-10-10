// fizz buzz  13/11/11
// to demo integer division
// Mike Hewitt
// 10/10/2016
String stringi, stringf, stringb, stringcat;

int i = 0;


void setup() {
  stringi = String("i= ");
  stringf = String(" fizz ");
  stringb = String(" buzz ");
  Serial.begin(9600);
  Serial.println("Demo of fizz buzz -> integer division");
}


void loop() {


  for ( i = 0; i <= 1000; i++) {
    // fizz buzz
    //  Serial.print("i= ");
    //  Serial.print(  i);
    //  Serial.print("  ");

    //  if ((i % 3) == 0) Serial.print("fizz ");
    //  if ((i % 5) == 0) Serial.print("buzz ");

    // Serial.println();
    // delay(1000);
    stringcat = stringi + i;
    if ((i % 3) == 0) stringcat = stringcat + stringf;
    if ((i % 5) == 0) stringcat = stringcat + stringb;

    Serial.println(stringcat);
    delay(500);

  }
}












