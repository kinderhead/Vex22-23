#pragma once

#include "main.h"
#include "api.h"
#include <vector>
#include "okapi/api.hpp"
using namespace okapi;
using namespace pros;
using namespace std;

#include "vec2d.hpp"
#include "controllerState.hpp"
#include "utils.hpp"

#include "drive_train.hpp"
#include "vex_meet.hpp"

class Robot
{
public:
    // initialization of pros components
    controllerState masterController;
    pros::Motor leftTop = pros::Motor(7);
    pros::Motor leftFront = pros::Motor(5);
    pros::Motor leftBack = pros::Motor(8);
    pros::Motor rightFront = pros::Motor(17);
    pros::Motor rightBack = pros::Motor(1);
    pros::Motor rightTop = pros::Motor(20);
    pros::Imu gyroSensor = pros::Imu(8);
    
    int desiredHeading = 0;
    vector<pros::Motor> motorsCoast{rightTop, rightFront, rightBack, leftTop, leftFront, leftBack};

    DriveTrain* drive_train;
    VexMeet* meet;

    // declaration of global variables and constants
    pid sPID;

    // these are in inches
    const double turningCircleDiameter = 14.7567;
    const double turningCircleCircumference = 46.3595;
    const double wheelCircumference = 10.2102;

    Robot(VexMeet* meet);
    ~Robot();

    void initialize();
    void autonomous();
    void disabled();
    void competition_initialize();
    void opcontrol();

    void tareMotors();
    void forward(double distance, int speed, double coeff, double leftCorrect = 0.9, double rightCorrect = 0.9);
    void backward(double distance, int speed, double coeff, double leftCorrect = 0.9, double rightCorrect = 0.9);
    void turnAbsolute(int angle, int speed, double coeff);
    void turn(int angle, int speed, double coeff);
};
