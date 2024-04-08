#include "Base_controller.h"
#include <math.h>


void base_controller::BLDCSetting()
{
    pinMode(BLDC_R_PWM, OUTPUT);
    pinMode(BLDC_L_PWM, OUTPUT);
    pinMode(BLDC_R_rev, OUTPUT);
    pinMode(BLDC_L_rev, OUTPUT);
    pinMode(Encoder_R, OUTPUT);
    pinMode(Encoder_L, OUTPUT);

    ledcSetup(R_PWM_channel, 5000, 8);
    ledcAttachPin(BLDC_R_PWM, R_PWM_channel);

    ledcSetup(L_PWM_channel, 5000, 8);
    ledcAttachPin(BLDC_L_PWM, L_PWM_channel);
}

void base_controller::SteperSetting()
{
    pinMode(STEP_R, OUTPUT);
    pinMode(DIR_R, OUTPUT);
    pinMode(STEP_L, OUTPUT);
    pinMode(DIR_L, OUTPUT);

    RightStepper.setMaxSpeed(3200);
    RightStepper.setSpeed(1600);
    LeftStepper.setMaxSpeed(3200);
    LeftStepper.setSpeed(1600);
}

void MotorDrive(float PWM)
{
    ledcWrite(R_PWM_channel, PWM);
    ledcWrite(L_PWM_channel, PWM);
}

void Steering(float thetaR, float thetaL)
{

    thetaR = thetaR * (PI / 180);
    thetaL = thetaL * (PI / 180);

    int R_pulse = thetaR / Pulse2Deg;
    int L_pulse = thetaL / Pulse2Deg;

    RightStepper.runToNewPosition(R_pulse);
    LeftStepper.runToNewPosition(L_pulse);
}