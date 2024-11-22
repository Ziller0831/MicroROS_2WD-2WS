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

#define RCCHECK(fn)              \
  {                              \
    rcl_ret_t temp_rc = fn;      \
    if ((temp_rc != RCL_RET_OK)) \
    {                            \
      rclErrorLoop();            \
    }                            \
  }

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
rcl_timer_t control_timer;

//* 宣告内存分配器物件
rcl_allocator_t allocator;

//* 宣告Topic訂閱者
rcl_subscription_t motion_subscriber;
rcl_subscription_t joy_motion_subscriber;
// rcl_publisher_t test_publisher;

//* 宣告消息文件
customize_interface__msg__MotionCommand motion_command;
customize_interface__msg__JoyMotionCommand joy_command;
// std_msgs__msg__Float64 test_msg;

Kinematics kinematics(
    Kinematics::ROBOT_2WD2WS,
    MAX_BLDC_vel,
    WHEEL_DIAMETER,
    WHEELBASE,
    TRACK);

BLDC bldcR_controller(false, BLDC_R_PWM, R_PWM_CHANNEL, BLDC_R_REV, PWM_OFFSET, PWM_RESOLUTION);
BLDC bldcL_controller(false, BLDC_L_PWM, L_PWM_CHANNEL, BLDC_L_REV, PWM_OFFSET, PWM_RESOLUTION);

AccelStepper R_Stepper(AccelStepper::DRIVER, STEP_R, DIR_R);
AccelStepper L_Stepper(AccelStepper::DRIVER, STEP_L, DIR_L);
MultiStepper steering_steppers;

void initialize()
{
  Serial.begin(115200);
  Serial.println("ROS Communication node start");
  set_microros_serial_transports(Serial);

  time_offset = 0;
  prev_cmd_time = 0;

  allocator = rcl_get_default_allocator();
  RCCHECK(rclc_support_init(&support, 0, NULL, &allocator));
  RCCHECK(rclc_node_init_default(&node, "Base_controller", "", &support));
}

void subscriber_define()
{
  RCCHECK(rclc_subscription_init_default(
      &motion_subscriber,
      &node,
      ROSIDL_GET_MSG_TYPE_SUPPORT(customize_interface, msg, MotionCommand),
      "/motion_command"));
  RCCHECK(rclc_subscription_init_default(
      &joy_motion_subscriber,
      &node,
      ROSIDL_GET_MSG_TYPE_SUPPORT(customize_interface, msg, JoyMotionCommand),
      "/joy_command"));
}

void executors_start()
{
  executor = rclc_executor_get_zero_initialized_executor();
  RCCHECK(rclc_executor_init(&executor, &support.context, 2, &allocator));

  // RCCHECK(rclc_executor_add_subscription(
  //     &executor,
  //     &motion_subscriber,
  //     &motion_command,
  //     &motion_callback,
  //     ON_NEW_DATA));
  RCCHECK(rclc_executor_add_subscription(
      &executor,
      &joy_motion_subscriber,
      &joy_command,
      &motion_callback,
      ON_NEW_DATA));

  digitalWrite(LED_PIN, HIGH);

  Serial.println("Executors Started");
}

// void publisher_define()
// {
//   RCCHECK(rclc_publisher_init_default(
//       &test_publisher,
//       &node,
//       ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Float64),
//       "/base_test"));
// }

void motion_callback(const void *msg_recv)
{
  moveBase();
  prev_cmd_time = millis();
}

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
  // vTaskDelay(1000);
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

  initialize();
  subscriber_define();
  executors_start();

  joy_command.linear_x = 0;
  joy_command.center_rotate_angle = 0;
  joy_command.turning_mode = 0;
}

void loop()
{
  rclc_executor_spin_some(&executor, RCL_MS_TO_NS(100));
}
