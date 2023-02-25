#include "spin_out.hpp"

#include "robot.hpp"

SpinOut::SpinOut()
{

}

void SpinOut::initialize()
{
    stringShooter.set_value(false);
    // Launch solenoid is reversed for some reason
    //shotPullBack(127);
}

void SpinOut::autonomous()
{
    //both sides plus shot
    // spinIntake(127);
    // robot->forward(3, 127, 2.2);
    // pros::delay(100);
    // spinIntake(0);

    // robot->backward(5, 127, 2.2);
    // robot->turn(-135, 110, 2.2);
    // robot->forward(65, 127, 2.2);
    // robot->turn(90, 110, 2.2);
    // pros::delay(500);

    // robot->turn(-90, 110, 2.2);
    // robot->forward(65, 127, 2.2);
    // spinIntake(127);
    // robot-> turn(30, 110, 2.2);
    // robot->forward(15, 127, 2.2);
    // pros::delay(150);
    // spinIntake(0);

    //nearside and shot
    // spinIntake(127);
    // robot->forward(3, 127, 2.2);
    // pros::delay(100);
    // spinIntake(0);

    // robot->backward(5, 127, 2.2);
    // robot->turn(-135, 80, 2.2);
    // robot->forward(65, 127, 2.2);
    // robot->turn(90, 80, 2.2);
    // pros::delay(500);

    //farside and shot
    
    robot->forward(16, 80, 2.2);
    spinIntake(127);
    robot->turn(90, 80, 2.2);
    robot->forward(6, 80, 2.2);
    pros::delay(100);
    spinIntake(0);
    robot->backward(12, 80, 2.2);
    robot->turn(-43, 80, 2.2);
    robot->backward(65, 80, 2.2);
    robot->turn(90, 80, 2.2);
    pros::delay(500);

}

void SpinOut::opcontrolLoop()
{   
    if (robot->masterController.a) {
        pullingBack = false;
        catapultSpin = !catapultSpin;
    }

    if (catapultSpin) {
        spinCatapult(-127);
    } 
    else {
        spinCatapult(0);
    }

    if (pullingBack) {
        if (!lever.get_value()) {
            spinCatapult(-127);
        } 
        else {
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

     
    if (robot->masterController.rArrow) stringShooter.set_value(true);


    if (robot->masterController.uArrow) {
        blockerW.set_value(true);
    }
    else{
        blockerW.set_value(false);
    }
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

void SpinOut::spinBackCatapult()
{
    pullingBack = true;
}

void SpinOut::launchDisks()
{
    spinCatapult(-127);
    pros::delay(750);
    spinBackCatapult();
}


