#include <Arduino.h>
#include <micro_ros_platformio.h>

#include <AccelStepper.h>
#include <MultiStepper.h>
#include <math.h>

#include <rcl/rcl.h>
#include <rclc/rclc.h>
#include <rclc/executor.h>

#include <std_msgs/msg/int32.h>
#include <ge

const int DIR_R = 12;
const int STEP_R = 14;
const int DIR_L = 2;
const int STEP_L = 15;

const float StepAngle = 1.8;
const int MicroStep = 16;
const int GearRatio = 10; // 10:1

const int BLDC_R_PWM = 26;
const int BLDC_L_PWM = 27;
const int BLDC_R_rev = 16;
const int BLDC_L_rev = 4;
const int Encoder_R = 19;
const int Encoder_L = 18;

AccelStepper RightStepper(AccelStepper::DRIVER, STEP_R, DIR_R);
AccelStepper LeftStepper(AccelStepper::DRIVER, STEP_L, DIR_L);
MultiStepper steppers;

int RobotVelocity;
int RobotAngle;

//* 輪子轉一圈要的脈衝數
double Pulse2Deg = 360 / ((360 / StepAngle) * MicroStep * GearRatio); // (360/1.8)*16*10 = 32000  1 pulse = 0.01125 degree

float Angle;
long Pulse[2];

typedef struct ackermannPara
{
    const int T = 1120;     // wheel axle spacing
    const int L = 750;      // wheel spacing

    float R; //

    float thetaR;
    float thetaL;
} AckermannPara;

AckermannPara RobotSteer;

void AckermannSteering(float Robot_yaw);