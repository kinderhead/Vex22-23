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
