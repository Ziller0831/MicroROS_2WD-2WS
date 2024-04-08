#ifndef KINEMATIC_H
#define KINEMATIC_H

#include <Arduino.h>

class Kinematics
{
public:
    struct rpm
    {
        int BLDC_R;
        int BLDC_L;
    };

    struct pwm
    {
        float BLDC_R;
        float BLDC_L;
    };

    Kinematics
};

#endif