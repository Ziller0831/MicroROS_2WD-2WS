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
#include <std_msgs/msg/float32_multi_array.h>

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

#define LED_PIN 2
#define DOMAIN_ID 0

unsigned long long time_offset;
const unsigned int control_timeout = 10; // 100hZ
unsigned long prev_cmd_time;

void initialize();
void subscriber_define();
void start_receiving_msgs();
void executors_start();
void moveBase();
void motion_callback(const void *msg_recv);
void controlCallback(rcl_timer_t *timer, int64_t last_call_time);
void syncTime();
void rclErrorLoop();

rcl_subscription_t motion_subscriber;
rcl_subscription_t joy_motion_subscriber;

customize_interface__msg__MotionCommand motion_command;
customize_interface__msg__JoyMotionCommand joy_command;

rclc_support_t support;
rclc_executor_t executor;

rcl_node_t node;
rcl_allocator_t allocator;
rcl_timer_t control_timer;

Kinematics kinematics(
    Kinematics::ACKERMAN,
    MAX_BLDC_vel,
    WHEEL_DIAMETER,
    WHEELBASE,
    TRACK);

BLDC bldcR_controller(false, BLDC_R_PWM, R_PWM_CHANNEL, BLDC_R_REV, 120);
BLDC bldcL_controller(false, BLDC_L_PWM, L_PWM_CHANNEL, BLDC_L_REV, 120);

AccelStepper R_Stepper(AccelStepper::DRIVER, STEP_R, DIR_R);
AccelStepper L_Stepper(AccelStepper::DRIVER, STEP_L, DIR_L);
MultiStepper steering_steppers;

void setup()
{
  R_Stepper.setMaxSpeed(16000); //* pulse
  R_Stepper.setAcceleration(4000);
  R_Stepper.setSpeed(8000);

  L_Stepper.setMaxSpeed(16000);
  R_Stepper.setAcceleration(4000);
  L_Stepper.setSpeed(8000);

  steering_steppers.addStepper(R_Stepper);
  steering_steppers.addStepper(L_Stepper);

  initialize();
  subscriber_define();
  executors_start();
}

void loop()
{
  start_receiving_msgs();
}

void initialize()
{
  Serial.begin(115200);
  Serial.println("ROS Communication node started");
  set_microros_serial_transports(Serial);

  time_offset = 0;
  prev_cmd_time = 0;
  allocator = rcl_get_default_allocator();

  RCCHECK(rclc_support_init(&support, 0, NULL, &allocator));
  RCCHECK(rclc_node_init_default(&node, "Base_controller", "", &support));
  RCCHECK(rclc_timer_init_default(
      &control_timer,
      &support,
      RCL_MS_TO_NS(control_timeout),
      controlCallback));
}

void executors_start()
{
  RCCHECK(rclc_executor_init(&executor, &support.context, 1, &allocator));
  RCCHECK(rclc_executor_add_subscription(
      &executor,
      &motion_subscriber,
      &motion_command,
      &motion_callback,
      ON_NEW_DATA));
  RCCHECK(rclc_executor_add_subscription(
      &executor,
      &joy_motion_subscriber,
      &joy_command,
      &motion_callback,
      ON_NEW_DATA));
  RCCHECK(rclc_executor_add_timer(&executor, &control_timer));

  syncTime();
  digitalWrite(LED_PIN, HIGH);

  Serial.println("Executors Started");
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
      "/joy_motion_command"));
}

void start_receiving_msgs()
{
  rclc_executor_spin_some(&executor, RCL_MS_TO_NS(100));
  delay(100);
}

void motion_callback(const void *msg_recv)
{
  digitalWrite(LED_PIN, !digitalRead(LED_PIN));
  prev_cmd_time = millis();
}

void controlCallback(rcl_timer_t *timer, int64_t last_call_time)
{
  RCLC_UNUSED(last_call_time);
  if (timer != NULL)
    moveBase();
}

void moveBase()
{
  float linear_x;
  float center_rotation_rad;
  float center_rotation_angle;
  int turning_mode;

  if ()
  {
    linear_x = motion_command.linear_x;
    center_rotation_rad = motion_command.center_rotation_rad;
    center_rotation_angle = 0;
    turning_mode = motion_command.turning_mode;
  }
  else if ()
  {
    linear_x = joy_command.linear_x;
    center_rotation_rad = 0;
    center_rotation_angle = joy_command.center_rotate_angle;
    turning_mode = joy_command.turning_mode;
  }
  Kinematics::CP req_convertPara = kinematics.inverseKinematics(
      linear_x,
      center_rotation_rad,
      center_rotation_angle,
      turning_mode);

  bldcL_controller.spin(req_convertPara.pwm.BLDC_L);
  bldcR_controller.spin(req_convertPara.pwm.BLDC_R);

  long stepperPulse[2] = {req_convertPara.pulse.STEPPER_R, req_convertPara.pulse.STEPPER_L};
  steering_steppers.moveTo(stepperPulse);
}

void syncTime()
{

  unsigned long now = millis();
  RCCHECK(rmw_uros_sync_session(10));
  unsigned long long ros_time_ms = rmw_uros_epoch_millis();
  // ROS_agent和MCU的时间差
  time_offset = ros_time_ms - now;
}

void rclErrorLoop()
{
  while (1)
  {
    digitalWrite(LED_PIN, !digitalRead(LED_PIN));
    delay(500);
  }
}