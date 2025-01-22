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
#include <FastAccelStepper.h>

#include "kinematic.h"
#include "base_config.h"
#include "Base_controller.h"
#include "XboxSeriesXControllerESP32_asukiaaa.hpp"

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
FastAccelStepperEngine stepperEngine;
FastAccelStepper *R_Stepper = nullptr;
FastAccelStepper *L_Stepper = nullptr;

XboxSeriesXControllerESP32_asukiaaa::Core
    xboxController(XBOX_MAC_ADDR);

void initialize()
{
  set_microros_serial_transports(Serial);

  prev_cmd_time = 0;

  allocator = rcl_get_default_allocator();
  RCCHECK(rclc_support_init(&support, 0, NULL, &allocator));
  RCCHECK(rclc_node_init_default(&node, "Base_controller", "", &support));

  // 初始化消息
  joy_command.linear_x = 0;
  joy_command.center_rotate_angle = 0;
  joy_command.turning_mode = 0;

  // 初始化步進引擎
  stepperEngine.init();
  R_Stepper = stepperEngine.stepperConnectToPin(STEP_R);
  L_Stepper = stepperEngine.stepperConnectToPin(STEP_L);

  if (R_Stepper && L_Stepper)
  {
    R_Stepper->setDirectionPin(DIR_R);
    R_Stepper->setAutoEnable(true);
    R_Stepper->setAcceleration(10000); // 設置加速度
    // R_Stepper->setSpeedInHz(6000);     // 設置速度

    L_Stepper->setDirectionPin(DIR_L);
    L_Stepper->setAutoEnable(true);
    L_Stepper->setAcceleration(10000); // 設置加速度
    // L_Stepper->setSpeedInHz(6000);     // 設置速度
  }
}

//* 訂閱者初始化
void subscriber_init()
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

void moveBase(float linear_x = joy_command.linear_x,
              float center_rotation_rad = 0,
              float center_rotation_angle = joy_command.center_rotate_angle,
              int turning_mode = joy_command.turning_mode)
{
  int32_t right_steps;
  int32_t left_steps;

  Kinematics::CP req_convertPara = kinematics.inverseKinematics(
      linear_x,
      center_rotation_rad,
      center_rotation_angle,
      turning_mode);

  bldcL_controller.spin(req_convertPara.pwm.BLDC_L);
  bldcR_controller.spin(req_convertPara.pwm.BLDC_R);

  if (R_Stepper && L_Stepper)
  {
    int32_t current_right_pos = R_Stepper->getCurrentPosition();
    int32_t current_left_pos = L_Stepper->getCurrentPosition();

    if (current_right_pos == 0 && current_left_pos == 0)
    {
      right_steps = req_convertPara.pulse.STEPPER_R;
      right_steps = req_convertPara.pulse.STEPPER_L;
    }
    else
    {
      right_steps = req_convertPara.pulse.STEPPER_R - current_right_pos;
      left_steps = req_convertPara.pulse.STEPPER_L - current_left_pos;
    }

    int32_t max_steps = max(abs(right_steps), abs(left_steps));
    float right_speed_ratio = abs(right_steps) / (float)max_steps;
    float left_speed_ratio = abs(left_steps) / (float)max_steps;

    uint32_t base_speed = 6000; // 基準速度（步/秒）
    R_Stepper->setSpeedInHz(base_speed * right_speed_ratio);
    L_Stepper->setSpeedInHz(base_speed * left_speed_ratio);

    R_Stepper->moveTo(req_convertPara.pulse.STEPPER_R); // 移動到目標位置
    L_Stepper->moveTo(req_convertPara.pulse.STEPPER_L);
  }
}

void motion_callback(const void *msg_recv)
{
  moveBase();
  prev_cmd_time = millis();
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

int8_t turning_mode = 0;
boolean gear_flag = true; // 換檔旗標
boolean vel_direction = true;

float linear_mapping(float value, float in_min, float in_max, float out_min, float out_max)
{
  return roundf((value - in_min) * (out_max - out_min) / (in_max - in_min) + out_min);
}

void remote_control()
{

  if (xboxController.xboxNotif.btnB == 1 && gear_flag == true)
  {
    turning_mode = !(turning_mode);
    gear_flag = false;
  }
  else if (xboxController.xboxNotif.btnB == 0)
  {
    gear_flag = true;
  }

  float_t linear_x = linear_mapping((float_t)xboxController.xboxNotif.trigRT, 0, 1023, 0, 2);

  if (turning_mode == 0)
  {
    if (xboxController.xboxNotif.btnLS == true && linear_x == 0)
    {
      vel_direction = false;
    }
    else if (xboxController.xboxNotif.btnRS == true && linear_x == 0)
    {
      vel_direction = true;
    }

    if (vel_direction == true)
    {
      joy_command.linear_x = linear_x;
    }
    else
    {
      joy_command.linear_x = -linear_x;
    }

    joy_command.center_rotate_angle = linear_mapping((float_t)xboxController.xboxNotif.joyLHori, 0, 65535, -45, 45);
  }
  else if (turning_mode == 1)
  {
    joy_command.linear_x = 0;
    joy_command.center_rotate_angle = linear_mapping((float_t)xboxController.xboxNotif.joyLHori, 0, 65535, 2, -2);
  }
  Serial.println(String(linear_x));
  // moveBase(joy_command.linear_x, 0, joy_command.center_rotate_angle, turning_mode);
}

void setup()
{
  Serial.begin(115200);

  xboxController.begin();

  // initialize();
  // subscriber_init();
  // executors_start();
}

void loop()
{
  xboxController.onLoop();
  remote_control();
  // Serial.println(String(xboxController.xboxNotif.trigRT));
}
