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
#include "BaseControllerSetting.h"
#include "transmission.h"

void setup()
{
  pinMode(STEP_R, OUTPUT);
  pinMode(DIR_R, OUTPUT);
  pinMode(STEP_L, OUTPUT);
  pinMode(DIR_L, OUTPUT);
  pinMode(BLDC_R_PWM, OUTPUT);
  pinMode(BLDC_L_PWM, OUTPUT);
  pinMode(BLDC_R_rev, OUTPUT);
  pinMode(BLDC_L_rev, OUTPUT);
  pinMode(Encoder_R, OUTPUT);
  pinMode(Encoder_L, OUTPUT);

  RightStepper.setMaxSpeed(3200);
  RightStepper.setSpeed(1600);
  LeftStepper.setMaxSpeed(3200);
  LeftStepper.setSpeed(1600);

  steppers.addStepper(RightStepper);
  steppers.addStepper(LeftStepper);

  ledcSetup(0, 5000, 10);
  ledcAttachPin(BLDC_R_PWM, 0);

  ledcSetup(1, 5000, 10);
  ledcAttachPin(BLDC_L_PWM, 1);

  Serial.begin(115200);
  set_microros_serial_transports(Serial);

  allocator = rcl_get_default_allocator();
    

  Twist.linear.x = 0;
  Twist.linear.y = 0;
  Twist.linear.z = 0;
  Twist.angular.x = 0;
  Twist.angular.y = 0;
  Twist.angular.z = 0;

  Serial.println("Setup Finish");
}

void loop()
{
  // if(Serial.available() > 0)
  // {
  //   Angle = Serial.parseInt();
  //   AckermannSteering(Angle);

  //   Pulse[0] = RobotSteer.thetaR / Pulse2Deg;
  //   Pulse[1] = RobotSteer.thetaL / Pulse2Deg;
  // }

  // steppers.moveTo(Pulse);
  // steppers.runSpeedToPosition();
  // delay(1000);

  ledcWrite(0

}

void AckermannSteering(float Robot_yaw)
{
  double thetaR, thetaL;
  Robot_yaw = Robot_yaw * (PI / 180);
  if (Robot_yaw != 0)
  {
    RobotSteer.R = (RobotSteer.L / 2) / tan(Robot_yaw);
    RobotSteer.thetaR = atan(RobotSteer.L / (RobotSteer.R - (RobotSteer.T / 2))) * (180 / PI);
    RobotSteer.thetaL = -atan(RobotSteer.L / (RobotSteer.R + (RobotSteer.T / 2))) * (180 / PI);

  }
  else if (Robot_yaw == 0)
  {
    RobotSteer.thetaR = 0;
    RobotSteer.thetaL = 0;
  }

}

void ROSTimer_callback(rcl_timer_t *timer, int64_t last_call_time)
{
  RCLC_UNUSED(last_call_time);

}