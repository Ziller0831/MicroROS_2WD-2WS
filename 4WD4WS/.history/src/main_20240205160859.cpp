#include "4WD4WS.h"

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

  LeftStepper.setMaxSpeed(200.0);
  LeftStepper.setAcceleration(200.0);

  steppers.addStepper(stepper1);
  steppers.addStepper(stepper2);
}

void loop()
{
  if (RightStepper.distanceToGo() == 0)
    RightStepper.moveTo(-RightStepper.currentPosition());
  if (LeftStepper.distanceToGo() == 0)
    LeftStepper.moveTo(-LeftStepper.currentPosition());
  RightStepper.run();
  LeftStepper.run();
}