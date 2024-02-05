#include <Arduino.h>
#include <AccelStepper.h>
#include <MultiStepper.h>

const int DIR_R = 12;
const int STEP_R = 14;
AccelStepper RightStepper(AccelStepper::DRIVER, STEP_R, DIR_R);

const int DIR_L = 2;
const int STEP_L = 15;
AccelStepper LeftStepper(AccelStepper::DRIVER, STEP_L, DIR_L);

const float StepAngle = 1.8;
const int MicroStep = 1;
const int GearRatio = 10;       // 10:1