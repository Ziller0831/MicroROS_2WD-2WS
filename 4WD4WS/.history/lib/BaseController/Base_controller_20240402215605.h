

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
    struct pwm
    {
        float BLDC_R;
        float BLDC_L;
    };

    struct pulse
    {
        float STEPPER_R;
        float STEPPER_L;
    };

    void calcRPM();

private:
    void
    MotorDrive(float PWM);
    void Steering(float thetaR, float thetaL);

    void BLDCSetting();
    void SteperSetting();
};

double Pulse2Deg = 360 / ((360 / StepAngle) * MicroStep * GearRatio);

#endif