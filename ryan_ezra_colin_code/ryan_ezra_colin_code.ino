// Adafruit Motor shield library
// copyright Adafruit Industries LLC, 2009
// this code is public domain, enjoy!

#include <AFMotor.h>

// DC motor on M2
AF_DCMotor motor(1);
AF_DCMotor motor2(2);

// Arduino Settings
#if defined(__AVR__)
  #define SERIALBAUD 9600
  #define TRIGPIN 10
  #define ECHOPIN 9
// Wemos D1 R32 Settings
#elif defined(ARDUINO_D1_UNO32)
  #define SERIALBAUD 115200
  #define TRIGPIN 5
  #define ECHOPIN 13
#endif

long duration, cm, inches;
 
void setup() {
  Serial.begin(SERIALBAUD);

    //Define inputs and outputs
  pinMode(TRIGPIN, OUTPUT);
  pinMode(ECHOPIN, INPUT);
   
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
  digitalWrite(TRIGPIN, LOW);
  delayMicroseconds(5);
  digitalWrite(TRIGPIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGPIN, LOW);
 
  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(ECHOPIN, INPUT);
  duration = pulseIn(ECHOPIN, HIGH);
 
  // Convert the time into a distance
  cm = (duration/2) / 29.1;     // Divide by 29.1 or multiply by 0.0343
  inches = (duration/2) / 74;   // Divide by 74 or multiply by 0.0135
  
  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();

  // Stop, turn right, wait a few seconds, then restart the loop
  if (inches<5) {
    motor.run(RELEASE);
    motor2.run(RELEASE);
    delay(50);
    motor.run(FORWARD);
    motor2.run(BACKWARD);
    delay(1000);
    motor.run(RELEASE);
    motor2.run(RELEASE);
    delay(5000);
  }

}
