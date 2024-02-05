#include <Arduino.h>
#include <AccelStepper.h>
#include "pinSetup.h"

AccelStepper RStepper(RightStepper, STEP_R, DIR_R);

void setup()
{
  Serial.begin(115200);
  RightStepper.setMaxSpeed(1000);
  RightStepper.setAcceleration(60);
  RightStepper.setSpeed(600);
  RightStepper.moveTo(0);
}

void loop()
{
  motor.moveTo(8000);
  motor.runToPosition();
  delay(1000);
  // Move back to zero:
  motor.moveTo(0);
  motor.runToPosition();
  delay(1000);
}