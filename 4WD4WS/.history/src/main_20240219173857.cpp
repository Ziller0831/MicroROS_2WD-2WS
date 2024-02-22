#include "4WD4WS.h"
#include "Ackerman.h"

//* 輪子轉一圈要的脈衝數
int Pulse2Deg = 360 / ((360 / StepAngle) * MicroStep * GearRatio); // (360/1.8)*16*10 = 32000  1 pulse = 0.01125 degree

void setup()
{
  pinMode(STEP_R, OUTPUT);
  pinMode(DIR_R, OUTPUT);
  pinMode(STEP_L, OUTPUT);
  pinMode(DIR_L, OUTPUT);

  Serial.begin(115200);

  RightStepper.setMaxSpeed(3200);
  // RightStepper.setAcceleration(3200 / 2);
  RightStepper.setSpeed(1600);

  LeftStepper.setMaxSpeed(3200);
  // LeftStepper.setAcceleration(3200 / 2);
  LeftStepper.setSpeed(1600);

  steppers.addStepper(RightStepper);
  steppers.addStepper(LeftStepper);

  Serial.println("Setup Finish");
}

void loop()
{
  Angle = 45;

  Pulse[0] = Angle / Pulse2Deg;
  Pulse[1] = Angle / Pulse2Deg;

  // Serial.println(Pulse);

  steppers.moveTo(Pulse);
  steppers.runSpeedToPosition(); // Blocks until all are in positions
  delay(1000);
}


