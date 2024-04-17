/**
 * @file Base_controller.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2024-04-08
 *
 * *連接端口  processPWM(int pwm)
 *
 *
 */

#ifndef BASE_CONTROLLER_H
#define BASE_CONTROLLER_H

#include <Arduino.h>
#include <AccelStepper.h>
#include <MultiStepper.h>
#include "base_config.h"
#include "motor_interface.h"

class BLDC : public MotorInterface
{
public:
    //* 物件建構子多載
    BLDC(bool invert, int pwm_pin, int pwm_channel, int rev_pin, int pwm_offset);

    struct PWM_data
    {
        int pwm;
        bool invert_;
    };

    void brake() override;

    PWM_data processPWM(int pwm);

    drivebase()

private:
    int pwm_pin_;
    int pwm_channel_;
    int rev_pin_;
    int pwm_offset_;

protected:
    void forward(int pwm) override;
    void reverse(int pwm) override;
};

AccelStepper R_Stepper(AccelStepper::DRIVER, STEP_R, DIR_R);
AccelStepper L_Stepper(AccelStepper::DRIVER, STEP_L, DIR_L);
MultiStepper steering_steppers;

void Stepper_init();

long Stepper_pulses[2];

// class Stepper : public MultiStepper
// {
//     public:
//         Stepper();

//     protected:
// };

#endif