#include <Arduino.h>

#include <AccelStepper.h>
#include <MultiStepper.h>

#include "base_config.h"
#include "Kinematic.h"
#include "Base_controller.h"
#include "BldcHallEncoder.h"

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

//* 宣告左右BLDC的Hall Encoder物件
BldcHallEncoder bldcR_encoder;
// BldcHallEncoder bldcL_encoder;

void moveBase(float linear_x, float center_rotation_angle)
{
  // float linear_x;
  // float center_rotation_rad;
  // float center_rotation_angle;
  // int turning_mode;

  // linear_x = linear_x;
  // center_rotation_rad = 0;
  // center_rotation_angle = ;
  // turning_mode = 0;

  Kinematics::CP req_convertPara = kinematics.inverseKinematics(
      linear_x,
      0,
      center_rotation_angle,
      0);

  bldcL_controller.spin(req_convertPara.pwm.BLDC_L);
  bldcR_controller.spin(req_convertPara.pwm.BLDC_R);

  long stepperPulse[2] = {req_convertPara.pulse.STEPPER_R, req_convertPara.pulse.STEPPER_L};
  steering_steppers.moveTo(stepperPulse);
  steering_steppers.runSpeedToPosition();
}

void setup()
{
  Serial.begin(115200);
  R_Stepper.setMaxSpeed(7600 * 1.5); //* pulse
  R_Stepper.setAcceleration(12000 / 4);
  R_Stepper.setSpeed(12000);

  L_Stepper.setMaxSpeed(7600 * 1.5);
  R_Stepper.setAcceleration(12000 / 4);
  L_Stepper.setSpeed(12000);

  steering_steppers.addStepper(R_Stepper);
  steering_steppers.addStepper(L_Stepper);

  bldcR_encoder.init(0, ENCODER_R, 20);
}

void loop()
{
  if (Serial.available() > 0)
  {
    String data = Serial.readString();
    float linear_x = data.substring(0, data.indexOf(",")).toFloat();
    float center_rotation_angle = data.substring(data.indexOf(",") + 1).toFloat();
    Serial.println("linear_x: " + String(linear_x) + " center_rotation_angle: " + String(center_rotation_angle));
    moveBase(linear_x, center_rotation_angle);
  }
}
