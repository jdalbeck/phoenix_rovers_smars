/*
  ESP32 (Wemos D1 R32) with L293 Motor Shield Test

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

#include <Bluepad32.h>
#include "MotorShieldESP32.h"

ControllerPtr myControllers[BP32_MAX_GAMEPADS];

// Define motors
espMotor lm(1);
espMotor rm(2);

// Variables for joystick values
int rightX = 0;
int rightY = 0;

// Variables to hold LED states
bool ledState = false;

// This callback gets called any time a new gamepad is connected.
// Up to 4 gamepads can be connected at the same time.
void onConnectedController(ControllerPtr ctl) {
    bool foundEmptySlot = false;
    for (int i = 0; i < BP32_MAX_GAMEPADS; i++) {
        if (myControllers[i] == nullptr) {
            Serial.printf("CALLBACK: Controller is connected, index=%d\n", i);
            // Additionally, you can get certain gamepad properties like:
            // Model, VID, PID, BTAddr, flags, etc.
            ControllerProperties properties = ctl->getProperties();
            Serial.printf("Controller model: %s, VID=0x%04x, PID=0x%04x\n", ctl->getModelName().c_str(), properties.vendor_id,
                           properties.product_id);
            myControllers[i] = ctl;
            foundEmptySlot = true;
            break;
        }
    }
    if (!foundEmptySlot) {
        Serial.println("CALLBACK: Controller connected, but could not found empty slot");
    }
}

void onDisconnectedController(ControllerPtr ctl) {
    bool foundController = false;

    for (int i = 0; i < BP32_MAX_GAMEPADS; i++) {
        if (myControllers[i] == ctl) {
            Serial.printf("CALLBACK: Controller disconnected from index=%d\n", i);
            myControllers[i] = nullptr;
            foundController = true;
            break;
        }
    }

    if (!foundController) {
        Serial.println("CALLBACK: Controller disconnected, but not found in myControllers");
    }
}

void dumpGamepad(ControllerPtr ctl) {
    Serial.printf(
        "idx=%d, dpad: 0x%02x, buttons: 0x%04x, axis L: %4d, %4d, axis R: %4d, %4d, brake: %4d, throttle: %4d, "
        "misc: 0x%02x, gyro x:%6d y:%6d z:%6d, accel x:%6d y:%6d z:%6d\n",
        ctl->index(),        // Controller Index
        ctl->dpad(),         // D-pad
        ctl->buttons(),      // bitmask of pressed buttons
        ctl->axisX(),        // (-511 - 512) left X Axis
        ctl->axisY(),        // (-511 - 512) left Y axis
        ctl->axisRX(),       // (-511 - 512) right X axis
        ctl->axisRY(),       // (-511 - 512) right Y axis
        ctl->brake(),        // (0 - 1023): brake button
        ctl->throttle(),     // (0 - 1023): throttle (AKA gas) button
        ctl->miscButtons(),  // bitmask of pressed "misc" buttons
        ctl->gyroX(),        // Gyro X
        ctl->gyroY(),        // Gyro Y
        ctl->gyroZ(),        // Gyro Z
        ctl->accelX(),       // Accelerometer X
        ctl->accelY(),       // Accelerometer Y
        ctl->accelZ()        // Accelerometer Z
    );
}

void processGamepad(ControllerPtr ctl) {
  uint8_t lmPwm;
  uint8_t rmPwm;
  uint8_t motorDir;
  int ljX;
  int ljY;

  // Triangle Button - LED toggle control
  if (ctl->x()) {
    ledState = !ledState;
    digitalWrite(LED_BUILTIN, ledState);
  }

  // Get Joystick value
  ljX = ctl->axisX();        // (-511 - 512) left X Axis
  ljY = ctl->axisY();        // (-511 - 512) left Y axis
 
  //Determine direction from Y axis position
  if (ljY < 0) {
    // Direction is forward
    motorDir = FORWARD;
  } else {
    // Direction is reverse
    motorDir = BACKWARD;
  }
 
  // Convert joystick values to positive 0 - 255
  int speedX = ((abs(ljX)-1) / 2);
  int speedY = ((abs(ljY)-1) / 2);
 
  // Factor in the X axis value to determine motor speeds (assume Motor A is Left motor going forward)
  if (ljX < -10) {
    // Motor B faster than Motor A
    lmPwm = speedY - speedX;
    rmPwm = speedY + speedX;
 
  } else if (ljX > 10) {
    // Motor A faster than Motor B
    lmPwm = speedY + speedX;
    rmPwm = speedY - speedX;
 
  } else {
    // Control is in middle, both motors same speed
    lmPwm = speedY;
    rmPwm = speedY;
  }
 
  // Ensure that speed values remain in range of 0 - 255
  lmPwm = constrain(lmPwm, 0, 255);
  rmPwm = constrain(rmPwm, 0, 255);
 
  // Drive the motors
  lm.setSpeed(lmPwm);
  rm.setSpeed(rmPwm);
  lm.run(motorDir);
  rm.run(motorDir);
 
  // Print to Serial Monitor
  Serial.print("X value = ");
  Serial.print(ljX);
  Serial.print(" - Y value = ");
  Serial.print(ljY);
  Serial.print(" - Motor A = ");
  Serial.print(lmPwm);
  Serial.print(" - Motor B = ");
  Serial.println(rmPwm);


    // Another way to query controller data is by getting the buttons() function.
    // See how the different "dump*" functions dump the Controller info.
    //dumpGamepad(ctl);
}


void processControllers() {
    for (auto myController : myControllers) {
        if (myController && myController->isConnected() && myController->hasData()) {
            if (myController->isGamepad()) {
                processGamepad(myController);
            } else {
                Serial.println("Unsupported controller");
            }
        }
    }
}

// Arduino setup function. Runs in CPU 1
void setup() {
  Serial.begin(115200);
  Serial.printf("Firmware: %s\n", BP32.firmwareVersion());
  const uint8_t* addr = BP32.localBdAddress();
  Serial.printf("BD Addr: %2X:%2X:%2X:%2X:%2X:%2X\n", addr[0], addr[1], addr[2], addr[3], addr[4], addr[5]);

  // Setup the Bluepad32 callbacks
  BP32.setup(&onConnectedController, &onDisconnectedController);

  // "forgetBluetoothKeys()" should be called when the user performs
  // a "device factory reset", or similar.
  // Calling "forgetBluetoothKeys" in setup() just as an example.
  // Forgetting Bluetooth keys prevents "paired" gamepads to reconnect.
  // But it might also fix some connection / re-connection issues.
  BP32.forgetBluetoothKeys();

  // Enables mouse / touchpad support for gamepads that support them.
  // When enabled, controllers like DualSense and DualShock4 generate two connected devices:
  // - First one: the gamepad
  // - Second one, which is a "virtual device", is a mouse.
  // By default, it is disabled.
  BP32.enableVirtualDevice(false);

  // turn on motor
  lm.setSpeed(100);
  rm.setSpeed(100);
  lm.run(RELEASE);
  rm.run(RELEASE);

  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
}

// Arduino loop function. Runs in CPU 1.
void loop() {
    // This call fetches all the controllers' data.
    // Call this function in your main loop.
    bool dataUpdated = BP32.update();
    if (dataUpdated)
        processControllers();

    // The main loop must have some kind of "yield to lower priority task" event.
    // Otherwise, the watchdog will get triggered.
    // If your main loop doesn't have one, just add a simple `vTaskDelay(1)`.
    // Detailed info here:
    // https://stackoverflow.com/questions/66278271/task-watchdog-got-triggered-the-tasks-did-not-reset-the-watchdog-in-time

    //     vTaskDelay(1);
    delay(150);
}
