/**
 * @file kinematic.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-04-08
 * 
 * @copyright Copyright (c) 2024
 * 
 * *負責將ROS2輸入進來的線速度與角速度最終轉換成PWM與Pulse
 */

#ifndef KINEMATIC_H
#define KINEMATIC_H

#include <Arduino.h>

class Kinematics
{
public:
    struct ackermannVel
    {
        float linear_x;
        float steer_angle;
    };

    struct rpm
    {
        int BLDC_R;
        int BLDC_L;
    };

    struct pwm
    {
        float BLDC_R;
        float BLDC_L;
    };

    struct angle
    {
        float STEPPER_R;
        float STEPPER_L;
    };

    struct pulse
    {
        float STEPPER_R;
        float STEPPER_L;
    };

    Kinematics()
    rpm calcRPM(float linear_x, float);

private:

};

#endif