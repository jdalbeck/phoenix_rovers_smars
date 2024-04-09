#ifndef MOTOR_SHIELD_ESP32_H
#define MOTOR_SHIELD_ESP32_H
#include <Arduino.h>

// Shift Register Pins
#define MOTORLATCH 19
#define MOTORCLK 17
#define MOTORENABLE 14
#define MOTORDATA 12

// Motor Pins and LEDC Channels
#define MOTOR1GPIO 23
#define MOTOR1LEDC 0
#define MOTOR2GPIO 25
#define MOTOR2LEDC 1
#define MOTOR3GPIO 16
#define MOTOR3LEDC 2
#define MOTOR4GPIO 27
#define MOTOR4LEDC 3

// setting PWM properties
#define PWM_FREQUENCY 5000
#define PWM_RESOLUTION 8

// Bit positions in the 74HCT595 shift register output
#define MOTOR1_A 2
#define MOTOR1_B 3
#define MOTOR2_A 1
#define MOTOR2_B 4
#define MOTOR4_A 0
#define MOTOR4_B 6
#define MOTOR3_A 5
#define MOTOR3_B 7

// Constants that the user passes in to the motor calls
#define FORWARD 1
#define BACKWARD 2
#define BRAKE 3
#define RELEASE 4

class espMotorShield
{
  public:
    espMotorShield(void);
    void enable(void);
    friend class espMotor;
    void latch_tx(void);
    uint8_t TimerInitalized;
};

class espMotor
{
 public:
  espMotor(uint8_t motornum, uint16_t freq = PWM_FREQUENCY, uint8_t resolution = PWM_RESOLUTION);
  void run(uint8_t);
  void setSpeed(int);

 private:
  uint8_t motornum, pwmfreq, pwmres;
};

#endif