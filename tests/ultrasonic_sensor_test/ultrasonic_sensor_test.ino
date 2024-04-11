/*
  Ultrasonic Sensor Test

  Detects the distance of any object immediately in front of the sensor
  and displays the measurements on the serial monitor

  See https://randomnerdtutorials.com/complete-guide-for-ultrasonic-sensor-hc-sr04/
*/

// Arduino Settings
#if defined(__AVR__)
  #define SERIALBAUD 9600
  #define TRIGPIN 10
  #define ECHOPIN 9

// Wemos D1 R32 Settings
#elif defined(ARDUINO_D1_UNO32)
  #define SERIALBAUD 115200
  #define TRIGPIN 5
  #define ECHOPIN 13
#endif

// Setup section
void setup() {

  // Serial monitor setup
  Serial.begin(SERIALBAUD);

  // Ultrasonic sensor setup
  pinMode(TRIGPIN, OUTPUT);
  pinMode(ECHOPIN, INPUT);
}

// Main loop section
void loop() {
  long duration, cm, inches;
  
  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(TRIGPIN, LOW);
  delayMicroseconds(5);
  digitalWrite(TRIGPIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGPIN, LOW);
 
  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(ECHOPIN, INPUT);
  duration = pulseIn(ECHOPIN, HIGH);
 
  // Convert the time into a distance
  cm = (duration/2) / 29.1;     // Divide by 29.1 or multiply by 0.0343
  inches = (duration/2) / 74;   // Divide by 74 or multiply by 0.0135

  // Print the current distance
  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
}
