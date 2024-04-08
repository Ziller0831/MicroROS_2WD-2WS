/*
 * Pulse2Deg  輪子轉一圈要的脈衝數
 @ (360/1.8)*16*10 = 32000  1 pulse = 0.01125 degree
 *
*/

#ifndef BASE_CONTROLLER_H
#define BASE_CONTROLLER_H

#include <Arduino.h>



//* PWM channels
#define R_PWM_channel 0
#define L_PWM_channel 1

//* Steper_constant
const float StepAngle = 1.8;
const int MicroStep = 16;
const int GearRatio = 10; // 10:1

int Right_CurrPos;
int Left_CurrPos;

void BLDCSetting();
void SteperSetting();
void MotorDrive(float PWM);
void Steering(float thetaR, float thetaL);

#endif