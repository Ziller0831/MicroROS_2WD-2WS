

#ifndef BASE_CONTROLLER_H
#define BASE_CONTROLLER_H

#include <Arduino.h>
#include "base_config.h"

class base_controller
{
public:
    void MotorDrive(float PWM);
    void Steering(float thetaR, float thetaL);
    struct pwm
    {
        float BLDC_R;
        float BLDC_L;
    };

private:
    //* Steper_constant
    const float StepAngle = 1.8;
    const int MicroStep = 16;
    const int GearRatio = 10;
    double Pulse2Deg = 360 / ((360 / StepAngle) * MicroStep * GearRatio);

    void BLDCSetting();
    void SteperSetting();
};


#endif