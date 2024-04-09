#include "Arduino.h"
#include "kinematic.h"

Kinematics::Kinematics(base robot_base, int motor_max_rpm, float wheelDiameter, 
                        float wheelsBase, float track): base_platform(robot_base),
                                                        