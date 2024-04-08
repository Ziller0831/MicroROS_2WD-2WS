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

    public:
 
        struct PWM_data
        {
            int pwm;
            bool invert_;
        };

        void brake() override;

        PWM_data processPWM(int pwm);
};

class Stepper : public AccelStepper
{
    private:

    protected:

    public:
        Stepper(int driver_type, int step_pin, int dir_pin) : AccelStepper(driver_type, step_pin, dir_pin){};
};

#endif