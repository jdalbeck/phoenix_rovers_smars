/*
  ESP32 (Wemos D1 R32) with L293 Motor Shield Test
*/

// Shift register pins
const int motorLatch = 19;
const int motorClock = 17;
const int motorEnable = 14;
const int motorData = 12;

// Motor A
const int pwmA = 23;
const int channelA = 0; // LEDC Channel

// Motor B
const int pwmB = 25; // GPIO26
const int channelB = 1; // LEDC Channel

// setting PWM properties
const int freq = 5000;
const int resolution = 8;

//Shift register instructions.  The leftmost bit corresponds to the second input for each motor, so the pattern is lmIn2 lmIn1 lmIn2 lmIn1
const byte lmForward = 0b1100;
const byte lmBackward = 0b1010;
const byte rmForward = 0b0011;
const byte rmBackward = 0b0101;

void setShiftRegister(byte settingsByte) {
  shiftOut(motorData, motorClock, MSBFIRST, settingsByte);
  delayMicroseconds(5);    // For safety, not really needed.
  digitalWrite(motorLatch, HIGH);
  delayMicroseconds(5);    // For safety, not really needed.
  digitalWrite(motorLatch, LOW);
}

void setup() {

  // Set all the shift register pins to outputs
  pinMode(motorLatch, OUTPUT);
  pinMode(motorClock, OUTPUT);
  pinMode(motorEnable, OUTPUT);
  pinMode(motorData, OUTPUT);

  // Set pins for shift register to default value (low);
  digitalWrite(motorData, LOW);
  digitalWrite(motorLatch, LOW);
  digitalWrite(motorClock, LOW);
  digitalWrite(motorEnable, LOW);

  // attach the channel to the GPIO to be controlled
  ledcSetup(channelA, freq, resolution);
  ledcSetup(channelB, freq, resolution);
  ledcAttachPin(pwmA, channelA);
  ledcAttachPin(pwmB, channelB);
}

void loop() {
  
  // Set the motor speeds
  ledcWrite(channelA, 200);
  ledcWrite(channelB, 200);

  //let's try a couple different settings

  //rmBackward
  setShiftRegister(0b00010000);
  delay(2000);
  //lmForward
  setShiftRegister(0b00001000);
  delay(2000);
  //lmBackward
  setShiftRegister(0b00000100);
  delay(2000);
  //rmForward
  setShiftRegister(0b00000010);
  delay(2000);

}
