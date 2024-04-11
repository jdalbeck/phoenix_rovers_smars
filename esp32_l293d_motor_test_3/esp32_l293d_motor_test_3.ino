/*
  L293 Motor Shield Test
  Should work with both Arduino and ESP32
  Requires MotorShield library copied to Arduino IDE Libraries folder
*/
#include <MotorShield.h>
Motor leftMotor(1);
Motor rightMotor(2);

void setup() {
  Serial.begin(9600);
  // turn on motor
  leftMotor.setSpeed(100);
  rightMotor.setSpeed(100);
  leftMotor.run(RELEASE);
  rightMotor.run(RELEASE);
}

void loop() {
  Serial.println("Running now");
  leftMotor.run(FORWARD);
  rightMotor.run(FORWARD);
  delay(3000);
  leftMotor.run(RELEASE);
  rightMotor.run(RELEASE);
  delay(300);
  leftMotor.run(BACKWARD);
  rightMotor.run(BACKWARD);
  delay(3000);
  leftMotor.run(RELEASE);
  rightMotor.run(RELEASE);
  delay(10000);
}
