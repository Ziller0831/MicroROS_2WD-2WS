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