#include "Base_controller.h"
#include <math.h>

BLDC::BLDC(bool invert, int pwm_pin, int pwm_channel,
           int rev_pin, int pwm_offset, int pwm_resolution) : MotorInterface(invert),
                                          _pwm_pin(pwm_pin),
                                          _pwm_channel(pwm_channel),
                                          _rev_pin(rev_pin),
                                          _pwm_offset(pwm_offset),
                                          _pwm_reso
{
    pinMode(_pwm_pin, OUTPUT);
    pinMode(_rev_pin, OUTPUT);

    ledcSetup(_pwm_channel, 5000, PWM_RESOLUTION);
    ledcAttachPin(_pwm_pin, _pwm_channel);
    ledcWrite(_pwm_channel, 0);
}

void BLDC::brake()
{
    ledcWrite(_pwm_channel, 0);
}

void BLDC::forward(int pwm)
{
    ledcWrite(_pwm_channel, processPWM(pwm));
    digitalWrite(_rev_pin, LOW);
}

void BLDC::reverse(int pwm)
{
    ledcWrite(_pwm_channel, processPWM(pwm));
    digitalWrite(_rev_pin, HIGH);
}

int BLDC::processPWM(int pwm)
{

    if (pwm < 0)
    {
        pwm = abs(pwm) + _pwm_offset;
    }
    else if (pwm > 0)
    {
        pwm += _pwm_offset;
    }

    if (pwm > 1024)
        pwm = 1024;

    return pwm;
}