#include "Arduino.h"
#include "kinematic.h"

Kinematics::Kinematics(base robot_base, 
                        int motor_max_rpm, 
                        float wheelDiameter,
                        float wheelBase, 
                        float track) 
                        : 
                        eBasePlatform_(robot_base),
                        iMaxRpm_(motor_max_rpm),
                        fWheelBase_(eBasePlatform_ == DIFFERENTIAL_DRIVE ? 0 : wheelBase),
                        fTrack_(track),
                        fWheelCircumference_(PI * wheelDiameter * 0.0254)
{};

Kinematics::MCD Kinematics::inverseKinematics(Vel *vel)
{
    if (eBasePlatform_ == ACKERMANN)
    {
    }
    else if (eBasePlatform_ == ACKERMANN_SELF_ROTATE)
    {
    }
}

Kinematics::MCD Kinematics::ackermann(Vel *vel)
{
    float linear_x_mins;
    float rad_of_turningCircle;
    float steer_angle;

    linear_x_mins = vel->linear_x * 60;       //* m/s -> m/min
    steer_angle = vel->rotate_z * (PI / 180); //* rad -> degree

    rad_of_turningCircle = (wheelBase_ / 2) / tan(steer_angle);

    MCD mcd;

    if (steer_angle != 0)
    {
        mcd.angle.STEPPER_R = atan(wheelBase_ / (rad_of_turningCircle + (track_ / 2))) * (180 / PI);
        mcd.angle.STEPPER_L = -atan(wheelBase_ / (rad_of_turningCircle - (track_ / 2))) * (180 / PI);
    }
    else if (steer_angle == 0)
    {
        mcd.angle.STEPPER_R = 0;
        mcd.angle.STEPPER_L = 0;
    }

    return mcd;
}

Kinematics::MCD Kinematics::selfRotate(float rotate_vel)
{
}
