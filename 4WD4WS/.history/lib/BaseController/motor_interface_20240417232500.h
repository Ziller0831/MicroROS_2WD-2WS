#ifndef __MOTOR_INTERFACE_H__
#define __MOTOR_INTERFACE_H__

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

    void spin(int pwm)
    {
        if (invert_)
            pwm *= -1;

        if (pwm > 0)
            forward(pwm);
        else if (pwm < 0)
            reverse(pwm);
        else
            brake();
    }
};

#endif