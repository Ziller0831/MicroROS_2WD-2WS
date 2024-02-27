/*
 * @file main.cpp
 * @Jhih-Bin Huang (F112102103@nkust.edu.tw)
 * @brief
 * @version 0.1
 * @date 2024-02-21
 *
 * @copyright Copyright (c) 2024
 *
 * Input argument:
 *    Robot_yaw -> 轉彎角度
 *    v -> 車體速度
 */
#include "4WD4WS.h"

void setup()
{
  pinMode(STEP_R, OUTPUT);
  pinMode(DIR_R, OUTPUT);
  pinMode(STEP_L, OUTPUT);
  pinMode(DIR_L, OUTPUT);

  RightStepper.setMaxSpeed(3200);
  RightStepper.setSpeed(1600);
  LeftStepper.setMaxSpeed(3200);
  LeftStepper.setSpeed(1600);

  steppers.addStepper(RightStepper);
  steppers.addStepper(LeftStepper);

  Serial.begin(115200);

  Serial.println("Setup Finish");
}

void loop()
{
  if(Serial.available() > 0){
    Angle = Serial.parseInt();
    RobotSteer.thetaR, RobotSteer.thetaL = AckermannSteering(Angle);
    Serial.println(RobotSteer.thetaR);
  }

  Pulse[0] = RobotSteer.thetaR / Pulse2Deg;
  Pulse[1] = RobotSteer.thetaL / Pulse2Deg;

  steppers.moveTo(Pulse);
  steppers.runSpeedToPosition(); 
  delay(1000);
}


float AckermannSteering(float Robot_yaw){
  RobotSteer.R = (RobotSteer.L / 2) / tan(Robot_yaw);
  Serial.println(RobotSteer.R);
  float thetaR = atan(RobotSteer.L / (RobotSteer.R - (RobotSteer.T / 2)));
  float thetaL = atan(RobotSteer.L / (RobotSteer.R + (RobotSteer.T / 2)));

  return thetaR, thetaL;
}
