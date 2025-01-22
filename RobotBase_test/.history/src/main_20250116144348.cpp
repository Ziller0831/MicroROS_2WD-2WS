#include <Arduino.h>

#include <AccelStepper.h>
#include <MultiStepper.h>
#include <Esp32PcntEncoder.h>

#include "base_config.h"
#include "Kinematic.h"
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

// //* 宣告左右BLDC的Hall Encoder物件
Esp32PcntEncoder R_Encoder;
Esp32PcntEncoder L_Encoder;

void moveBase(float linear_x, float center_rotation_angle)
{
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

  R_Encoder.init(0, ENC_R_A, ENC_R_B);
  L_Encoder.init(1, ENC_L_A, ENC_L_B);
}

void loop()
{
  if (Serial.available() > 0)
  {
    String data = Serial.readString();
    float linear_x = data.substring(0, data.indexOf(",")).toFloat();
    Serial.println("linear_x: " + String(linear_x) + " center_rotation_angle: " + S float center_rotation_angle = data.substring(data.indexOf(",") + 1).toFloat(); tring(center_rotation_angle));
    moveBase(linear_x, 0);
  }

  Serial.printf("tick1=%d,tick2=%d\n", R_Encoder.getTicks(), L_Encoder.getTicks());
}
