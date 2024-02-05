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

  RightStepper.setMaxSpeed(3200);
  RightStepper.setAcceleration(Pulse_per_rev/2);
  // RightStepper.setSpeed(200);

  LeftStepper.setMaxSpeed(Pulse_per_rev);
  LeftStepper.setAcceleration(Pulse_per_rev/2);
  // LeftStepper.setSpeed(200);

  steppers.addStepper(RightStepper);
  steppers.addStepper(LeftStepper);
}

void loop()
{
  long positions[2]; // Array of desired stepper positions

  positions[0] = Pulse_per_rev*10;
  positions[1] = Pulse_per_rev*5;
  steppers.moveTo(positions);
  steppers.run(); // Blocks until all are in position
  delay(1000);

  // Move to a different coordinate
  positions[0] = -Pulse_per_rev * 5;
  positions[1] = -Pulse_per_rev * 10;
  steppers.moveTo(positions);
  steppers.runSpeedToPosition(); // Blocks until all are in position
  delay(1000);
}


