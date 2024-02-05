#include <Arduino.h>
#include <AccelStepper.h>
#include "pinSetup.h"

AccelStepper RightStepper(AccelStepper::DRIVER, STEP_R, DIR_R);
AccelStepper LeftStepper(AccelStepper::DRIVER, STEP_L, DIR_L);

void setup()
{
  pinMode(STEP_R, OUTPUT);
  pinMode(DIR_R, OUTPUT);
  pinMode(STEP_L, OUTPUT);
  pinMode(DIR_L, OUTPUT)
  Serial.begin(115200);

  RightStepper.setMaxSpeed(1000);
  RightStepper.setAcceleration(60);
  RightStepper.setSpeed(600);
  RightStepper.moveTo(0);     // 設定絕對位置

  LeftStepper.setMaxSpeed(1000);
  LeftStepper.setAcceleration(60);
  LeftStepper.setSpeed(600);
  LeftStepper.moveTo(0);
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