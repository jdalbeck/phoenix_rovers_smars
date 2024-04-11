# phoenix_rovers_smars
SMARS code for Phoenix Rovers robotics team.

## 3D Printer Files
STL Files can be found here: https://www.thingiverse.com/thing:2662828

Parts to print:
 - (1) Chassis SL
 - (1) Holding Board 9V
 - (1) Ultrasonic 1
 - (1) Ultrasonic 2b
 - (2) Master Wheel
 - (2) Slave Wheel SL
 - (32) Mechanical Track (Flexible filament like TPU is best, if you have it)

## Electronic Parts
Links are for example pricing may change and shopping around may be needed.  These links would provide enough parts for 3 robots.
 - Arduino Uno or [Wemos D1 R32 (recommended)](https://a.co/d/9RCvCmO) (3 for $19)
 - [Arduino Motor Shield v1 (L293D Shield)](https://a.co/d/5au71xM) (3 for $10)
 - (2) [N20 Motors 6v, Slow speed (~100rpm)](https://a.co/d/bgSqQUk) (6 for $20) (2 motors per robot)
 - [Ultrasonic Sensor HC-SR04](https://a.co/d/4brL1ym) (5 for $10)

## Bluetooth Controller (Optional)
The Wemos D1 R32 (ESP32) development board has a built-in bluetooth radio, which we can pair with pretty much any Bluetooth game controller.  An old PlayStation 3 controller is ideal, but should also work with Nintendo Switch, XBox, 8bitdo, and other controllers.  PS3 Clone controllers like [this one](https://a.co/d/9IKPwNE) also work fine.

## Coding Setup
 1. [Download](https://www.arduino.cc/en/software) and install Arduino IDE (recommend "MSI installer" version for Windows)
 2. For the Wemos D1 board, [follow instructions](https://bluepad32.readthedocs.io/en/latest/plat_arduino/) under "Option A" to add ESP32 and Bluepad32 board packages to Board Manager and install ESP32 and Bluepad32 boards.
 3. For the Wemos D1 board, when selecting a board target, use "WEMOS D1 R32" in the board dropdown list.
 4. Download our [custom motor library](https://github.com/jdalbeck/Adafruit-Motor-Shield-library).  Click the "Code" dropdown button, then click "Download ZIP".  Extract the folder "Adafruit-Motor-Shield-library" to your Arduino IDE "libraries" folder. (Alternatively you can use Git to check out the repository to the "libraries" folder to make sure you can easily keep it in sync if there are any changes).