#include "drive_train.hpp"
#include "robot.hpp"

DriveTrain::DriveTrain(Robot* robot)
{
    this->robot = robot;
}

void DriveTrain::rightMotors(double speed)
{
    robot->rightTop.move(speed);
    robot->rightFront.move(speed);
    robot->rightBack.move(speed);
}

void DriveTrain::rightMotorsVelocity(double speed)
{
    robot->rightTop.move_velocity(speed);
    robot->rightFront.move_velocity(speed);
    robot->rightBack.move_velocity(speed);
}

void DriveTrain::leftMotors(double speed)
{
    robot->leftTop.move(speed);
    robot->leftFront.move(speed);
    robot->leftBack.move(speed);
}

void DriveTrain::leftMotorsVelocity(double speed)
{
    robot->leftTop.move_velocity(speed);
    robot->leftFront.move_velocity(speed);
    robot->leftBack.move_velocity(speed);
}

double DriveTrain::getLeftEncoders()
{
    return robot->leftTop.get_raw_position(NULL);
}

double DriveTrain::getRightEncoders()
{
    return robot->rightTop.get_raw_position(NULL);
}
