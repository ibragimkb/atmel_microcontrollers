/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */

#include <SoftwareSerial.h>
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int t = 250;

#define RX    0   // *** P0 D0, Pin 1 to TX USB TTL
#define TX    1   // *** P1 D1, Pin 2 to RX USB TTL
#define BRATE 19200
SoftwareSerial SerialSoft(RX, TX);
// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  SerialSoft.begin(BRATE);
  SerialSoft.println("Initializing...");
}

// the loop routine runs over and over again forever:
void loop() {
  //digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
  SerialSoft.println("on");
  /*int sensorValueA0 = analogRead(2);
  SerialSoft.println(sensorValueA0);*/
  int sensorValueA0 = analogRead(2); //P2
  int sensorValueA1 = analogRead(3); //P3
  int sensorValueA2 = analogRead(4); //P4
  SerialSoft.print(sensorValueA0);
  SerialSoft.print(":");
  SerialSoft.print(sensorValueA1);
  SerialSoft.print(":");
  SerialSoft.println(sensorValueA2);

  /*int sensorValueA0 = analogRead(A1);
  int sensorValueA1 = analogRead(A2);
  int sensorValueA2 = analogRead(A3);
  SerialSoft.print(sensorValueA0);
  SerialSoft.print(":");
  SerialSoft.print(sensorValueA1);
  SerialSoft.print(":");
  SerialSoft.println(sensorValueA2);*/
  
  delay(t);               // wait for a second
  //digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
  //SerialSoft.println("off");
  //delay(t);               // wait for a second
}
