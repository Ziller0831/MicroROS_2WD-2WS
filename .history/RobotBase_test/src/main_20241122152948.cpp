#include <Arduino.h>

#include <AccelStepper.h>
#include <MultiStepper.h>

#include "kinematic.h"
#include "base_config.h"
#include "Base_controller.h"

//* 宣告運動學
Kinematics kinematics(
    Kinematics::ROBOT_2WD2WS,
    MAX_BLDC_vel,
    WHEEL_DIAMETER,
    WHEELBASE,
    TRACK);

//* 宣告左右BLDC馬達控制器物件
BLDC bldcR_controller(false, BLDC_R_PWM, R_PWM_CHANNEL, BLDC_R_REV, PWM_OFFSET, PWM_RESOLUTION);
BLDC bldcL_controller(false, BLDC_L_PWM, L_PWM_CHANNEL, BLDC_L_REV, PWM_OFFSET, PWM_RESOLUTION);

//* 宣告左右轉向步進馬達物件
AccelStepper R_Stepper(AccelStepper::DRIVER, STEP_R, DIR_R);
AccelStepper L_Stepper(AccelStepper::DRIVER, STEP_L, DIR_L);
MultiStepper steering_steppers;

void setup()
{
  R_Stepper.setMaxSpeed(7600 * 1.5); //* pulse
  R_Stepper.setAcceleration(12000 / 4);
  R_Stepper.setSpeed(12000);

  L_Stepper.setMaxSpeed(7600 * 1.5);
  R_Stepper.setAcceleration(12000 / 4);
  L_Stepper.setSpeed(12000);

  steering_steppers.addStepper(R_Stepper);
  steering_steppers.addStepper(L_Stepper);
}

void loop()
{
}
