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
    shotPullBack(127);
}

void SpinOut::autonomous()
{
    robot->forward(3, 80, 2.2);
    robot->turn(90, 50, 2.2);
    robot->forward(21, 80, 2.2);
    spinIntake(127);
    robot->turn(90, 50, 2.2);
    robot->forward(5, 50, 2.2);

    pros::delay(400);
    
    spinIntake(0);
    // robot->forward(5, 80, 2.2);
    // spinIntake(127);
    // pros::delay(1000);
    // spinIntake(0);
}

void SpinOut::opcontrolLoop()
{   
    if (robot->masterController.rArrow) stringShooter.set_value(true);

    if (robot->masterController.a) {
        pullingBack = false;
        winchSpin = !winchSpin;
    }

    if (winchSpin) {
        spinWinch(-127);
    } else {
        spinWinch(0);
    }

    if (pullingBack) {
        if (!button.get_value()){
            spinWinch(-127);
        } else {
            pullingBack = false;
        }
    }
    
    if (robot->masterController.leftBumper1) {
        spinIntake(-INTAKE_SPEED);
    } else if (robot->masterController.leftBumper2) {
        spinIntake(INTAKE_SPEED);
    } else {
        spinIntake(0);
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
    pros::delay(750);

    launch.set_value(true);

    shotPullBack(127);
}
