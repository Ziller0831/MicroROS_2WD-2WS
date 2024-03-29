/*
 * Pulse2Deg  輪子轉一圈要的脈衝數
 @ (360/1.8)*16*10 = 32000  1 pulse = 0.01125 degree
 *
*/

#ifndef BASE_CONTROL_H
#define BASE_CONTROL_H

#include <Arduino.h>

//* Pin definitions
const int DIR_R = 12;
const int STEP_R = 14;
const int DIR_L = 2;
const int STEP_L = 15;

const int BLDC_R_PWM = 26;
const int BLDC_L_PWM = 27;
const int BLDC_R_rev = 16;
const int BLDC_L_rev = 4;
const int Encoder_R = 19;
const int Encoder_L = 18;

//* PWM channels
#define R_PWM_channel 0
#define L_PWM_channel 1

//* Steper_constant
const float StepAngle = 1.8;
const int MicroStep = 16;
const int GearRatio = 10; // 10:1


long Pulse[2];

void BLDCSetting();
void SteperSetting();
void MotorDrive(float linear_vel);
void SteeperSteering(float Right_steer_ang, float Left_steer_ang)l

#endif