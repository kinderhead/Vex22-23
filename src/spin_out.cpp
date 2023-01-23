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
    launch.set_value(false);
    
    if (robot->masterController.uArrow) stringShooter.set_value(true);

    if (robot->masterController.y) toggledIntake = !toggledIntake;
    if (toggledIntake) {
        spinWinch(127);
    } else {
        spinWinch(0);
    }
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
    pros::delay(20);

    while(!button.get_value()){
        spinWinch(-speed);
    }

    spinWinch(0);
}
