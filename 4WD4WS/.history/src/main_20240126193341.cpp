#include <Arduino.h>
#include <AccelStepper.h>
#include "pinSetup.h"

AccelStepper stepper = AccelStepper(motorInterfaceType, stepPin, dirPin);

void setup()
{
  stepper.setMaxSpeed(1000);
  stepper.setAcceleration(500);
}

void loop()
{
  stepper.moveTo(8000);
  stepper.runToPosition();
  delay(1000);
  // Move back to zero:
  stepper.moveTo(0);
  stepper.runToPosition();
  delay(1000);
}