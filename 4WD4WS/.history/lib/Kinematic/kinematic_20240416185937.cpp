#include "Arduino.h"
#include "kinematic.h"

Kinematics::Kinematics(base robot_base,
                       int motor_max_rpm,
                       float wheelDiameter,
                       float wheelBase,
                       float track)
    : eBasePlatform_(robot_base),
      iMaxRpm_(motor_max_rpm),
      fWheelBase_(eBasePlatform_ == DIFFERENTIAL_DRIVE ? 0 : wheelBase),
      fTrack_(track),
      fWheelCircumference_(PI * wheelDiameter * 0.0254){};

Kinematics::MControl Kinematics::inverseKinematics(MCommand *mCommand)
{
    if (eBasePlatform_ == ACKERMAN)
    {
    }
    // else if (eBasePlatform_ == ACKERMAN_SELF_ROTATE)
    // {
    // }
}

Kinematics::MControl Kinematics::ackerman(MCommand *mCommand)
{
    float linear_x_mins;
    float center_rotation_rad, rotation_rad;
    float turning_angle;
    float theta_center, theta_ack;
    float R_long, R_short;
    float angle_R, angle_L;
    float vel_R, vel_L;

    linear_x_mins = mCommand->linear_x * 1000;                  //* m/s -> mm/s
    center_rotation_rad = mCommand->center_rotation_rad * 1000; //* m -> mm

    theta_center = asin(TRACK / (2 * center_rotation_rad));
    rotation_rad = center_rotation_rad * cos(theta_center);

    theta_ack = RAD_TO_DEG * (atan(WHEELBASE / rotation_rad));

    float abs_center_rotation_rad = abs(center_rotation_rad);
    rotation_rad = abs(rotation_rad);

    R_long = rotation_rad + TRACK / 2;
    R_short = rotation_rad - TRACK / 2;

    MControl mControl;

    if (center_rotation_rad > 800 && turning_angle > 0)
    {
        angle_R = atan(WHEELBASE / R_short);
        angle_L = atan(WHEELBASE / R_long);

        vel_R = (R_short / cos(angle_R)) / abs_center_rotation_rad * linear_x_mins;
        vel_L = (R_short / cos(angle_R)) / abs_center_rotation_rad * linear_x_mins;
    }
    else if (center_rotation_rad < -800 && turning_angle > 0)
    {
        angle_R = atan(WHEELBASE / R_long) * RAD_TO_DEG;
        angle_L = atan(WHEELBASE / R_short) * RAD_TO_DEG;
    }
    else if (center_rotation_rad)
    {
        angle_R = 0;
        angle_L = 0;
    }

    mControl.angle.STEPPER_R = angle_R * RAD_TO_DEG;
    mControl.angle.STEPPER_L = angle_L * RAD_TO_DEG;

    return mControl;
}
