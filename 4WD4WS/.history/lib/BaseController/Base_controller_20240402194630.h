

#ifndef BASE_CONTROLLER_H
#define BASE_CONTROLLER_H

#include <Arduino.h>
#include "base_config.h"

class base_controller
{

    
private:
    void BLDCSetting();
    void SteperSetting();
};


//* Steper_constant
const float StepAngle = 1.8;
const int MicroStep = 16;
const int GearRatio = 10; // 10:1



void MotorDrive(float PWM);
void Steering(float thetaR, float thetaL);

#endif