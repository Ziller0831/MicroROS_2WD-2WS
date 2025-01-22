#include "Base_controller.h"
#include <math.h>

BLDC::BLDC(bool invert, int pwm_pin, int pwm_channel,
           int rev_pin, int pwm_offset) : MotorInterface(invert),
                                          _pwm_pin(pwm_pin),
                                          _pwm_channel(pwm_channel),
                                          _rev_pin(rev_pin),
                                          _pwm_offset(pwm_offset)
{
    pinMode(pwm_pin_, OUTPUT);
    pinMode(rev_pin_, OUTPUT);

    ledcSetup(pwm_channel_, 5000, 10);
    ledcAttachPin(pwm_pin_, pwm_channel_);
    ledcWrite(pwm_channel_, 0);
}

void BLDC::brake()
{
    ledcWrite(pwm_channel_, 0);
}

void BLDC::forward(int pwm)
{
    ledcWrite(pwm_channel_, processPWM(pwm));
    digitalWrite(rev_pin_, LOW);
}

void BLDC::reverse(int pwm)
{
    ledcWrite(pwm_channel_, processPWM(pwm));
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