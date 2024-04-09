#ifndef BASE_CONFIG_H
#define BASE_CONFIG_H

//* STEPPER　MOTOR CONSTANT
#define SStepAngle = 1.8
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

#define ENCODER_R = 19;
#define ENCODER_L = 18;

//* PWM channels
#define R_PWM_CHANNEL = 0;
#define L_PWM_CHANNEL = 1;


//* Robot significant
#define TRACK = 1120; // wheel axle spacing
#define WHELLBASE = 750;  // wheel spacing`l``

#endif