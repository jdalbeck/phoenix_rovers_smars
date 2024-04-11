/*
  ESP32 (Wemos D1 R32) with TB6612FNG H-Bridge
  Bluetooth Control Test

  variable naming conventions

  lm = Left Motor
  rm = Right Motor
  d  = Direction Button
  lj = Left Joystick
  rj = Right Joystick
  b  = Action Button (bUp = Triangle, etc.)
  s  = Shoulder
  t  = Trigger
*/

// Include PS3 Controller library
#include <Ps3Controller.h>

// left motor
const int lmPwm = 12; // GPIO12
const int lmIn1 = 27; // GPIO27
const int lmIn2 = 14; // GPIO14
const int lmChannel = 0; // LEDC Channel

// right motor
const int rmPwm = 26; // GPIO26
const int rmIn1 = 17; // GPIO17
const int rmIn2 = 25; // GPIO25
const int rmChannel = 1; // LEDC Channel

// PWM properties
const int pwmFreq = 5000;
const int pwmResolution = 8;


// Variables to hold LED states
bool ledState = false;

// Callback Function for PS3 event handler
void notify() {

  // Triangle Button - LED2 toggle control
  if (Ps3.event.button_down.triangle) {
    ledState = !ledState;
    digitalWrite(LED_BUILTIN, ledState);
  }
}

// On Connection function
void onConnect() {
  // Print to Serial Monitor
  Serial.println("Connected.");
}


void setup() {

  // Setup Serial Monitor for testing+

  // Define PS3 Callback Function
  Ps3.attach(notify);
  // Define On Connection Function
  Ps3.attachOnConnect(onConnect);
  // Emulate console as specific MAC address (change as required)
  Ps3.begin("00:00:00:00:00:00");

  // set the motor control pins to outputs
  pinMode(lmIn1, OUTPUT);
  pinMode(lmIn2, OUTPUT);
  pinMode(rmIn1, OUTPUT);
  pinMode(rmIn2, OUTPUT);
  
  // attach the PWM channel to the GPIO to be controlled
  ledcSetup(lmChannel, pwmFreq, pwmResolution);
  ledcSetup(rmChannel, pwmFreq, pwmResolution);
  ledcAttachPin(lmPwm, lmChannel);
  ledcAttachPin(rmPwm, rmChannel);

  // Print to Serial Monitor
  Serial.println("Ready.");
}


void loop() {
  if (!Ps3.isConnected())
    return;
  delay(2000);
  
  // Set Motor A forward
  digitalWrite(lmIn1, HIGH);
  digitalWrite(lmIn2, LOW);

 // Set Motor B forward
  digitalWrite(rmIn1, HIGH);
  digitalWrite(rmIn2, LOW);
  
  // Set the motor speeds
  ledcWrite(lmChannel, 200);
  ledcWrite(rmChannel, 200);
}
