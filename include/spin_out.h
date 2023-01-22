#pragma once

#include "vex_meet.h"
#include "api.h"
#include <vector>
#include "okapi/api.hpp"
using namespace okapi;
using namespace pros;
using namespace std;

#include "vec2d.h"
#include "controllerState.h"
#include "utils.h"

class SpinOut : public VexMeet
{
public:
    pros::Motor winchRight = pros::Motor(13);
    pros::Motor winchLeft = pros::Motor(15);
    ADIDigitalIn button = ADIDigitalIn('A');

    SpinOut();

    void initialize() override;
    void autonomous() override;
    void opcontrolLoop() override;

    void spinWinch(double speed);
    void spinWinchVelocity(double speed);
    void shotPullBack(double speed);
};
