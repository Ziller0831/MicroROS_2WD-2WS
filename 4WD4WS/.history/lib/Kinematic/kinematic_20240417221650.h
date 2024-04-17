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
#include "base_config.h"

class Kinematics
{
public:
    enum base
    {
        ACKERMAN, // 1
        DIFFERENTIAL_DRIVE
    };

    enum base eBasePlatform_;

    typedef struct MotionCommand
    {
        float linear_x;
        float center_rotation_rad;
        int turning_distance;
    } MCommand;

    MCommand mCommand;

    typedef struct MotionControlData
    {
        struct
        {
            int BLDC_R;
            int BLDC_L;
        } rpm;
        struct
        {
            float STEPPER_R;
            float STEPPER_L;
        } angle;
    } MControl;

    typedef struct ConverterParameters
    {
        struct
        {
            int BLDC_R;
            byte BLDC_L;
        } pwm;
        struct
        {
            long STEPPER_R;
            long STEPPER_L;
        } pulse;
    } CP;

    Kinematics(base robot_base, int motor_max_rpm, float wheelDiameter, float wheelBase, float track);
    CP inverseKinematics(float linear_x, float center_rotation_rad, int turning_distance);

private:
    int iMaxVel_;
    float fWheelBase_;
    float fTrack_;
    float fWheelCircumference_;

    // TODO:把傳出也改成用傳址的方式
    MControl ackerman(MCommand *mCommand);
    CP baseOrderConvert(MControl *mControl);
};

#endif