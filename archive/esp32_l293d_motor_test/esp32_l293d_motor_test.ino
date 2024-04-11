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


// shiftWrite helper function
void shiftWrite(int output, int high_low) {
  static int latch_copy;
  static int shift_register_initialized = false;

  // Do the initialization on the fly, the first time it is used.
  if (!shift_register_initialized) {
    // Set all the shift register pins to outputs
    pinMode(motorLatch, OUTPUT);
    pinMode(motorClock, OUTPUT);
    pinMode(motorEnable, OUTPUT);
    pinMode(motorData, OUTPUT);

    // Set pins for shift register to default value (low);
    digitalWrite(motorData, LOW);
    digitalWrite(motorLatch, LOW);
    digitalWrite(motorClock, LOW);
    // Enable the shift register, set Enable pin Low.
    digitalWrite(motorEnable, LOW);

    // start with all outputs (of the shift register) low
    latch_copy = 0;

    shift_register_initialized = true;
  }

  // The defines HIGH and LOW are 1 and 0.
  bitWrite(latch_copy, output, high_low);

  // Use the default Arduino 'shiftOut()' function to
  // shift the bits with the MOTORCLK as clock pulse.
  // The 74HC595 shiftregister wants the MSB first.
  // After that, generate a latch pulse with MOTORLATCH.
  shiftOut(motorData, motorClock, MSBFIRST, latch_copy);
  delayMicroseconds(5);    // For safety, not really needed.
  digitalWrite(motorLatch, HIGH);
  delayMicroseconds(5);    // For safety, not really needed.
  digitalWrite(motorLatch, LOW);
}


void setup() {
  // attach the channel to the GPIO to be controlled
  ledcSetup(channelA, freq, resolution);
  ledcSetup(channelB, freq, resolution);
  ledcAttachPin(pwmA, channelA);
  ledcAttachPin(pwmB, channelB);
}

void loop() {
  // Set Motor A forward
  digitalWrite(in1A, HIGH);
  digitalWrite(in2A, LOW);

 // Set Motor B forward
  digitalWrite(in1B, HIGH);
  digitalWrite(in2B, LOW);
  
  // Set the motor speeds
  ledcWrite(channelA, 200);
  ledcWrite(channelB, 200);
}
