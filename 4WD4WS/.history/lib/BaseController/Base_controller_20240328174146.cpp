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

void MotorDrive(float linear_vel)
{
    int PWM = int(linear_vel);
    ledcWrite(R_PWM_channel, PWM);
    ledcWrite(L_PWM_channel, PWM);
    Serial.print(PWM);
    // if (linear_vel > 0)
    // {
    //     digitalWrite(BLDC_R_rev, LOW);
    //     ledcWrite(R_PWM_channel, PWM);
    //     digitalWrite(BLDC_L_rev, LOW);
    //     ledcWrite(L_PWM_channel, PWM);
    // }
    // else if (linear_vel < 0)
    // {
    //     digitalWrite(BLDC_R_rev, HIGH);
    //     ledcWrite(R_PWM_channel, PWM);
    //     digitalWrite(BLDC_L_rev, HIGH);
    //     ledcWrite(L_PWM_channel, PWM);
    // }
    // else if (linear_vel == 0)
    // {
    //     ledcWrite(R_PWM_channel, 0);
    //     ledcWrite(L_PWM_channel, 0);
    // }
}

void Ackermann(float steer_angle)
{
    steer_angle = steer_angle * (PI / 180);

    double Pulse2Deg = 360 / ((360 / StepAngle) * MicroStep * GearRatio);
    float Angle;
    long Pulse[2];

    if (steer_angle != 0)
    {
        RobotSteer.R = (RobotSteer.L / 2) / tan(steer_angle);
        RobotSteer.thetaR = atan(RobotSteer.L / (RobotSteer.R - (RobotSteer.T / 2))) * (180 / PI);
        RobotSteer.thetaL = -atan(RobotSteer.L / (RobotSteer.R + (RobotSteer.T / 2))) * (180 / PI);
    }
    else if (steer_angle == 0)
    {
        RobotSteer.thetaR = 0;
        RobotSteer.thetaL = 0;
    }
    
    Serial.print(RobotSteer.thetaR);
    Serial.print(RobotSteer.thetaL);

    Pulse[0] = RobotSteer.thetaR / Pulse2Deg;
    Pulse[1] = RobotSteer.thetaL / Pulse2Deg;
    steppers.moveTo(Pulse);
    steppers.runSpeedToPosition();
}