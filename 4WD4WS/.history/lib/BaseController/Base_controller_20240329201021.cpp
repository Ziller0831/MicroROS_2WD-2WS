#include "Base_controller.h"
#include <AccelStepper.h>
#include <MultiStepper.h>
#include <math.h>

AccelStepper RightStepper(AccelStepper::DRIVER, STEP_R, DIR_R);
AccelStepper LeftStepper(AccelStepper::DRIVER, STEP_L, DIR_L);
MultiStepper steppers;

AckermannPara RobotSteer;

void BLDCSetting()
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

void SteperSetting()
{
    pinMode(STEP_R, OUTPUT);
    pinMode(DIR_R, OUTPUT);
    pinMode(STEP_L, OUTPUT);
    pinMode(DIR_L, OUTPUT);

    RightStepper.setMaxSpeed(3200);
    RightStepper.setSpeed(1600);
    LeftStepper.setMaxSpeed(3200);
    LeftStepper.setSpeed(1600);

    steppers.addStepper(RightStepper);
    steppers.addStepper(LeftStepper);
}

void MotorDrive(float Right_BLDC_vel, float Left_BLDC_vel)
{

    ledcWrite(R_PWM_channel, Right_BLDC_vel);
    ledcWrite(L_PWM_channel, Left_BLDC_vel);
}

void SteeperSteering(float Right_steer_ang, float Left_steer_ang)
{
    Right_steer_ang = Right_steer_ang * (PI / 180);
    Left_steer_ang = Left_steer_ang * (PI / 180);

    double Pulse2Deg = 360 / ((360 / StepAngle) * MicroStep * GearRatio);

    Pulse[0] = Right_steer_ang / Pulse2Deg;
    Pulse[1] = Left_steer_ang / Pulse2Deg;
    
    steppers.moveTo(Pulse);
    steppers.runSpeedToPosition();
}