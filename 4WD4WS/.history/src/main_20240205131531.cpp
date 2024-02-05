#include <Arduino.h>
#include <AccelStepper.h>
#include "pinSetup.h"

AccelStepper RightStepper(MotorInterfaceType_R, STEP_R, DIR_R);
AccelStepper LeftStepper(MotorInterfaceType_L, STEP_L, DIR_L);

void setup()
{
  Serial.begin(115200);
  RightStepper.setMaxSpeed(1000);
  RightStepper.setAcceleration(60);
  RightStepper.setSpeed(600);
  RightStepper.moveTo(0);
  RightStepper.setMaxSpeed(1000);
  RightStepper.setAcceleration(60);
  RightStepper.setSpeed(600);
  RightStepper.moveTo(0);
}

void loop()
{
  RightStepper.moveTo(8000);
  RightStepper.runToPosition();
  delay(1000);
  // Move back to zero:
  RightStepper.moveTo(0);
  RightStepper.runToPosition();
  delay(1000);
}