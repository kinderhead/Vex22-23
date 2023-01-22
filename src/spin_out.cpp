#include "spin_out.h"

#include "robot.h"

SpinOut::SpinOut()
{

}

void SpinOut::initialize()
{
    winchLeft.set_reversed(true);
}

void SpinOut::autonomous()
{
}

void SpinOut::opcontrolLoop()
{
    if (toggledIntake) {
        spinWinch(127);
    } else {
        spinWinch(0);
    }

    if (robot->masterController.y) toggledIntake = !toggledIntake;
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
