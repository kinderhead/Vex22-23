#include "spin_out.hpp"

#include "robot.hpp"

SpinOut::SpinOut()
{

}

void SpinOut::initialize()
{
    stringShooter.set_value(false);
    launch.set_value(false);
    winchLeft.set_reversed(true);
    //shotPullBack(127);
}

void SpinOut::autonomous()
{
}

void SpinOut::opcontrolLoop()
{   
    if (robot->masterController.rArrow) stringShooter.set_value(true);

    if (robot->masterController.rightBumper1) toggledIntake = !toggledIntake;
    if (toggledIntake) {
        spinWinch(127);
    } else {
        spinWinch(0);
    }

    if (robot->masterController.y) launchDisks();
}

void SpinOut::spinWinch(double speed)
{
    winchLeft.move(speed);
    winchRight.move(speed);
}

void SpinOut::spinWinchVelocity(double speed)
{
    winchLeft.move_velocity(speed);
    winchRight.move_velocity(speed);
}

void SpinOut::shotPullBack(double speed)
{

    while(!button.get_value()){
        spinWinch(-speed);
    }

    spinWinch(0);
}

void SpinOut::launchDisks()
{
    spinWinch(0);

    launch.set_value(true);
    pros::delay(100);

    shotPullBack(127);
}
