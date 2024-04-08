#ifndef KINEMATIC_H
#define KINEMATIC_H

#include <Arduino.h>

class Kinematics
{
public:
    struct ackermannVel
    {
        float linear_x;
        float steer_angle;
    };
    /********************************/
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
    /********************************/
    struct angle
    {
        float STEPPER_R;
        float STEPPER_L;
    };

private:
    typedef struct ackermannPara
    {
        const int T = 1120; // wheel axle spacing
        const int L = 750;  // wheel spacing`l``

        float R; //

        float thetaR;
        float thetaL;
    } AckermannPara;
};

#endif