/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO 
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino model, check
  the Technical Specs of your board  at https://www.arduino.cc/en/Main/Products
  
  This example code is in the public domain.

  modified 8 May 2014
  by Scott Fitzgerald
  
  modified 2 Sep 2016
  by Arturo Guadalupi
  
  modified 8 Sep 2016
  by Colby Newman
*/
//#include <functional>
//#include <vector>
//#include <iostream>

//auto my_lambda_func = [&](int x) { /*...*/ };
//auto my_onheap_lambda_func = new auto([=](int x) { /*...*/ });
  int thisByte = 33;
  
auto a_lambda_func = [](int x) { 
  thisByte = x * 80;
  };
void (* func_ptr)(int) = a_lambda_func;


// the setup function runs once when you press reset or power the board
void setup() {

//  func_ptr(4); //calls the lambda.
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
    func_ptr(4); //calls the lambda.
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(  thisByte);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(  thisByte);                       // wait for a second
}
