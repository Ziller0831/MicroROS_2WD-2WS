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
    enum base
    {
        ACKERMAN,            // 1
        ACKERMAN_SELF_ROTATE, // 2
        DIFFERENTIAL_DRIVE
    };

    enum base eBasePlatform_;

    typedef struct MotionCommand
    {
        float linear_x;
        float center_rotation_rad;
        int turning_distance;
    } MC;

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
    }MCD;

    typedef struct ConverterParameters
    {
        struct
        {
            float BLDC_R;
            float BLDC_L;
        } pwm;
        struct
        {
            float STEPPER_R;
            float STEPPER_L;
        } pulse;
    }CP;

    Kinematics(base robot_base, int motor_max_rpm, float wheelDiameter, float wheelBase, float track);
    MCD inverseKinematics(upperCommand *upperCommand);

private:

    int iMaxRpm_;
    float fWheelBase_;
    float fTrack_;
    float fWheelCircumference_;

    // TODO:把傳出也改成用傳址的方式
    MCD ackerman(Vel* vel);
    MCD selfRotate(float rotate_vel);
    CP baseOrderConvert(MCD* mcd);
};

#endif