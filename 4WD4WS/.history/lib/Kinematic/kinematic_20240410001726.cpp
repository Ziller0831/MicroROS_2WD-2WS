#include "Arduino.h"
#include "kinematic.h"

Kinematics::Kinematics(base robot_base, int motor_max_rpm, float wheelDiameter,
                       float wheelBase, float track) : base_platform(robot_base),
                                                        max_rpm_(motor_max_rpm),
                                                        wheelBase_(base_platform == DIFFERENTIAL_DRIVE ? 0 : wheelBase),
                                                        track_(track),
                                                        wheel_circumference_(PI * wheelDiameter * 0.0254)

{
};

Kinematics::MotionControlData Kinematics::inverseKinematics(float linear_x, float rotate_z)
{
    if (base_platform == ACKERMANN)
    {

    }
    else if (base_platform == ACKERMANN_SELF_ROTATE)
    {

    }
}

Kinematics::MotionControlData Kinematics::ackermann(float linear_x, float steer_angle)
{
    float linear_x_mins;
    float rad_of_turningCircle

        linear_x_mins = linear_x * 60;      //* m/s -> m/min
    steer_angle = steer_angle * (PI / 180); //* rad -> degree
    rad_of_turningCircle = (wheelBase_ / 2) / tan(steer_angle);

    if (steer_angle != 0)
    {

    }

    MotionControlData MCD;
}

Kinematics::MotionControlData Kinematics::selfRotate(float rotate_vel)
{

}