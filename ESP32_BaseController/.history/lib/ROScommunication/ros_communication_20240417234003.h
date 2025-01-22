#ifndef __ROS_COMMUNICATION_H__
#define __ROS_COMMUNICATION_H__

#include <micro_ros_platformio.h>
#include <rclc/rclc.h>
#include <rclc/executor.h>

#include <customize_interface/msg/motion_command.h>
#include <std_msgs/msg/float32_multi_array.h>

#include "Base_controller.h"
#include "kinematic.h"

#define LED_PIN 2
#define DOMAIN_ID 0

#ifndef time_offset
unsigned long long time_offset = 0;
#endif
const unsigned int control_timeout = 10; // 100hZ

unsigned long prev_cmd_time = 0;

Kinematics kinematics(
    Kinematics::ACKERMAN,
    MAX_BLDC_vel,
    WHEEL_DIAMETER,
    WHEELBASE,
    TRACK);

BLDC bldcR_controller(false, BLDC_R_PWM, R_PWM_CHANNEL, BLDC_R_REV, 120);
BLDC bldcL_controller(false, BLDC_L_PWM, L_PWM_CHANNEL, BLDC_L_REV, 120);

class ROS_communication
{
public:
    ROS_communication();
    void initialize();
    void subscriber_define();
    void start_receiving_msgs();
    void executors_start();

private:
    static float linear_vel;
};

void moveBase();
void motion_callback(const void *msg_recv);
void controlCallback(rcl_timer_t *timer, int64_t last_call_time);

void syncTime();
void rclErrorLoop();

#endif