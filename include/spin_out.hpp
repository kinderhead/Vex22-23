#pragma once

#include "vex_meet.hpp"
#include "api.h"
#include <vector>
#include "okapi/api.hpp"
using namespace okapi;
using namespace pros;
using namespace std;

#include "vec2d.hpp"
#include "controllerState.hpp"
#include "utils.hpp"

#define INTAKE_SPEED 127

class SpinOut : public VexMeet
{
public:
    pros::Motor winch = pros::Motor(13);
    pros::Motor intake = pros::Motor(15);
    ADIDigitalIn button = ADIDigitalIn('B');
    ADIDigitalOut launch = ADIDigitalOut('A');
    ADIDigitalOut stringShooter = ADIDigitalOut('C');

    int intakeSpeed = 0;
    bool pullingBack = false;

    // Testing
    bool winchSpin = false;

    SpinOut();

    void initialize() override;
    void autonomous() override;
    void opcontrolLoop() override;

    void spinIntake(double speed);
    void spinCatapult(double speed);
    void spinCatapultVelocity(double speed);
    void launchDisks();
};
