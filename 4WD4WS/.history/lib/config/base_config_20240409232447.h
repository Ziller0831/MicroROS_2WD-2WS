#ifndef BASE_CONFIG_H
#define BASE_CONFIG_H

//* STEPPER　MOTOR CONSTANT
#define StepAngle = 1.8
#define MicroStep = 16
#define GearRatio = 10
#define Pulse2Deg = 360 / ((360 / StepAngle) * MicroStep * GearRatio)

//* STEPPER MOTOR PINS
#define DIR_R = 12;
#define STEP_R = 14;

#define DIR_L = 2;
#define STEP_L = 15;


//* BLDC MOTOR PINS
#define BLDC_R_PWM = 26;
#define BLDC_L_PWM = 27;

#define BLDC_R_REV = 16;
#define BLDC_L_REV = 4;

const int Encoder_R = 19;
const int Encoder_L = 18;

//* PWM channels
const int R_PWM_CHANNEL = 0;
const int L_PWM_CHANNEL = 1;


//* Robot significant
const int  = 1120; // wheel axle spacing
const int Wheel = 750;  // wheel spacing`l``

#endif