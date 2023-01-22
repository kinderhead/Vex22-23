#pragma once

// Forward declaration
class Robot;

class DriveTrain
{
public:
    Robot* robot;

    DriveTrain(Robot* robot);

    void rightMotors(double speed);
    void rightMotorsVelocity(double speed);
    void leftMotors(double speed);
    void leftMotorsVelocity(double speed);

    double getLeftEncoders();
    double getRightEncoders();
};
