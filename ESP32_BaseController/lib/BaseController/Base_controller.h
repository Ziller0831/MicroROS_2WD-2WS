/**
 * @file Base_controller.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2024-04-08
 *
 * *連接端口  processPWM(int pwm)
 *
 *
 */

#ifndef __BASE_CONTROLLER_H__
#define __BASE_CONTROLLER_H__

#include <Arduino.h>
#include "base_config.h"
#include "motor_interface.h"

class BLDC : public MotorInterface
{
public:
    //* 物件建構子多載
    BLDC(bool invert, short int pwm_pin, short int pwm_channel, short int rev_pin, int pwm_offset, int pwm_resolution);

    void brake() override;

    int processPWM(int pwm);

private:
    short int _pwm_pin;
    short int _pwm_channel;
    short int _rev_pin;
    int _pwm_offset;
    int _pwm_resolution;

protected:
    void forward(int pwm) override;
    void reverse(int pwm) override;
};

#endif