#include "Arduino.h"
#include "kinematic.h"

Kinematics::Kinematics(base robot_base, int motor_max_rpm, float wheelDiameter,
                       float wheelsBase, float track) : base_platform(robot_base),
                                                        max_rpm_(motor_max_rpm),
                                                        wheelsBase_(base_platform == DIFFERENTIAL_DRIVE ? 0 : wheelsBase),
                                                        track_(track),
                                                        wheel_circumference_(PI * wheelDiameter)

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

    linear_x_mins = linear_x * 60; //* m/s -> 

    MotionControlData MCD;
}

Kinematics::MotionControlData Kinematics::selfRotate(float rotate_vel)
{

}