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

  RightStepper.setMaxSpeed(Pulse_per_rev * 1.5);
  RightStepper.setAcceleration(Pulse_per_rev/4);
  RightStepper.setSpeed(Pulse_per_rev);

  LeftStepper.setMaxSpeed(Pulse_per_rev * 1.5);
  LeftStepper.setAcceleration(Pulse_per_rev/4);

  steppers.addStepper(RightStepper);
  steppers.addStepper(LeftStepper);
}

void loop()
{
  long positions[2]; // Array of desired stepper positions

  positions[0] = 1000;
  positions[1] = 50;
  steppers.moveTo(positions);
  steppers.runSpeedToPosition(); // Blocks until all are in position
  delay(1000);

  // Move to a different coordinate
  positions[0] = -100;
  positions[1] = 100;
  steppers.moveTo(positions);
  steppers.runSpeedToPosition(); // Blocks until all are in position
  delay(1000);
}