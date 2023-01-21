#pragma once

#include "vec2d.h"
#include "api.h"
#include "okapi/api.hpp"

// Controller State for easily accessing controller inputs
class controllerState
{
public:
  void getControllerState();

  bool rightBumper1;
  bool leftBumper1;
  bool rightBumper2;
  bool leftBumper2;
  bool a;
  bool b;
  bool x;
  bool y;
  bool uArrow;
  bool dArrow;
  bool lArrow;
  bool rArrow;
  Vec2d leftStick{0, 0};
  Vec2d rightStick{0, 0};
  pros::Controller master = pros::Controller(pros::E_CONTROLLER_MASTER);
};
