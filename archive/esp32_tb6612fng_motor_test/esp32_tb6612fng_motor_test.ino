/*
  ESP32 (Wemos D1 R32) with TB6612FNG H-Bridge Test
*/

// Shift register pins
const int motorLatch = 19;
const int motorClock = 17;
const int motorEnable = 14;
const int motorData = 12;

// Motor A
const int pwmA = 12; // GPIO12
const int in1A = 27; // GPIO27
const int in2A = 14; // GPIO14
const int channelA = 0; // LEDC Channel

// Motor B
const int pwmB = 26; // GPIO26
const int in1B = 17; // GPIO17
const int in2B = 25; // GPIO25
const int channelB = 1; // LEDC Channel

// setting PWM properties
const int freq = 5000;
const int resolution = 8;

void setup() {
  // Set all the motor control pins to outputs
  //pinMode(pwmA, OUTPUT);
  //pinMode(pwmB, OUTPUT);
  pinMode(in1A, OUTPUT);
  pinMode(in2A, OUTPUT);
  pinMode(in1B, OUTPUT);
  pinMode(in2B, OUTPUT);
  
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
