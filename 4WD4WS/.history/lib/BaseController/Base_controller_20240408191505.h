/**
 * @file Base_controller.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-04-08
 * 
 * *目前這個部分是將整個底層控制器當成一個物件來管理，後面可改成將每顆馬達物件化
 * 
 * 
 */

#ifndef BASE_CONTROLLER_H
#define BASE_CONTROLLER_H

#include <Arduino.h>
#include <AccelStepper.h>
#include "base_config.h"

AccelStepper RightStepper(AccelStepper::DRIVER, STEP_R, DIR_R);
AccelStepper LeftStepper(AccelStepper::DRIVER, STEP_L, DIR_L);


class base_controller
{
public:


private:
    void MotorDrive(byte PWM_R, byte);
    void Steering(float thetaR, float thetaL);

    void BLDCSetting();
    void SteperSetting();
};


class BLDC
{
    private:
        int pwm_pin_;
        int pwm_channel_;
        int rev_pin_;
        int pwm_offset_;

    public:
        BLDC(int pwm_pin, int pwm_channel, int rev_pin, int pwm_offset): pwm_pin_(pwm_pin), pwm_channel_(pwm_channel), rev_pin_(rev_pin), pwm_offset_(pwm_offset)
        {
            pinMode(pwm_pin_, OUTPUT);
            pinMode(rev_pin_, OUTPUT);

            ledcSetup(pwm_channel_, 5000, 8);
            ledcAttachPin(pwm_pin_, pwm_channel_);
        }
};

#endif