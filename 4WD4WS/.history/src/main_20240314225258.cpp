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
  if(Serial.available() > 0)
  {
    Angle = Serial.parseInt();
    AckermannSteering(Angle);

    Pulse[0] = RobotSteer.thetaR / Pulse2Deg;
    Pulse[1] = RobotSteer.thetaL / Pulse2Deg;
  }

 
 
  steppers.moveTo(Pulse);
  steppers.runSpeedToPosition(); 
  delay(1000);
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

// #include <Arduino.h>
// #include <micro_ros_platformio.h>

// #include <rcl/rcl.h>
// #include <rclc/rclc.h>
// #include <rclc/executor.h>

// #include <std_msgs/msg/int32.h>

// #if !defined(MICRO_ROS_TRANSPORT_ARDUINO_SERIAL)
// #error This example is only avaliable for Arduino framework with serial transport.
// #endif

// rcl_publisher_t publisher;
// std_msgs__msg__Int32 msg;

// rclc_executor_t executor;
// rclc_support_t support;
// rcl_allocator_t allocator;
// rcl_node_t node;
// rcl_timer_t timer;

// #define RCCHECK(fn)              \
//   {                              \
//     rcl_ret_t temp_rc = fn;      \
//     if ((temp_rc != RCL_RET_OK)) \
//     {                            \
//       error_loop();              \
//     }                            \
//   }
// #define RCSOFTCHECK(fn)          \
//   {                              \
//     rcl_ret_t temp_rc = fn;      \
//     if ((temp_rc != RCL_RET_OK)) \
//     {                            \
//     }                            \
//   }

// // Error handle loop
// void error_loop()
// {
//   while (1)
//   {
//     delay(100);
//   }
// }

// void timer_callback(rcl_timer_t *timer, int64_t last_call_time)
// {
//   RCLC_UNUSED(last_call_time);
//   if (timer != NULL)
//   {
//     RCSOFTCHECK(rcl_publish(&publisher, &msg, NULL));
//     msg.data++;
//   }
// }

// void setup()
// {
//   // Configure serial transport
//   Serial.begin(115200);
//   set_microros_serial_transports(Serial);
//   delay(2000);

//   allocator = rcl_get_default_allocator();

//   // create init_options
//   RCCHECK(rclc_support_init(&support, 0, NULL, &allocator));

//   // create node
//   RCCHECK(rclc_node_init_default(&node, "micro_ros_platformio_node", "", &support));

//   // create publisher
//   RCCHECK(rclc_publisher_init_default(
//       &publisher,
//       &node,
//       ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Int32),
//       "micro_ros_platformio_node_publisher"));

//   // create timer,
//   const unsigned int timer_timeout = 1000;
//   RCCHECK(rclc_timer_init_default(
//       &timer,
//       &support,
//       RCL_MS_TO_NS(timer_timeout),
//       timer_callback));

//   // create executor
//   RCCHECK(rclc_executor_init(&executor, &support.context, 1, &allocator));
//   RCCHECK(rclc_executor_add_timer(&executor, &timer));

//   msg.data = 0;
// }

// void loop()
// {
//   delay(100);
//   RCSOFTCHECK(rclc_executor_spin_some(&executor, RCL_MS_TO_NS(100)));
// }