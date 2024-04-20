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

#define LED_PIN 2
#define DOMAIN_ID 0

unsigned long long time_offset;

const unsigned int control_timeout = 10; // 100hZ

unsigned long prev_cmd_time;

Kinematics kinematics(
    Kinematics::ACKERMAN,
    MAX_BLDC_vel,
    WHEEL_DIAMETER,
    WHEELBASE,
    TRACK);

BLDC bldcR_controller(false, BLDC_R_PWM, R_PWM_CHANNEL, BLDC_R_REV, 120);
BLDC bldcL_controller(false, BLDC_L_PWM, L_PWM_CHANNEL, BLDC_L_REV, 120);

void setup()
{
  Stepper_init();

  ros.initialize();
  ros.subscriber_define();
  ros.executors_start();
}

void loop()
{
  ros.start_receiving_msgs();
}