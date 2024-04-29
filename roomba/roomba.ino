/*
  Phoenix Rovers SMARS
  Roomba project

  Start driving forward at medium speed. If an obstacle is detected nearby, stop and turn in a random direction, then repeat.
  Bonus points for changing the speed every time it turns!


  HINTS:

    It may help to pause for 1 second in between movements, to make sure that movements are not affecting the sonar readings.  Here is
    a high level overview of the loop "algorithm":
       - Move forward
       - Get distance from sonar
       - If an obstacle is detected 2-5 inches away:
          - Pause for 1 second
          - Pick a random direction (left or right) and set the motors to spin in that direction
          - Spin the motors for a random turning duration (2-10 seconds?)
          - Pause for 1 second
          - Pick a new speed randomly between 80 and 220
       - Delay 500 milliseconds

    Copy the code from our "motor_test" project to set up the motors and figure out how to move them. Also look at the code from
    Ryan Ezra and Colin (ryan_ezra_colin_code) because they already did a similar algorithm.

    Picking a direction: Use "random(0,10)" to get a random number between 0 and 10.  If that number is less than 5, turn left.
        If the number is greater than 5, turn right.  In order to turn left, spin the right motor forward and the left motor backward.
        To turn right, spin the left motor forward and the right motor backward.
    Picking a random turning amount: Use the "random(2,10)" function to get a random number between 2 and 10.  Delay for that many seconds
        and then stop the motors.  Remember to reset the motors to both go forwards after it finishes turning!
        Remember, 1 second is 1000 milliseconds, and the "delay" function only accepts milliseconds.  Therefore you must multiply the
        random number by 1000 to get milliseconds (or instead you could use random(2000, 10000)).
        However, the "random" function returns a floating point variable (a number with decimals).  You will need to "round" this to the
        nearest whole number (integer). There is a "round" function in the "math.h" library.  Can you figure out how to include that library?
    Picking a random speed: Do the same thing as you did to pick a random turning amount, but keep the random number between 80 and 220.
*/

// This uses Serial Monitor to display Range Finder distance readings

// Include NewPing Library
#include <NewPing.h>


// Arduino Settings
#if defined(__AVR__)
  #define SERIALBAUD 9600
  #define TRIGGER_PIN 10
  #define ECHO_PIN 9

// Wemos D1 R32 Settings
#elif defined(ARDUINO_D1_UNO32)
  #define SERIALBAUD 115200
  #define TRIGGER_PIN 5
  #define ECHO_PIN 13
#endif

#define MAX_DISTANCE 400
 
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

float distance;

void setup() {
  Serial.begin (SERIALBAUD);
}

void loop() {
   
  distance = sonar.ping_in();
  
  // Send results to Serial Monitor
  Serial.print("Distance = ");
  if (distance >= 400 || distance <= 2) {
    Serial.println("Out of range");
  }
  else {
    Serial.print(distance);
    Serial.println(" in");
    delay(500);
  }
  delay(500);
}