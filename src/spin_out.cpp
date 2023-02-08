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
        spinCatapult(-127);
    } else {
        spinCatapult(0);
    }

    if (pullingBack) {
        if (!button.get_value()){
            spinCatapult(-127);
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

void SpinOut::spinCatapult(double speed)
{
    catapult.move(speed);
}

void SpinOut::spinCatapultVelocity(double speed)
{
    catapult.move_velocity(speed);
}

void SpinOut::launchDisks()
{
    spinCatapult(0);

    launch.set_value(false);
    pros::delay(750);

    launch.set_value(true);
}
