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
    winchLeft.set_reversed(true);
    shotPullBack(127);
}

void SpinOut::autonomous()
{
}

void SpinOut::opcontrolLoop()
{   
    if (robot->masterController.rArrow) stringShooter.set_value(true);

    if (robot->masterController.rightBumper1) toggledIntake = !toggledIntake;

    if (pullingBack) {
        if (!button.get_value()){
            spinWinch(-127);
        } else {
            pullingBack = false;
        }
    } else {
        if (toggledIntake) {
            spinWinch(127);
        } else {
            spinWinch(0);
        }
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
