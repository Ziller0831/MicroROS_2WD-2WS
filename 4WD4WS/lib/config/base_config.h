#ifndef BASE_CONFIG_H
#define BASE_CONFIG_H

//* STEPPER　MOTOR CONSTANT
const float StepAngle = 1.8;
const int MicroStep = 16;
const int GearRatio = 10;

//* STEPPER MOTOR PINS
const int DIR_R = 12;
const int STEP_R = 14;

const int DIR_L = 2;
const int STEP_L = 15;

double Pulse2Deg = 360 / ((360 / StepAngle) * MicroStep * GearRatio);

//* BLDC MOTOR PINS
const int BLDC_R_PWM = 26;
const int BLDC_L_PWM = 27;

const int BLDC_R_REV = 16;
const int BLDC_L_REV = 4;

const int Encoder_R = 19;
const int Encoder_L = 18;

//* PWM channels
const int R_PWM_CHANNEL = 0;
const int L_PWM_CHANNEL = 1;


//* Ackermann parameter
typedef struct ackermannPara
{
    const int T = 1120; // wheel axle spacing
    const int L = 750;  // wheel spacing`l``

    float R;

    float thetaR;
    float thetaL;
} AckermannPara;

#endif