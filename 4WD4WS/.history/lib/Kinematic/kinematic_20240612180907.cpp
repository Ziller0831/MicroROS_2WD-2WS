#include "Arduino.h"
#include "kinematic.h"

Kinematics::Kinematics(base robot_base, int motor_max_vel,
                       int wheelDiameter, float wheelBase,
                       float track) : eBasePlatform_(robot_base),
                                      iMaxRPM_(motor_max_vel * (60 / fWheelCircumference_) / 1000),
                                      fWheelBase_(eBasePlatform_ == DIFFERENTIAL_DRIVE ? 0 : wheelBase),
                                      fTrack_(track),
                                      fWheelCircumference_(PI * wheelDiameter * 0.0254),
                                      degree2pulse_(DEG_TO_PUL){};

Kinematics::CP Kinematics::inverseKinematics(
    float linear_x,
    float center_rotation_rad,
    int center_rotation_angle,
    int turning_mode)
{
    MCommand mCommand;
    MControl mControl;
    CP converterParameters;

    mCommand.linear_x = linear_x;
    // mCommand.center_rotation_rad = center_rotation_rad;
    mCommand.center_rotation_angle = center_rotation_angle;
    mCommand.turning_mode = turning_mode;

    if (mCommand.turning_mode == ACKERMAN)
    {
        mControl = ackerman(&mCommand);
        converterParameters = baseOrderConvert(&mControl);
    }
    else if (mCommand.turning_mode == SELF_ROTATION)
    {
        mControl = selfRotation(&mCommand);
        converterParameters = baseOrderConvert(&mControl);
    }

        return converterParameters;
}

Kinematics::MControl Kinematics::ackerman(MCommand *mCommand)
{
    MControl mControl;

    float center_rotation_rad;
    float theta_center;
    float angle_R, angle_L;
    float vel_R, vel_L;

    float linear_x_mm = mCommand->linear_x * 1000; //* m/s -> mm/s

    //* Ackerman parameter calc
    if (mCommand->center_rotation_rad != 0 && mCommand->center_rotation_angle == 0)
    {
        center_rotation_rad = mCommand->center_rotation_rad * 1000;
        theta_center = asin(fTrack_ / (2 * center_rotation_rad));
    }
    else if (mCommand->center_rotation_rad == 0 && mCommand->center_rotation_angle != 0)
    {
        theta_center = mCommand->center_rotation_angle * DEG_TO_RAD;
        center_rotation_rad = fTrack_ / (2 * sin(theta_center));
    }
    else
    {
        mControl.rpm.BLDC_L = linear_x_mm * (60 / fWheelCircumference_) / 1000;
        mControl.rpm.BLDC_R = linear_x_mm * (60 / fWheelCircumference_) / 1000;
        mControl.angle.STEPPER_L = 0;
        mControl.angle.STEPPER_R = 0;
        return mControl;
    }

    float rotation_rad = center_rotation_rad * cos(theta_center);
    float theta_ack = RAD_TO_DEG * (atan(fWheelBase_ / rotation_rad));

    float abs_center_rotation_rad = abs(center_rotation_rad);
    rotation_rad = abs(rotation_rad);

    float R_long = rotation_rad + fTrack_ / 2;
    float R_short = rotation_rad - fTrack_ / 2;

    //* Angle calc
    if (center_rotation_rad > 800)
    {
        angle_R = atan(fWheelBase_ / R_short);
        angle_L = atan(fWheelBase_ / R_long);

        vel_R = (R_short / cos(angle_R)) / abs_center_rotation_rad * linear_x_mm;
        vel_L = (R_long / cos(angle_L)) / abs_center_rotation_rad * linear_x_mm;
    }
    else if (center_rotation_rad < -800)
    {
        angle_R = -atan(fWheelBase_ / R_long);
        angle_L = -atan(fWheelBase_ / R_short);

        vel_R = (R_long / cos(angle_R)) / abs_center_rotation_rad * linear_x_mm;
        vel_L = (R_short / cos(angle_L)) / abs_center_rotation_rad * linear_x_mm;
    }

    mControl.angle.STEPPER_R = angle_R * RAD_TO_DEG;
    mControl.angle.STEPPER_L = angle_L * RAD_TO_DEG;

    mControl.rpm.BLDC_L = vel_L * (60 / fWheelCircumference_) / 1000;
    mControl.rpm.BLDC_R = vel_R * (60 / fWheelCircumference_) / 1000;

    return mControl;
}

Kinematics::MControl Kinematics::selfRotation(MCommand *mCommand)
{
    MControl mControl;
    float rotation_speed = MCommand

    // float linear_x_mm = mCommand->linear_x * 1000; //* m/s -> mm/s
    // float center_rotation_rad = mCommand->center_rotation_rad * 1000;
    // float center_rotation_angle = mCommand->center_rotation_angle * DEG_TO_RAD;

    // float vel_R = linear_x_mm * (60 / fWheelCircumference_) / 1000;
    // float vel_L = linear_x_mm * (60 / fWheelCircumference_) / 1000;

    // float angle_R = center_rotation_angle;
    // float angle_L = center_rotation_angle;

    // mControl.angle.STEPPER_R = angle_R * RAD_TO_DEG;
    // mControl.angle.STEPPER_L = angle_L * RAD_TO_DEG;

    // mControl.rpm.BLDC_L = vel_L;
    // mControl.rpm.BLDC_R = vel_R;

    return mControl;
}

Kinematics::CP Kinematics::baseOrderConvert(MControl *mControl)
{
    CP converterParameters;

    converterParameters.pulse.STEPPER_R = mControl->angle.STEPPER_R / degree2pulse_;
    converterParameters.pulse.STEPPER_L = mControl->angle.STEPPER_L / degree2pulse_;

    converterParameters.pwm.BLDC_R = mControl->rpm.BLDC_R * (1025 / iMaxRPM_);
    converterParameters.pwm.BLDC_L = mControl->rpm.BLDC_L * (1025 / iMaxRPM_);

    return converterParameters;
}