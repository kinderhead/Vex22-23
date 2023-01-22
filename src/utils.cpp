#include "utils.h"
#include "robot.h"

#include <math.h>

int iPID(Robot* robot, int iDes, int iSensorInput, const float kP, const float kI, const float kD, const float kILimit)
{
    robot->sPID.current = iSensorInput;
    robot->sPID.error = iDes - robot->sPID.current;
    if (kI != 0) // integral - if Ki is not 0
    {            // If we are inside controllable window then integrate the error
        if (abs(robot->sPID.error) < kILimit)
        robot->sPID.integral = robot->sPID.integral + robot->sPID.error;
        else
        robot->sPID.integral = 0;
    }
    else // Otherwise set integral to 0
        robot->sPID.integral = 0;
    robot->sPID.derivative = robot->sPID.error - robot->sPID.lastError; // Calculate Derivative
    pros::delay(5);
    robot->sPID.lastError = robot->sPID.error;
    return (-1 * ((robot->sPID.error * kP) + (robot->sPID.integral * kI) + (robot->sPID.derivative * kD)));
}

double monkeyPID(int speed, int distance, double coefficient, double encoder)
{ // encoder is current encoder value, coefficient changes the sharpness of the curve
  // COEFFICIENT SHOULD NOT BE LESS THAN 2
  double value = speed * cos((pi * encoder) / (distance * coefficient));
  return value > 15 ? value : 15;

  // https://www.desmos.com/calculator/eqcltlj8of
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
