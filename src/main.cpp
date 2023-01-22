#include "robot.hpp"

// Create a new class 
#include "spin_out.hpp"

Robot robot(new SpinOut());

// void on_center_button()
// {
// } // activates on center button press. Not needed for now

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize()
{
    robot.initialize();
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled()
{
    robot.disabled();
}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize()
{
    robot.competition_initialize();
}

void autonomous()
{
    robot.autonomous();
    /*

    // https://github.com/kunwarsahni01/Vex-Autonomous-Selector

    // Win Point

    // while (mainLiftPotentiometer.get_value_calibrated() > 2800)
    // {
    //   liftMotor.move_velocity(600);
    //   pros::delay(20);
    // }
    // moveLift(0);
    // clawSolenoid.set_value(false);
    // pros::delay(100);
    // while (mainLiftPotentiometer.get_value_calibrated() < 3621)
    // {
    //   liftMotor.move_velocity(-600);
    //   pros::delay(20);
    // }
    // moveLift(0);
    // pros::delay(100);
    // pros::delay(500);
    // backward(9, 200, 2.1);
    // turnAbsolute(315, 50, 2.1);
    // forward(24, 200, 2.1);
    // turnAbsolute(180, 30, 2.0);
    // pros::delay(100);
    // // going to team goal
    // backward(90, 300, 2.2);
    // clampSolenoid.set_value(true);
    // pros::delay(200);
    // forward(27, 200, 2.1);
    // moveRings(127);
    // pros::delay(200);
    // moveLift(127);
    // pros::delay(200);
    // moveLift(0);
    // moveRings(0);
    // moveLift(-127);
    // pros::delay(200);
    // moveLift(0);
    // turnAbsolute(225, 45, 2.3);
    // // to center goal
    // forward(35, 200, 2.1);
    // clawSolenoid.set_value(true);
    // pros::delay(400);
    // backward(50, 300, 2.1);

    // Skill Issue

    clampSolenoid.set_value(false);
    //clawSolenoid.set_value(false);
    backward(9, 50, 2.5);
    clampSolenoid.set_value(true);
    forward(12, 100, 2.2);
    turn(-45, 80, 2.2); // clockwise: more turn = more rightward motion
    backward(12, 60, 2.2);
    turn(-87, 80, 2.2);
    pros::delay(100);
    forward(45, 100, 3, 0.85, 0.85);
    //clawSolenoid.set_value(true);
    pros::delay(100);
    turn(-12, 30, 2.2);
    masterController.master.rumble("....");
    pros::delay(100);
    forward(20, 100, 2.2);
    forward(20, 100, 2.5);
    turn(90, 50, 2.2);
    forward(37, 100, 2.5);
    turn(-90, 50, 2.2);
    forward(10, 100, 2.5);

    //clawSolenoid.set_value(false);
    pros::delay(200);

    backward(19, 80, 2.2);
    turn(90, 80, 2.2);
    forward(70, 50, 2.5);
    backward(16, 70, 2.1);
    turn(90, 80, 2.2);
    forward(20, 100, 2.5);
    //clawSolenoid.set_value(true);
    pros::delay(100);
    turn(90, 80, 2.2);
    forward(48, 69, 2.5);
    // clawSolenoid.set_value(false);

    // Right Goal

    // clawSolenoid.set_value(false);
    // forward(38, 600, 0);
    // clawSolenoid.set_value(true);
    // pros::delay(100);
    // backward(38, 600, 2.0);

    // Center Goal

    // clawSolenoid.set_value(false);
    // forward(60, 600, 0);
    // clawSolenoid.set_value(true);
    // pros::delay(100);
    // backward(60, 600, 2.0);

    // Left Goal

    // clawSolenoid.set_value(false);
    // forward(40, 600, 0);
    // clawSolenoid.set_value(true);
    // pros::delay(100);
    // backward(40, 600, 2.0);
    */
}

void opcontrol()
{
    robot.opcontrol();
}