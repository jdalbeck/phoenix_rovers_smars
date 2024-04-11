/*
  Motor Test

  Simple test which runs the motors forwards, then backwards, then pauses, and repeats.
*/

// Use our custom motor library (https://github.com/jdalbeck/Adafruit-Motor-Shield-library)
// to allow this to work on both Arduino and ESP32
#include <AFMotor.h>

// Initialize left motor and right motor
AF_DCMotor leftMotor(1);
AF_DCMotor rightMotor(2);


// Setup code section
void setup() {

  //Motor setup
  leftMotor.setSpeed(100);
  leftMotor.run(RELEASE);
  rightMotor.setSpeed(100);
  rightMotor.run(RELEASE);
}

// Main loop section
void loop() {

  // Run both the motors forward for 3 seconds
  leftMotor.run(FORWARD);
  rightMotor.run(FORWARD);
  delay(3000);

  // Stop the motors for 0.3 seconds
  leftMotor.run(RELEASE);
  rightMotor.run(RELEASE);
  delay(300);

  // Run both the motors backwards for 3 seconds
  leftMotor.run(BACKWARD);
  rightMotor.run(BACKWARD);
  delay(3000);

  // Pause for 10 seconds, then start the main loop over again
  leftMotor.run(RELEASE);
  rightMotor.run(RELEASE);
  delay(10000);
}
