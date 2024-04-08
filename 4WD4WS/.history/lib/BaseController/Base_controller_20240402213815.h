

#ifndef BASE_CONTROLLER_H
#define BASE_CONTROLLER_H

#include <Arduino.h>
#include "base_config.h"

double Pulse2Deg = 360 / ((360 / StepAngle) * MicroStep * GearRatio);

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

    void MotorDrive(float PWM);
    void Steering(float thetaR, float thetaL);

private:
    AccelStepper RightStepper(AccelStepper::DRIVER, STEP_R, DIR_R);
    AccelStepper LeftStepper(AccelStepper::DRIVER, STEP_L, DIR_L);
    //* Steper_constant
    const float StepAngle = 1.8;
    const int MicroStep = 16;
    const int GearRatio = 10;

    void BLDCSetting();
    void SteperSetting();
};


#endif