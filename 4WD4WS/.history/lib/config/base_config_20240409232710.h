#ifndef BASE_CONFIG_H
#define BASE_CONFIG_H

//* STEPPER　MOTOR CONSTANT
#define STEP_ANGLE = 1.8
#define MICRO_STEP = 16
#define GEAR_RATIO = 10
#define PULSE_TO_DEG = 360 / ((360 / STEP_ANGLE) * MICRO_STEP * GEAR_RATIO)

//* STEPPER MOTOR PINS
#define DIR_R = 12
#define STEP_R = 14

#define DIR_L = 2
#define STEP_L = 15


//* BLDC MOTOR PINS
#define BLDC_R_PWM = 26
#define BLDC_L_PWM = 27

#define BLDC_R_REV = 16
#define BLDC_L_REV = 4

#define ENCODER_R = 19
#define ENCODER_L = 18

//* PWM channels
#define R_PWM_CHANNEL = 0
#define L_PWM_CHANNEL = 1


//* Robot significant
#define TRACK = 1120 // wheel axle spacing
#define WHEELBASE = 750  // wheel spacing`l``

#endif