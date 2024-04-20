// #ifndef __ROS_COMMUNICATION_H__
// #define __ROS_COMMUNICATION_H__

// #include <micro_ros_platformio.h>
// #include <rclc/rclc.h>
// #include <rclc/executor.h>

// #include <customize_interface/msg/motion_command.h>
// #include <std_msgs/msg/float32_multi_array.h>

// #include "Base_controller.h"
// #include "kinematic.h"
// #include <Arduino.h>


// class ROS_communication
// {
// public:
//     ROS_communication();
//     void initialize();
//     void subscriber_define();
//     void start_receiving_msgs();
//     void executors_start();

// private:
//     static float linear_vel;
// };

// void moveBase();
// void motion_callback(const void *msg_recv);
// void controlCallback(rcl_timer_t *timer, int64_t last_call_time);

// void syncTime();
// void rclErrorLoop();

// #endif