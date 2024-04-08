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

#include <Arduino.h>
#include "ros_communication.h"
#include "Base_controller.h"

ROS_communication ros;


void setup()
{
  R_Stepper.setMaxSpeed(16000);  //* pulse
  R_Stepper.setAcceleration(4000);
  R_Stepper.setSpeed(8000);
  L_Stepper.setMaxSpeed(4000);
  L_Stepper.setSpeed(8000);

  ros.initialize();
  ros.subscriber_define();
  ros.executors_start();
}

void loop()
{
  ros.start_receiving_msgs();
}