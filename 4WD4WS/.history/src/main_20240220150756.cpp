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
  RightStepper.setSpeed(1600);
  LeftStepper.setMaxSpeed(3200);
  LeftStepper.setSpeed(1600);

  steppers.addStepper(RightStepper);
  steppers.addStepper(LeftStepper);

  Serial.println("Setup Finish");
}

void loop()
{
  if(Serial.available() > 0){
    Angle = Serial.parseInt();
    Pulse[0] = int(Angle / Pulse2Deg);
    Pulse[1] = int(Angle / Pulse2Deg);
  }

  steppers.moveTo(Pulse);
  steppers.runSpeedToPosition(); // Blocks until all are in positions
  delay(1000);
}


