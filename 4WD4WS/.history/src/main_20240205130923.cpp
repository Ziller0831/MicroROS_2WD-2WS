#include <Arduino.h>
#include <AccelStepper.h>
#include "pinSetup.h"

AccelStepper Rightmotor(RightStepper, STEP_R, DIR_R);

void setup()
{
  Serial.begin(115200);
  motor.setMaxSpeed(1000);
  motor.setAcceleration(60);
  motor.setSpeed(600);
  motor.moveTo(0);
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