#include "Base_controller.h"
#include <math.h>


// void Steering(float thetaR, float thetaL)
// {

//     thetaR = thetaR * (PI / 180);
//     thetaL = thetaL * (PI / 180);

//     int R_pulse = thetaR / Pulse2Deg;
//     int L_pulse = thetaL / Pulse2Deg;

//     RightStepper.runToNewPosition(R_pulse);
//     LeftStepper.runToNewPosition(L_pulse);
// }

void BLDC::brake()
{
    ledcWrite(pwm_pin_, 0);
}

void BLDC::forward(int pwm)
{
    ledcWrite(pwm_pin_, pwm);
    digitalWrite(rev_pin_, LOW);
}

void BLDC::reverse(int pwm)
{
    ledcWrite(pwm_pin_, pwm);
    digitalWrite(rev_pin_, HIGH);
}

BLDC::PWM_data BLDC::processPWM(int pwm)
{
    BLDC::PWM_data pwm_data;

    if (pwm < 0)
    {
        pwm_data.pwm = abs(pwm) + pwm_offset_;
        pwm_data.invert_ = true;
    }
    else if (pwm > 0)
    {
        pwm_data.pwm += pwm_offset_;
        pwm_data.invert_ = false;
    }

    if (pwm > 255)
        pwm_data.pwm = 255;

    return pwm_data;
}