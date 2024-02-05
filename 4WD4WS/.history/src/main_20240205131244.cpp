#include <Arduino.h>
#include <AccelStepper.h>
#include "pinSetup.h"

AccelStepper Rightstepper(MotorInterfaceType_R, STEP_R, DIR_R);

void setup()
{
  Serial.begin(115200);
  Rstepper.setMaxSpeed(1000);
  Rstepper.setAcceleration(60);
  Rstepper.setSpeed(600);
  Rstepper.moveTo(0);
}

void loop()
{
  Rstepper.moveTo(8000);
  Rstepper.runToPosition();
  delay(1000);
  // Move back to zero:
  Rstepper.moveTo(0);
  Rstepper.runToPosition();
  delay(1000);
}