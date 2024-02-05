#include <Arduino.h>
#include <AccelStepper.h>
#include "pinSetup.h"

AccelStepper motor(motorInterfaceType, STEP, DIR);

void setup()
{
  Serial.begin(115200);
  motor.setMaxSpeed(1000);
  motor.setAcceleration(60);
  motor.setSpeed(200);
  motor.moveTo(200);
}

void loop()
{
  if (motor.distanceToGo() == 0)
  {
    motor.moveTo(-motor.currentPosition());
    Serial.println("Rotating Motor in opposite direction...");
  }
  motor.run();
}