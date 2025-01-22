#include "Arduino.h"
#include "Kinematic.h"

Kinematics::Kinematics(base robot_base, float motor_max_vel,
                       int wheelDiameter, float wheelBase,
                       float track) : eBasePlatform(robot_base),
                                      _fWheelCircumference(PI * wheelDiameter * 0.0254),
                                      _iMaxRPM(motor_max_vel * (60 / (PI * wheelDiameter * 0.0254)) * 4),
                                      _fWheelBase(eBasePlatform == DIFFERENTIAL_DRIVE ? 0 : wheelBase),
                                      _fTrack(track),
                                      _degree2pulse(DEG_TO_PUL) {};

//% 逆向運動學選擇
Kinematics::CP Kinematics::inverseKinematics(
    float linear_x,
    float center_rotation_rad,
    int center_rotation_angle,
    short int turning_mode)
{
    MCommand mCommand;
    MControl mControl;
    CP converterParameters;

    mCommand.linear_x = linear_x;
    mCommand.center_rotation_rad = center_rotation_rad;
    mCommand.center_rotation_angle = center_rotation_angle;
    mCommand.turning_mode = turning_mode;

    if (mCommand.turning_mode == ACKERMAN)
        mControl = ackerman(&mCommand);
    else if (mCommand.turning_mode == SELF_ROTATION)
        mControl = selfRotation(&mCommand);

    converterParameters = baseOrderConvert(&mControl);

    return converterParameters;
}

//% 阿克曼轉向運動學
Kinematics::MControl Kinematics::ackerman(MCommand *mCommand)
{
    MControl mControl;

    float center_rotation_rad;
    float theta_center;
    float angle_R, angle_L;
    float vel_R, vel_L;

    float linear_x_mm = mCommand->linear_x * 1000; // m/s -> mm/s

    //@ Ackerman parameter calc
    //* rotation radius input
    if (mCommand->center_rotation_rad != 0 && mCommand->center_rotation_angle == 0)
    {
        center_rotation_rad = mCommand->center_rotation_rad * 1000;
        theta_center = asin(_fTrack / (2 * center_rotation_rad));
    }
    //* center rotation angle input
    else if (mCommand->center_rotation_rad == 0 && mCommand->center_rotation_angle != 0)
    {
        theta_center = mCommand->center_rotation_angle * DEG_TO_RAD;
        center_rotation_rad = _fTrack / (2 * sin(theta_center));
    }
    //* forward/backward
    else
    {
        mControl.rpm.BLDC_L = (linear_x_mm / 1000) * (60 / _fWheelCircumference) * BLDC_GEAR_RATIO;
        mControl.rpm.BLDC_R = (linear_x_mm / 1000) * (60 / _fWheelCircumference) * BLDC_GEAR_RATIO;
        // mControl.rpm.BLDC_R = 0;
        // mControl.rpm.BLDC_L = 0;
        mControl.angle.STEPPER_L = 0;
        mControl.angle.STEPPER_R = 0;
        return mControl;
    }

    float rotation_rad = center_rotation_rad * cos(theta_center);
    float theta_ack = atan(_fWheelBase / rotation_rad) * RAD_TO_DEG;

    float abs_center_rotation_rad = abs(center_rotation_rad);
    rotation_rad = abs(rotation_rad);

    float R_short = rotation_rad - _fTrack / 2;
    float R_long = rotation_rad + _fTrack / 2;

    //@ Angle calc
    //* 順時針
    if (center_rotation_rad > 800)
    {
        angle_R = atan(_fWheelBase / R_long);
        angle_L = atan(_fWheelBase / R_short);

        vel_R = (R_short / cos(angle_R)) / abs_center_rotation_rad * linear_x_mm;
        vel_L = (R_long / cos(angle_L)) / abs_center_rotation_rad * linear_x_mm;
    } //* 逆時針
    else if (center_rotation_rad < -800)
    {
        angle_R = -atan(_fWheelBase / R_short);
        angle_L = -atan(_fWheelBase / R_long);

        vel_R = (R_long / cos(angle_R)) / abs_center_rotation_rad * linear_x_mm;
        vel_L = (R_short / cos(angle_L)) / abs_center_rotation_rad * linear_x_mm;
    }

    mControl.angle.STEPPER_R = angle_R * RAD_TO_DEG;
    mControl.angle.STEPPER_L = angle_L * RAD_TO_DEG;

    mControl.rpm.BLDC_L = (vel_L / 1000) * (60 / _fWheelCircumference) * BLDC_GEAR_RATIO;
    mControl.rpm.BLDC_R = (vel_R / 1000) * (60 / _fWheelCircumference) * BLDC_GEAR_RATIO;

    return mControl;
}

//% 自轉運動學
Kinematics::MControl Kinematics::selfRotation(MCommand *mCommand)
{
    MControl mControl;
    float rotation_speed = mCommand->center_rotation_angle;

    mControl.angle.STEPPER_R = atan(_fWheelBase / (_fTrack / 2)) * RAD_TO_DEG;
    mControl.angle.STEPPER_L = -atan(_fWheelBase / (_fTrack / 2)) * RAD_TO_DEG;

    //* 順時針
    if (rotation_speed > 0.2)
    {
        mControl.rpm.BLDC_L = 2 * (60 / _fWheelCircumference) * BLDC_GEAR_RATIO;
        mControl.rpm.BLDC_R = -(2 * (60 / _fWheelCircumference) * BLDC_GEAR_RATIO);

    } //* 逆時針
    else if (rotation_speed < -0.2)
    {
        mControl.rpm.BLDC_L = -(2 * (60 / _fWheelCircumference) * BLDC_GEAR_RATIO);
        mControl.rpm.BLDC_R = 2 * (60 / _fWheelCircumference) * BLDC_GEAR_RATIO;
    }
    else
    {
        mControl.rpm.BLDC_R = 0;
        mControl.rpm.BLDC_L = 0;
    }

    return mControl;
}

//% 命令轉換成控制指令
Kinematics::CP Kinematics::baseOrderConvert(MControl *mControl)
{
    CP converterParameters;

    converterParameters.pulse.STEPPER_R = mControl->angle.STEPPER_R / _degree2pulse;
    converterParameters.pulse.STEPPER_L = mControl->angle.STEPPER_L / _degree2pulse;

    converterParameters.pwm.BLDC_R = mControl->rpm.BLDC_R * (_max_pwm / _iMaxRPM);
    converterParameters.pwm.BLDC_L = mControl->rpm.BLDC_L * (_max_pwm / _iMaxRPM);

    return converterParameters;
}