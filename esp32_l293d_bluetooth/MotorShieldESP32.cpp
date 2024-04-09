#include "MotorShieldESP32.h"
static uint8_t latch_state;

// ------------------------------------------------
// MOTOR SHIELD (Shift Register controls)
// ------------------------------------------------
espMotorShield::espMotorShield(void) {
    TimerInitalized = false;
}

void espMotorShield::enable(void) {

  // Set all the shift register pins to outputs
  pinMode(MOTORLATCH, OUTPUT);
  pinMode(MOTORCLK, OUTPUT);
  pinMode(MOTORENABLE, OUTPUT);
  pinMode(MOTORDATA, OUTPUT);

  // "Reset" the shift register
  latch_state = 0;
  latch_tx();

  // enable the chip outputs (pull ENA low)
  digitalWrite(MOTORENABLE, LOW);
}

void espMotorShield::latch_tx(void) {
  uint8_t i;

  // Set pins for shift register to default value (low);
  digitalWrite(MOTORDATA, LOW);
  digitalWrite(MOTORLATCH, LOW);

  for (i=0; i<8; i++) {
    digitalWrite(MOTORCLK, LOW);

    if (latch_state & _BV(7-i)) {
      digitalWrite(MOTORDATA, HIGH);
    } else {
      digitalWrite(MOTORDATA, LOW);
    }
    digitalWrite(MOTORCLK, HIGH);
  }
  digitalWrite(MOTORLATCH, HIGH);
}



// ------------------------------------------------
// MOTOR
// ------------------------------------------------

static espMotorShield EMS;

espMotor::espMotor(uint8_t num, uint16_t freq, uint8_t resolution) {
  motornum = num;
  pwmfreq = freq;
  pwmres = resolution;

  EMS.enable();

  switch (num) {
  case 1:
    latch_state &= ~_BV(MOTOR1_A) & ~_BV(MOTOR1_B); // set both motor pins to 0
    EMS.latch_tx();
    ledcSetup(MOTOR1LEDC, pwmfreq, pwmres);
    ledcAttachPin(MOTOR1GPIO, MOTOR1LEDC);
    break;
  case 2:
    latch_state &= ~_BV(MOTOR2_A) & ~_BV(MOTOR2_B); // set both motor pins to 0
    EMS.latch_tx();
    ledcSetup(MOTOR2LEDC, pwmfreq, pwmres);
    ledcAttachPin(MOTOR2GPIO, MOTOR2LEDC);
    break;
  case 3:
    latch_state &= ~_BV(MOTOR3_A) & ~_BV(MOTOR3_B); // set both motor pins to 0
    EMS.latch_tx();
    ledcSetup(MOTOR3LEDC, pwmfreq, pwmres);
    ledcAttachPin(MOTOR3GPIO, MOTOR3LEDC);
    break;
  case 4:
    latch_state &= ~_BV(MOTOR4_A) & ~_BV(MOTOR4_B); // set both motor pins to 0
    EMS.latch_tx();
    ledcSetup(MOTOR4LEDC, pwmfreq, pwmres);
    ledcAttachPin(MOTOR4GPIO, MOTOR4LEDC);
    break;
  }
}

void espMotor::run(uint8_t cmd) {
  uint8_t a, b;
  switch (motornum) {
  case 1:
    a = MOTOR1_A; b = MOTOR1_B; break;
  case 2:
    a = MOTOR2_A; b = MOTOR2_B; break;
  case 3:
    a = MOTOR3_A; b = MOTOR3_B; break;
  case 4:
    a = MOTOR4_A; b = MOTOR4_B; break;
  default:
    return;
  }
  
  switch (cmd) {
  case FORWARD:
    latch_state |= _BV(a);
    latch_state &= ~_BV(b); 
    EMS.latch_tx();
    break;
  case BACKWARD:
    latch_state &= ~_BV(a);
    latch_state |= _BV(b); 
    EMS.latch_tx();
    break;
  case RELEASE:
    latch_state &= ~_BV(a);     // A and B both low
    latch_state &= ~_BV(b); 
    EMS.latch_tx();
    break;
  }
}

void espMotor::setSpeed(int speed) {
  switch (motornum) {
  case 1:
    ledcWrite(MOTOR1LEDC, speed); break;
  case 2:
    ledcWrite(MOTOR2LEDC, speed); break;
  case 3:
    ledcWrite(MOTOR3LEDC, speed); break;
  case 4:
    ledcWrite(MOTOR4LEDC, speed); break;
  }
}