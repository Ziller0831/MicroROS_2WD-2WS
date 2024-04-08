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

const int BLDC_R_rev = 16;
const int BLDC_L_rev = 4;

const int Encoder_R = 19;
const int Encoder_L = 18;

//* PWM channels
const int R_PWM_channel 0
#define L_PWM_channel 1

#endif