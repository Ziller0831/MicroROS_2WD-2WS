#include <Arduino.h>
#include <AccelStepper.h>
#include "pinSetup.h"

// AccelStepper stepper = AccelStepper(1, Pul, Dir);

void setup()
{
  pinMode(Pul, OUTPUT);
  pinMode(Dir, OUTPUT);
}
void loop()
{
  for (int i = 0; i < 6400; i++) // Forward 5000 steps
  {
    digitalWrite(Dir, LOW);
    digitalWrite(Pul, HIGH);
    delayMicroseconds(50);
    digitalWrite(Pul, LOW);
    delayMicroseconds(50);
  }
  for (int i = 0; i < 6400; i++) // Backward 5000 steps
  {
    digitalWrite(Dir, HIGH);
    digitalWrite(Pul, HIGH);
    delayMicroseconds(50);
    digitalWrite(PUL, LOW);
    delayMicroseconds(50);
  }
}