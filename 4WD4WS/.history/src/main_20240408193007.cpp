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
Stepper RightStepper(AccelStepper::DRIVER, STEP_R, DIR_R);
Stepper LeftStepper(AccelStepper::DRIVER, STEP_L, DIR_L)
BLDC bldc;

void setup()
{
  ros.initialize();
  ros.subscriber_define();
  ros.executors_start();
}

void loop()
{
  ros.start_receiving_msgs();
}