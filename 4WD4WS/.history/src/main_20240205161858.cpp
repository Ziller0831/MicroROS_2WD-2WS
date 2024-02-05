#include "4WD4WS.h"

//* 輪子轉一圈要的脈衝數
int Pulse_per_rev = 360/StepAngle * MicroStep;

void setup()
{
  pinMode(STEP_R, OUTPUT);
  pinMode(DIR_R, OUTPUT);
  pinMode(STEP_L, OUTPUT);
  pinMode(DIR_L, OUTPUT);

  Serial.begin(115200);

  RightStepper.setMaxSpeed(200 * 1.5);
  RightStepper.setAcceleration(200/4);
  RightStepper.setSpeed(200);

  LeftStepper.setMaxSpeed(200 * 1.5);
  LeftStepper.setAcceleration(200/4);
  LeftStepper.setSpeed(200);

  steppers.addStepper(RightStepper);
  steppers.addStepper(LeftStepper);
}

void loop()
{
  long positions[2]; // Array of desired stepper positions

  positions[0] = Pulse_per_rev*1.5;
  positions[1] = Pulse_per_rev*2;
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