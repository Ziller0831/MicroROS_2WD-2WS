#ifndef ROS_COMMUNICATION_H
#define ROS_COMMUNICATION_H

#include <micro_ros_platformio.h>
#include <rclc/rclc.h>
#include <rclc/executor.h>

#include <customize_interface/msg/motion_command.h>
#include <std_msgs/msg/float32_multi_array.h>

#include "Base_controller.h"
#include "kinematic.h"

#define LED_PIN 2
#define DOMAIN_ID 0

Kinematics kinematics(
    Kinematics::ACKERMAN,
    MAX_BLDC_RPM,
    WHEEL_DIAMETER,
    WHEELBASE,
    TRACK);

BLDC bldcR_controller(0, BLDC_R_PWM, R_PWM_CHANNEL, BLDC_R_REV, 120);
BLDC bldcL_controller(0, BLDC_L_PWM, L_PWM_CHANNEL, BLDC_L_REV, 120);

Kinematics.MCommand

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
};

void error_loop();

#endif