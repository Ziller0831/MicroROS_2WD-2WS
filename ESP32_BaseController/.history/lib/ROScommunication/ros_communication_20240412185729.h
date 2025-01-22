#ifndef ROS_COMMUNICATION_H
#define ROS_COMMUNICATION_H

#include <micro_ros_platformio.h>
#include <rclc/rclc.h>
#include <rclc/executor.h>

#include <extra_packages/msg/MotionCommand.h>
#include <std_msgs/msg/float32_multi_array.h>

#define LED_PIN 2
#define DOMAIN_ID 0

class ROS_communication
{
public:
    ROS_communication();
    void initialize();
    void subscriber_define();
    static void vel_callback(const void *msg_recv);
    void start_receiving_msgs();
    void executors_start();

private:
    static float linear_vel;
    static float steer_angle;
};

void error_loop();

#endif