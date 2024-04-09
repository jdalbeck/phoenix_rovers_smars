// Adafruit Motor shield library
// copyright Adafruit Industries LLC, 2009
// this code is public domain, enjoy!

#include <AFMotor.h>

// DC motor on M2
AF_DCMotor motor(2);
AF_DCMotor motor2(1);

 // ESP32
//int trigPin = 5;    // Trigger
//int echoPin = 13;    // Echo

// Arduino
int trigPin = 10;    // Trigger
int echoPin = 9;    // Echo

long duration, cm, inches;
 
void setup() {
    //Define inputs and outputs
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
   
  // turn on motor #2
  motor.setSpeed(200);
  motor.run(RELEASE);

  motor2.setSpeed(200);
  motor2.run(RELEASE);
}

int i;

// Test the DC motor, stepper and servo ALL AT ONCE!
void loop() {
  motor.run(FORWARD);
  motor2.run(FORWARD);
  
  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
 
  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
 
  // Convert the time into a distance
  cm = (duration/2) / 29.1;     // Divide by 29.1 or multiply by 0.0343
  inches = (duration/2) / 74;   // Divide by 74 or multiply by 0.0135
if (inches<5) {
  motor.run(RELEASE);
  motor2.run(RELEASE);
  delay(25000);
  motor.run(FORWARD);
  motor2.run(FORWARD);
}

}
