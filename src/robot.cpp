#include "robot.h"

Robot::Robot(VexMeet* meet)
{
    drive_train = new DriveTrain(this);
    this->meet = meet;
    this->meet->robot = this;
}

Robot::~Robot()
{
    delete drive_train;
}

void Robot::initialize()
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

    meet->initialize();
}

void Robot::autonomous()
{
    for (int i = 0; i < motorsCoast.size(); i++)
    {
        motorsCoast[i].set_brake_mode(E_MOTOR_BRAKE_HOLD);
    }

    pros::delay(20);
    meet->autonomous();
}

void Robot::disabled()
{
}

void Robot::competition_initialize()
{
}

void Robot::opcontrol()
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
        drive_train->rightMotors(masterController.rightStick.y);
        drive_train->leftMotors(masterController.leftStick.y);

        meet->opcontrolLoop();
    }
}

void Robot::tareMotors()
{
    leftTop.tare_position();
    leftFront.tare_position();
    leftBack.tare_position();
    rightTop.tare_position();
    rightFront.tare_position();
    rightBack.tare_position();
}

void Robot::forward(double distance, int speed, double coeff, double leftCorrect, double rightCorrect)
{
    pros::delay(20);

    distance = distance / 10.2102 * 500;
    double initialValueGyro = gyroSensor.get_rotation();
    double initialValueRight = drive_train->getRightEncoders();
    double initialValueLeft = drive_train->getLeftEncoders();
    double speedPID = 0;

    while (drive_train->getRightEncoders() - initialValueRight < distance || drive_train->getLeftEncoders() - initialValueLeft < distance)
    {
        speedPID = monkeyPID(speed, distance, coeff, drive_train->getRightEncoders() - initialValueRight);
        if (coeff == 0)
        {
            speedPID = speed;
        }
        if (gyroSensor.get_rotation() < initialValueGyro)
        {
            drive_train->rightMotorsVelocity(speedPID * rightCorrect);
            drive_train->leftMotorsVelocity(speedPID);
        }
        else if (gyroSensor.get_rotation() > initialValueGyro)
        {
            drive_train->rightMotorsVelocity(speedPID);
            drive_train->leftMotorsVelocity(speedPID * leftCorrect);
        }
        else if (gyroSensor.get_rotation() == initialValueGyro)
        {
            drive_train->rightMotorsVelocity(speedPID);
            drive_train->leftMotorsVelocity(speedPID);
        }
        pros::delay(20);
    }
    drive_train->rightMotorsVelocity(0);
    drive_train->leftMotorsVelocity(0);
}

void Robot::backward(double distance, int speed, double coeff, double leftCorrect, double rightCorrect)
{
    pros::delay(20);

    distance = distance / 10.2102 * 500;
    distance = -distance;
    double initialValueGyro{gyroSensor.get_rotation()};
    double initialValueRight{drive_train->getRightEncoders()};
    double initialValueLeft{drive_train->getLeftEncoders()};
    double speedPID = 0;

    while (drive_train->getRightEncoders() - initialValueRight > distance || drive_train->getLeftEncoders() - initialValueLeft > distance)
    {
        speedPID = monkeyPID(speed, distance, coeff, drive_train->getRightEncoders() - initialValueRight);
        if (coeff == 0)
        {
            speedPID = speed;
        }
        if (gyroSensor.get_rotation() > initialValueGyro)
        {
            drive_train->rightMotorsVelocity(-speedPID * rightCorrect);
            drive_train->leftMotorsVelocity(-speedPID);
        }
        else if (gyroSensor.get_rotation() < initialValueGyro)
        {
            drive_train->rightMotorsVelocity(-speedPID);
            drive_train->leftMotorsVelocity(-speedPID * leftCorrect);
        }
        else if (gyroSensor.get_rotation() == initialValueGyro)
        {
            drive_train->rightMotorsVelocity(-speed);
            drive_train->leftMotorsVelocity(-speed);
        }
        pros::delay(20);
    }
    drive_train->rightMotorsVelocity(0);
    drive_train->leftMotorsVelocity(0);
}

void Robot::turnAbsolute(int angle, int speed, double coeff)
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
        drive_train->rightMotorsVelocity(speedPID * -direction);
        drive_train->leftMotorsVelocity(speedPID * direction);
        pros::delay(20);
    }
    drive_train->rightMotorsVelocity(0);
    drive_train->leftMotorsVelocity(0);
}

void Robot::turn(int angle, int speed, double coeff)
{
    desiredHeading += angle;
    desiredHeading = desiredHeading < 0 ? 360-(abs(desiredHeading)%360) : desiredHeading%360;
    turnAbsolute(desiredHeading,speed,coeff);
    //balls
}
