#ifndef __BASE_CONFIG_H__
#define __BASE_CONFIG_H__

//* STEPPER　MOTOR CONSTANT
#define STEP_ANGLE 1.8
#define MICRO_STEP 16
#define STEP_GEAR_RATIO 10
#define DEG_TO_PUL 360 / ((360 / STEP_ANGLE) * MICRO_STEP * STEP_GEAR_RATIO)

//* STEPPER MOTOR PINS
#define DIR_R 12
#define STEP_R 14

#define DIR_L 2
#define STEP_L 15

//* BLDC MOTOR PINS
#define BLDC_R_PWM 26
#define BLDC_L_PWM 27

#define BLDC_R_REV 16
#define BLDC_L_REV 4

//* ENCODER PINS
#define ENC_L_A 39
#define ENC_L_B 36
#define ENC_R_A 34
#define ENC_R_B 35

//* PWM channels
#define R_PWM_CHANNEL 0
#define L_PWM_CHANNEL 1
#define PWM_RESOLUTION 10
#define PWM_OFFSET 440

//* Robot significant
#define TRACK 1120
#define WHEELBASE 730
#define WHEEL_DIAMETER 13 // 吋
#define MAX_BLDC_vel 2
#define BLDC_GEAR_RATIO 4

#define PULSE_PER_REVOLUTION 20
#define SAMPLING_TIME 100

#endif