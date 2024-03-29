#ifndef ROS_COMMUNICATION_H
#define ROS_COMMUNICATION_H

#include <micro_ros_platformio.h>
#include <rclc/rclc.h>
#include <rclc/executor.h>

#include <std_msgs/msg/Float64MultiArray.h>

#define LED_PIN 2

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