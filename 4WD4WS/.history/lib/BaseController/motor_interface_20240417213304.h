#ifndef MOTOR_INTERFACE
#define MOTOR_INTERFACE

class MotorInterface
{
    bool invert_;

protected:
    virtual void forward(int pwm) = 0;
    virtual void reverse(int pwm) = 0;

public:
    MotorInterface(int invert) : invert_(invert)
    {
    }

    virtual void brake() = 0;

    virtual void driveBase(int pwm);
};

#endif