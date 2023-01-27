#include "spin_out.hpp"

#include "robot.hpp"

SpinOut::SpinOut()
{

}

void SpinOut::initialize()
{
    stringShooter.set_value(false);
    // Launch solenoid is reversed for some reason
    launch.set_value(true);
    //shotPullBack(127);
}

void SpinOut::autonomous()
{
}

void SpinOut::opcontrolLoop()
{   
    if (robot->masterController.rArrow) stringShooter.set_value(true);

    if (robot->masterController.leftBumper1) {
        if (intakeSpeed == -INTAKE_SPEED) {
            intakeSpeed = 0;
        } else {
            intakeSpeed = -INTAKE_SPEED;
        }
    }

    if (robot->masterController.leftBumper2) {
        if (intakeSpeed == INTAKE_SPEED) {
            intakeSpeed = 0;
        } else {
            intakeSpeed = INTAKE_SPEED;
        }
    }

    if (pullingBack) {
        if (!button.get_value()){
            spinWinch(-127);
        } else {
            pullingBack = false;
        }
    } else {
        spinIntake(intakeSpeed);
    }

    if (robot->masterController.y) launchDisks();
}

void SpinOut::spinIntake(double speed)
{
    intake.move(speed);
}

void SpinOut::spinWinch(double speed)
{
    winch.move(speed);
}

void SpinOut::spinWinchVelocity(double speed)
{
    winch.move_velocity(speed);
}

void SpinOut::shotPullBack(double speed)
{
    pullingBack = true;

    spinWinch(0);
}

void SpinOut::launchDisks()
{
    spinWinch(0);

    launch.set_value(false);
    pros::delay(100);
    launch.set_value(true);

    shotPullBack(127);
}
