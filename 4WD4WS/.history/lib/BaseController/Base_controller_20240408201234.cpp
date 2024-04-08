#include "Base_controller.h"
#include <math.h>


// void base_controller::SteperSetting()
// {
//     pinMode(STEP_R, OUTPUT);
//     pinMode(DIR_R, OUTPUT);
//     pinMode(STEP_L, OUTPUT);
//     pinMode(DIR_L, OUTPUT);

//     RightStepper.setMaxSpeed(3200);
//     RightStepper.setSpeed(1600);
//     LeftStepper.setMaxSpeed(3200);
//     LeftStepper.setSpeed(1600);
// }

// void MotorDrive(float PWM)
// {
//     ledcWrite(R_PWM_channel, PWM);
//     ledcWrite(L_PWM_channel, PWM);
// }

// void Steering(float thetaR, float thetaL)
// {

//     thetaR = thetaR * (PI / 180);
//     thetaL = thetaL * (PI / 180);

//     int R_pulse = thetaR / Pulse2Deg;
//     int L_pulse = thetaL / Pulse2Deg;

//     RightStepper.runToNewPosition(R_pulse);
//     LeftStepper.runToNewPosition(L_pulse);
// }

//* 物件建構子多載
BLDC::bldc(bool invert, int pwm_pin, int pwm_channel, int rev_pin, int pwm_offset) : MotorInterface(invert), pwm_pin_(pwm_pin), pwm_channel_(pwm_channel), rev_pin_(rev_pin), pwm_offset_(pwm_offset)
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

BLDC::PWM_data BLDC::processPWM(int pwm)
{
    bool invert_;
    if (pwm < 0)
    {
        pwm = abs(pwm) + pwm_offset_;
        invert_ = true;
    }
    if (pwm > 0)
    {
        pwm += pwm_offset_;
        invert_ = false;
    }
    if (pwm > 255)
        pwm = 255;

    return pwm, invert_;
}