// libraries and namespaces
#include "main.h"
#include "api.h"
#include <vector>
#include "okapi/api.hpp"
using namespace okapi;
using namespace pros;
using namespace std;

#include "vec2d.h"
#include "controllerState.h"
#include "utils.h"

// rename a program in the 'project.pros' file
 
// initialization of pros components
controllerState masterController;
pros::Motor leftTop(7);
pros::Motor leftFront(5);
pros::Motor leftBack(8);
pros::Motor rightFront(17);
pros::Motor rightBack(1);
pros::Motor winchRight(13);
pros::Motor winchLeft(15);
pros::Motor rightTop(20);
ADIDigitalIn button('A');
ADIDigitalOut clampSolenoid('H');
pros::Imu gyroSensor(8);
bool braked = false;
int desiredHeading = 0;
vector<pros::Motor> motorsCoast{rightTop, rightFront, rightBack, leftTop, leftFront, leftBack};

// declaration of global variables and constants
pid sPID;
bool clawState = true;
bool clampState = false;
bool ringState = false;

// these are in inches
const double turningCircleDiameter = 14.7567;
const double turningCircleCircumference = 46.3595;
const double wheelCircumference = 10.2102;

// complicated mathematics
int iPID(int iDes, int iSensorInput, const float kP, const float kI, const float kD, const float kILimit)
{
  sPID.current = iSensorInput;
  sPID.error = iDes - sPID.current;
  if (kI != 0) // integral - if Ki is not 0
  {            // If we are inside controllable window then integrate the error
    if (abs(sPID.error) < kILimit)
      sPID.integral = sPID.integral + sPID.error;
    else
      sPID.integral = 0;
  }
  else // Otherwise set integral to 0
    sPID.integral = 0;
  sPID.derivative = sPID.error - sPID.lastError; // Calculate Derivative
  pros::delay(5);
  sPID.lastError = sPID.error;
  return (-1 * ((sPID.error * kP) + (sPID.integral * kI) + (sPID.derivative * kD)));
}

void on_center_button()
{
} // activates on center button press. Not needed for now

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */

void tareMotors()
{
  leftTop.tare_position();
  leftFront.tare_position();
  leftBack.tare_position();
  rightTop.tare_position();
  rightFront.tare_position();
  rightBack.tare_position();
}

void initialize()
{
  pros::lcd::initialize();
  tareMotors();
  gyroSensor.reset();
  pros::delay(3000);

  for (int i = 0; i < motorsCoast.size(); i++)
  {
    motorsCoast[i].set_brake_mode(E_MOTOR_BRAKE_COAST);
  }

  //clawSolenoid.set_value(true);

  leftTop.set_reversed(true);
  leftFront.set_reversed(true);
  leftBack.set_reversed(true);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */

// This is the place to put funcitons that will be used in autonomous and opcontrol
void rightMotors(double speed)
{
  rightTop.move(speed);
  rightFront.move(speed);
  rightBack.move(speed);
}

void rightMotorsVelocity(double speed)
{
  rightTop.move_velocity(speed);
  rightFront.move_velocity(speed);
  rightBack.move_velocity(speed);
}

void leftMotors(double speed)
{
  leftTop.move(speed);
  leftFront.move(speed);
  leftBack.move(speed);
}

void leftMotorsVelocity(double speed)
{
  leftTop.move_velocity(speed);
  leftFront.move_velocity(speed);
  leftBack.move_velocity(speed);
}

double getLeftEncoders()
{
  return leftTop.get_raw_position(NULL);
}

double getRightEncoders()
{
  return rightTop.get_raw_position(NULL);
}

double monkeyPID(int speed, int distance, double coefficient, double encoder)
{ // encoder is current encoder value, coefficient changes the sharpness of the curve
  // COEFFICIENT SHOULD NOT BE LESS THAN 2
  double value = speed * cos((pi * encoder) / (distance * coefficient));
  return value > 15 ? value : 15;

  // https://www.desmos.com/calculator/eqcltlj8of
}

void forward(double distance, int speed, double coeff, double leftCorrect = 0.9, double rightCorrect = 0.9)
{
  pros::delay(20);

  distance = distance / 10.2102 * 500;
  double initialValueGyro{gyroSensor.get_rotation()};
  double initialValueRight{getRightEncoders()};
  double initialValueLeft{getLeftEncoders()};
  double speedPID = 0;

  while (getRightEncoders() - initialValueRight < distance || getLeftEncoders() - initialValueLeft < distance)
  {
    speedPID = monkeyPID(speed, distance, coeff, getRightEncoders() - initialValueRight);
    if (coeff == 0)
    {
      speedPID = speed;
    }
    if (gyroSensor.get_rotation() < initialValueGyro)
    {
      rightMotorsVelocity(speedPID * rightCorrect);
      leftMotorsVelocity(speedPID);
    }
    else if (gyroSensor.get_rotation() > initialValueGyro)
    {
      rightMotorsVelocity(speedPID);
      leftMotorsVelocity(speedPID * leftCorrect);
    }
    else if (gyroSensor.get_rotation() == initialValueGyro)
    {
      rightMotorsVelocity(speedPID);
      leftMotorsVelocity(speedPID);
    }
    pros::delay(20);
  }
  rightMotorsVelocity(0);
  leftMotorsVelocity(0);
}

void backward(double distance, int speed, double coeff, double leftCorrect = 0.9, double rightCorrect = 0.9)
{
  pros::delay(20);

  distance = distance / 10.2102 * 500;
  distance = -distance;
  double initialValueGyro{gyroSensor.get_rotation()};
  double initialValueRight{getRightEncoders()};
  double initialValueLeft{getLeftEncoders()};
  double speedPID = 0;

  while (getRightEncoders() - initialValueRight > distance || getLeftEncoders() - initialValueLeft > distance)
  {
    speedPID = monkeyPID(speed, distance, coeff, getRightEncoders() - initialValueRight);
    if (coeff == 0)
    {
      speedPID = speed;
    }
    if (gyroSensor.get_rotation() > initialValueGyro)
    {
      rightMotorsVelocity(-speedPID * rightCorrect);
      leftMotorsVelocity(-speedPID);
    }
    else if (gyroSensor.get_rotation() < initialValueGyro)
    {
      rightMotorsVelocity(-speedPID);
      leftMotorsVelocity(-speedPID * leftCorrect);
    }
    else if (gyroSensor.get_rotation() == initialValueGyro)
    {
      rightMotorsVelocity(-speed);
      leftMotorsVelocity(-speed);
    }
    pros::delay(20);
  }
  rightMotorsVelocity(0);
  leftMotorsVelocity(0);
}

double angleDiff(double target, double current)
{
  if (abs(target - current) < abs(target - current - 360))
  {
    return target - current;
  }
  if (abs(target - current) > abs(target - current - 360))
  {
    return target - current - 360;
  }
  else
  {
    return target - current;
  }
}

void turnAbsolute(int angle, int speed, double coeff)
{
  pros::delay(20);

  double initialRotation{gyroSensor.get_heading()};
  double speedPID = 0;
  double progress = 0;
  int direction = 0;

  while (abs(gyroSensor.get_heading() - angle) > 2)
  {
    direction = angleDiff(angle, gyroSensor.get_heading()) < 0 ? -1 : 1;
    progress = abs(angleDiff(initialRotation, gyroSensor.get_heading()));
    speedPID = monkeyPID(speed, angleDiff(angle, initialRotation), coeff, progress);
    rightMotorsVelocity(speedPID * -direction);
    leftMotorsVelocity(speedPID * direction);
    pros::delay(20);
  }
  rightMotorsVelocity(0);
  leftMotorsVelocity(0);
}

void turn(int angle, int speed, double coeff)
{
  desiredHeading += angle;
  desiredHeading = desiredHeading < 0 ? 360-(abs(desiredHeading)%360) : desiredHeading%360;
  turnAbsolute(desiredHeading,speed,coeff);
  //balls
}

void shotPullBack(double speed){
  pros::delay(20);

  while(!button.get_value()){
    winchLeft.move(-speed);
    winchRight.move(-speed);
  }
  winchLeft.move(0); 
  winchRight.move(0);

}




void autonomous()
{
  for (int i = 0; i < motorsCoast.size(); i++)
  {
    motorsCoast[i].set_brake_mode(E_MOTOR_BRAKE_HOLD);
  }

  pros::delay(20);

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
}

void opcontrol()
{
  for (int i = 0; i < motorsCoast.size(); i++)
  {
    motorsCoast[i].set_brake_mode(E_MOTOR_BRAKE_COAST);
  }

  while (true)
  {

    pros::lcd::set_text(1, to_string(gyroSensor.get_rotation()));

    // Updates controller values
    masterController.getControllerState();

    // Drivetrain
    rightMotors(masterController.rightStick.y);
    leftMotors(masterController.leftStick.y);

    // Solenoid Control
    if (masterController.y)
    {
      // clawSolenoid.set_value(!clawState);
      clawState = !clawState;
    }

    if (masterController.a)
    {
      braked = !braked;
      if (braked)
      {
        for (int i = 0; i < motorsCoast.size(); i++)
        {
          motorsCoast[i].set_brake_mode(E_MOTOR_BRAKE_HOLD);
        }
        masterController.master.rumble("..-..");
      }
      else
      {
        masterController.master.rumble("--.--");
        for (int i = 0; i < motorsCoast.size(); i++)
        {
          motorsCoast[i].set_brake_mode(E_MOTOR_BRAKE_COAST);
        }
      }
    }

    if (masterController.rArrow)
    {
      clampSolenoid.set_value(!clampState);
      clampState = !clampState;
    }

    // Ring
    if (masterController.rightBumper1)
    {
      ringState = !ringState;
    }

    pros::delay(20);
  }
}