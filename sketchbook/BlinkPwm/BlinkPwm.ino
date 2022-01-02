/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */

// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int led = 1;
int t = 100;

int brightness = 0;    // how bright the LED is
int fadeAmount = 5;    // how many points to fade the LED by

void blink(int n,  int t2)
{
  digitalWrite(led, LOW);
  delay(t2);
  for (int i=0; i<n; i++)
  {
    digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(t2);               // wait for a second
    digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
    delay(t2);               // wait for a second
  }
}


// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);
  //initTimer1();
}

// the loop routine runs over and over again forever:
void loop() {
  analogWrite(led, brightness);
  brightness = brightness + fadeAmount;
  if (brightness == 255) {
    blink(5, 500);
    fadeAmount = -fadeAmount ;
  }
  else if (brightness == 0)
  {
    blink(5, 250);
    fadeAmount = -fadeAmount ;
  }
  delay(t);
  /*digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(t);               // wait for a second
  digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
  delay(t);               // wait for a second*/
}
