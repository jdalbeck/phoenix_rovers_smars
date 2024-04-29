/*
  HC-SR04 NewPing Library Demonstration
  HC-SR04-NewPing.ino
  Demonstrates functions of NewPing Library for HC-SR04 Ultrasonic Range Finder
  Displays results on Serial Monitor

  DroneBot Workshop 2017
  http://dronebotworkshop.com
*/

// This uses Serial Monitor to display Range Finder distance readings

// Include NewPing Library
#include <NewPing.h>

// Hook up HC-SR04 with Trig to Arduino Pin 10, Echo to Arduino pin 13
// Maximum Distance is 400 cm


// Arduino Settings
#if defined(__AVR__)
  #define SERIALBAUD 9600
  #define TRIGGER_PIN 10
  #define ECHO_PIN 9

// Wemos D1 R32 Settings
#elif defined(ARDUINO_D1_UNO32)
  #define SERIALBAUD 115200
  #define TRIGGER_PIN 5
  #define ECHO_PIN 13
#endif

#define MAX_DISTANCE 400
 
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

float distance;

void setup() {
  Serial.begin (SERIALBAUD);
}

void loop() {
   
  distance = sonar.ping_in();
  
  // Send results to Serial Monitor
  Serial.print("Distance = ");
  if (distance >= 400 || distance <= 2) {
    Serial.println("Out of range");
  }
  else {
    Serial.print(distance);
    Serial.println(" in");
    delay(500);
  }
  delay(500);
}