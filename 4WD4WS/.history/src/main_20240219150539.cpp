#include "4WD4WS.h"
#include "Ackerman.h"

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
}

void loop()
{
  long positions[2]; // Array of desired stepper positions

  if(Serial.available() > 0){
    char receivedChar = Serial.parseInt();
  }

  positions[0] = Pulse_per_rev/8;
  positions[1] = Pulse_per_rev/8;
  steppers.moveTo(positions);
  steppers.runSpeedToPosition(); // Blocks until all are in position
  delay(1000);

  // Move to a different coordinate
  positions[0] = -Pulse_per_rev / 8;
  positions[1] = -Pulse_per_rev / 8;
  steppers.moveTo(positions);
  steppers.runSpeedToPosition(); // Blocks until all are in position
  delay(1000);
}


