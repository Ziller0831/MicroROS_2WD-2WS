#include <Arduino.h>
#include <AccelStepper.h>
#include <MultiStepper.h>
#include "4WD4WS.h"

AccelStepper RightStepper(AccelStepper::DRIVER, STEP_R, DIR_R);
AccelStepper LeftStepper(AccelStepper::DRIVER, STEP_L, DIR_L);

//* 輪子轉一圈要的脈衝數
int Pulse_per_rev = 360/StepAngle * MicroStep * GearRatio;

void setup()
{
  pinMode(STEP_R, OUTPUT);
  pinMode(DIR_R, OUTPUT);
  pinMode(STEP_L, OUTPUT);
  pinMode(DIR_L, OUTPUT);

  Serial.begin(115200);

  RightStepper.setMaxSpeed(200.0);
  RightStepper.setAcceleration(200.0);
  RightStepper.moveTo(100);

  LeftStepper.setMaxSpeed(200.0);
  LeftStepper.setAcceleration(200.0);
  LeftStepper.moveTo(100);
}

void loop()
{
  if (RightStepper.distanceToGo() == 0)
    RightStepper.moveTo(-stepper1.currentPosition());
  if (LeftStepper.distanceToGo() == 0)
    LeftStepper.moveTo(-stepper2.currentPosition());
  stepper1.run();
  stepper2.run();
  }
}