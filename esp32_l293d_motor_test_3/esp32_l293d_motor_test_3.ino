/*
  ESP32 (Wemos D1 R32) with L293 Motor Shield Test
*/
#include "MotorShieldESP32.h"
espMotor motor1(1);
espMotor motor2(2);

void setup() {

  // turn on motor
  motor1.setSpeed(200);
  motor2.setSpeed(200);
  motor1.run(FORWARD);
  motor2.run(FORWARD);
}

void loop() {
}
