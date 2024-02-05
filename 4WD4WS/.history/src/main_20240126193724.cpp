#include <Arduino.h>
#include <AccelStepper.h>
#include "pinSetup.h"

AccelStepper stepper = AccelStepper(1, Pul, Dir);

void setup()
{
  stepper.setMaxSpeed(1000);
  stepper.setAcceleration(500);
}

void loop()
{
  for (int i = 0; i < 6400; i++) // Forward 5000 steps
  {
    digitalWrite(DIR, LOW);
    digitalWrite(ENA, HIGH);
    digitalWrite(PUL, HIGH);
    delayMicroseconds(50);
    digitalWrite(PUL, LOW);
    delayMicroseconds(50);
  }
  for (int i = 0; i < 6400; i++) // Backward 5000 steps
  {
    digitalWrite(DIR, HIGH);
    digitalWrite(ENA, HIGH);
    digitalWrite(PUL, HIGH);
    delayMicroseconds(50);
    digitalWrite(PUL, LOW);
    delayMicroseconds(50);
  }
}