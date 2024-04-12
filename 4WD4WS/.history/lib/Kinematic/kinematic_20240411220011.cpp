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

Kinematics::MControl Kinematics::inverseKinematics(MCommand *mCommand)
{
    if (eBasePlatform_ == ACKERMAN)
    {
    }
    else if (eBasePlatform_ == ACKERMAN_SELF_ROTATE)
    {
    }
}

Kinematics::MControl Kinematics::ackerman(MCommand *mCommand)
{
    float linear_x_mins;
    float rad_of_turningCircle;
    float steer_angle;

    linear_x_mins = mCommand->linear_x * 60;  //* m/s -> m/min
    steer_angle = mCommand->rotate_z * (PI / 180); //* rad -> degree

    rad_of_turningCircle = (fWheelBase_) / tan(steer_angle);

    MControl mControl;

    if (steer_angle != 0)
    {
        mControl.angle.STEPPER_R = atan(fWheelBase_ / (rad_of_turningCircle + (fTrack_ / 2))) * (180 / PI);
        mControl.angle.STEPPER_L = -atan(fWheelBase_ / (rad_of_turningCircle - (fTrack_ / 2))) * (180 / PI);
    }
    else if (steer_angle == 0)
    {
        mControl.angle.STEPPER_R = 0;
        mControl.angle.STEPPER_L = 0;
    }

    return mControl;
}


