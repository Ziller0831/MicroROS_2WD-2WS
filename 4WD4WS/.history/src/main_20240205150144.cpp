#include <Arduino.h>
#include <AccelStepper.h>
#include "4WD4WS.h"

AccelStepper RightStepper(AccelStepper::DRIVER, STEP_R, DIR_R);
AccelStepper LeftStepper(AccelStepper::DRIVER, STEP_L, DIR_L);

int Pulse_per

void setup()
{
  pinMode(STEP_R, OUTPUT);
  pinMode(DIR_R, OUTPUT);
  pinMode(STEP_L, OUTPUT);
  pinMode(DIR_L, OUTPUT);

  Serial.begin(115200);

  RightStepper.setMaxSpeed(1000);
  RightStepper.setAcceleration(60);
  RightStepper.setSpeed(600);

  LeftStepper.setMaxSpeed(1000);
  LeftStepper.setAcceleration(60);
  LeftStepper.setSpeed(600);
}

void loop()
{
  if (RightStepper.currentPosition != 800)
    RightStepper.moveTo(8000);
  RightStepper.runToPosition();

}