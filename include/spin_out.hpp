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

class SpinOut : public VexMeet
{
public:
    pros::Motor winchRight = pros::Motor(13);
    pros::Motor winchLeft = pros::Motor(15);
    ADIDigitalIn button = ADIDigitalIn('B');
    ADIDigitalOut launch = ADIDigitalOut('A');
    ADIDigitalOut stringShooter = ADIDigitalOut('C');

    bool toggledIntake = false;

    SpinOut();

    void initialize() override;
    void autonomous() override;
    void opcontrolLoop() override;

    void spinWinch(double speed);
    void spinWinchVelocity(double speed);
    void shotPullBack(double speed);
    void launchDisks();
};
