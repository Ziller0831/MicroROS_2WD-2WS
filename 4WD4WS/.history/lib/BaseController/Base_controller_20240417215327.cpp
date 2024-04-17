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

BLDC::BLDC(bool invert, int pwm_pin, int pwm_channel,
           int rev_pin, int pwm_offset) : MotorInterface(invert),
                                          pwm_pin_(pwm_pin),
                                          pwm_channel_(pwm_channel),
                                          rev_pin_(rev_pin),
                                          pwm_offset_(pwm_offset)
{
    pinMode(pwm_pin_, OUTPUT);
    pinMode(rev_pin_, OUTPUT);

    ledcSetup(pwm_channel_, 5000, 8);
    ledcAttachPin(pwm_pin_, pwm_channel_);
    ledcWrite(pwm_channel_, 0);
}


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

int BLDC::processPWM(int pwm)
{

    if (pwm < 0)
    {
        pwm = abs(pwm) + pwm_offset_;
    }
    else if (pwm > 0)
    {
        pwm += pwm_offset_;

    }

    if (pwm > 255)
        pwm = 255;

    return pwm;
}

void Stepper_init()
{
    R_Stepper.setMaxSpeed(16000); //* pulse
    R_Stepper.setAcceleration(4000);
    R_Stepper.setSpeed(8000);

    L_Stepper.setMaxSpeed(16000);
    R_Stepper.setAcceleration(4000);
    L_Stepper.setSpeed(8000);

    steering_steppers.addStepper(R_Stepper);
    steering_steppers.addStepper(L_Stepper);
}