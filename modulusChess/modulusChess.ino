void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  // 12 jun  2015

  // testing modulus arithmetic

  //int main ()  {
  int i, r, m;
  Serial.println("Modulus Arithmetic");
  for (i = -6; i < 10; i++) {
    m = i / 3;
    r = i % 3;
    Serial.print(" i,r,m = ");
    Serial.print( i);
    Serial.print(" ");
    Serial.print( r);
    Serial.print(" ");
    Serial.print( m);
    Serial.println();
    delay(1000);
  }

  // return(0);
}


