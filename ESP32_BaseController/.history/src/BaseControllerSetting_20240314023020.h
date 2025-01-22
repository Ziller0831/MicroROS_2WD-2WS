#include <Arduino.h>

#include <AccelStepper.h>
#include <MultiStepper.h>
#include <math.h>


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

int RobotVelocity;
int RobotAngle;
