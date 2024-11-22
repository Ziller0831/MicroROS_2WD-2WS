/*
 * @file main.cpp
 * @Jhih-Bin Huang (F112102103@nkust.edu.tw)
 * @brief
 * @version 0.1
 * @date 2024-02-21
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <Arduino.h>
#include <AccelStepper.h>
#include <MultiStepper.h>

#include "kinematic.h"
#include "base_config.h"
#include "Base_controller.h"

#include <micro_ros_platformio.h>
#include <rclc/rclc.h>
#include <rclc/executor.h>

#include <customize_interface/msg/motion_command.h>
#include <customize_interface/msg/joy_motion_command.h>
#include <std_msgs/msg/float64.h>

#define LED_PIN 2
#define DOMAIN_ID 0

//* 返回值檢查
#define RCCHECK(fn)              \
  {                              \
    rcl_ret_t temp_rc = fn;      \
    if ((temp_rc != RCL_RET_OK)) \
    {                            \
      rclErrorLoop();            \
    }                            \
  }

//* 返回值檢查
#define RCSOFTCHECK(fn)          \
  {                              \
    rcl_ret_t temp_rc = fn;      \
    if ((temp_rc != RCL_RET_OK)) \
    {                            \
    }                            \
  }

void rclErrorLoop()
{
  while (1)
  {
    digitalWrite(LED_PIN, !digitalRead(LED_PIN));
    delay(250);
  }
}

unsigned long long time_offset;
const unsigned int control_timeout = 10; // 100hZ
unsigned long prev_cmd_time;

rclc_support_t support;
rclc_executor_t executor;

rcl_node_t node;

//* 宣告内存分配器物件
rcl_allocator_t allocator;

//* 宣告Topic訂閱者
rcl_subscription_t motion_subscriber;
rcl_subscription_t joy_motion_subscriber;
// rcl_publisher_t test_publisher;

//* 宣告消息文件
customize_interface__msg__MotionCommand motion_command;
customize_interface__msg__JoyMotionCommand joy_command;

//* 宣告運動學
Kinematics kinematics(
    Kinematics::ROBOT_2WD2WS,
    MAX_BLDC_vel,
    WHEEL_DIAMETER,
    WHEELBASE,
    TRACK);

//* 宣告左右BLDC馬達控制器物件
BLDC bldcR_controller(false, BLDC_R_PWM, R_PWM_CHANNEL, BLDC_R_REV, PWM_OFFSET, PWM_RESOLUTION);
BLDC bldcL_controller(false, BLDC_L_PWM, L_PWM_CHANNEL, BLDC_L_REV, PWM_OFFSET, PWM_RESOLUTION);

//* 宣告左右轉向步進馬達物件
AccelStepper R_Stepper(AccelStepper::DRIVER, STEP_R, DIR_R);
AccelStepper L_Stepper(AccelStepper::DRIVER, STEP_L, DIR_L);
MultiStepper steering_steppers;

void moveBase()
{
  float linear_x;
  float center_rotation_rad;
  float center_rotation_angle;
  int turning_mode;

  linear_x = joy_command.linear_x;
  center_rotation_rad = 0;
  center_rotation_angle = joy_command.center_rotate_angle;
  turning_mode = joy_command.turning_mode;

  Kinematics::CP req_convertPara = kinematics.inverseKinematics(
      linear_x,
      center_rotation_rad,
      center_rotation_angle,
      turning_mode);

  bldcL_controller.spin(req_convertPara.pwm.BLDC_L);
  bldcR_controller.spin(req_convertPara.pwm.BLDC_R);

  long stepperPulse[2] = {req_convertPara.pulse.STEPPER_R, req_convertPara.pulse.STEPPER_L};
  steering_steppers.moveTo(stepperPulse);
  steering_steppers.runSpeedToPosition();
}

void motion_callback(const void *msg_recv)
{
  moveBase();
  prev_cmd_time = millis();
}

void setup()
{
  R_Stepper.setMaxSpeed(7600 * 1.5); //* pulse
  R_Stepper.setAcceleration(12000 / 4);
  R_Stepper.setSpeed(12000);

  L_Stepper.setMaxSpeed(7600 * 1.5);
  R_Stepper.setAcceleration(12000 / 4);
  L_Stepper.setSpeed(12000);

  steering_steppers.addStepper(R_Stepper);
  steering_steppers.addStepper(L_Stepper);

  // initialize();
  // subscriber_init();
  // executors_start();
}

void loop()
{
  // RCSOFTCHECK(rclc_executor_spin_some(&executor, RCL_MS_TO_NS(100)));
}