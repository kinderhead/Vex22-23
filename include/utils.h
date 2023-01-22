#pragma once

// initialization of variables for PID
typedef struct
{
  float current;
  float kP;
  float kI;
  float kD;
  float target;
  float error;
  float integral;
  float derivative;
  float lastError;
  float threshold;
  int lastTime;
} pid;

// Forward declaration
class Robot;

int iPID(Robot* robot, int iDes, int iSensorInput, const float kP, const float kI, const float kD, const float kILimit);

double monkeyPID(int speed, int distance, double coefficient, double encoder);

double angleDiff(double target, double current);