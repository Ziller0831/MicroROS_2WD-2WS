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
#include "motor_interface.h"



class base_controller
{
public:


private:
    void MotorDrive(byte PWM_R, byte);
    void Steering(float thetaR, float thetaL);

    void BLDCSetting();
    void SteperSetting();
};


class BLDC : public MotorInterface
{
    private:
        int pwm_pin_;
        int pwm_channel_;
        int rev_pin_;
        int pwm_offset_;

        struct motor_control_parm
        {
            
        }typedef ;
        

    public:
        //* 物件建構子多載 
        BLDC(bool invert, int pwm_pin, int pwm_channel, int rev_pin, int pwm_offset): MotorInterface(invert), pwm_pin_(pwm_pin), pwm_channel_(pwm_channel), rev_pin_(rev_pin), pwm_offset_(pwm_offset)
        {
            pinMode(pwm_pin_, OUTPUT);
            pinMode(rev_pin_, OUTPUT);

            ledcSetup(pwm_channel_, 5000, 8);
            ledcAttachPin(pwm_pin_, pwm_channel_);
            ledcWrite(pwm_channel_, 0);
        }

        void brake() override;

        int calc_pwm_with_offset(int pwm);
};

class Stepper : public AccelStepper
{
    private:

    protected:

    public:
        Stepper(int driver_type, int step_pin, int dir_pin) : AccelStepper(driver_type, step_pin, dir_pin){};
};

#endif