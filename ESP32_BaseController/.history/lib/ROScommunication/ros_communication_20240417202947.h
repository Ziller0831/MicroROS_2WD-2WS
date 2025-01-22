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

const unsigned int control_timeout = 10; // 100hZ

unsigned long prev_cmd_time = 0;

Kinematics kinematics(
    Kinematics::ACKERMAN,
    MAX_BLDC_vel,
    WHEEL_DIAMETER,
    WHEELBASE,
    TRACK);

BLDC bldcR_controller(0, BLDC_R_PWM, R_PWM_CHANNEL, BLDC_R_REV, 120);
BLDC bldcL_controller(0, BLDC_L_PWM, L_PWM_CHANNEL, BLDC_L_REV, 120);

class ROS_communication
{
public:
        ROS_communication();
    void initialize();
    void subscriber_define();
    void start_receiving_msgs();
    void executors_start();
    void timerSetup();

private:
    static float linear_vel;

    void motion_callback(const void *msg_recv);
    void controlCallback(rcl_timer_t *timer, int64_t last_call_time);
};

void error_loop();

#endif