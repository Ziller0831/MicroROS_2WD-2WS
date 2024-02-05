#include <Arduino.h>
#include <AccelStepper.h>
#include "pinSetup.h"

AccelStepper Rstepper(RightStepper, STEP_R, DIR_R);

void setup()
{
  Serial.begin(115200);
  RStepper.setMaxSpeed(1000);
  RStepper.setAcceleration(60);
  RStepper.setSpeed(600);
  RStepper.moveTo(0);
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