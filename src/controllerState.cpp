#include "controllerState.hpp"
#include "api.h"
#include "okapi/api.hpp"

using namespace pros;

void controllerState::getControllerState()
{
  // Bumpers
  leftBumper1 = master.get_digital(E_CONTROLLER_DIGITAL_L1);
  rightBumper1 = master.get_digital_new_press(E_CONTROLLER_DIGITAL_R1);
  leftBumper2 = master.get_digital(E_CONTROLLER_DIGITAL_L2);
  rightBumper2 = master.get_digital_new_press(E_CONTROLLER_DIGITAL_R2);
  // Button Pad
  a = master.get_digital_new_press(E_CONTROLLER_DIGITAL_A);
  b = master.get_digital_new_press(E_CONTROLLER_DIGITAL_B);
  y = master.get_digital_new_press(E_CONTROLLER_DIGITAL_Y);
  x = master.get_digital_new_press(E_CONTROLLER_DIGITAL_X);
  // Arrows
  uArrow = master.get_digital(E_CONTROLLER_DIGITAL_UP);
  dArrow = master.get_digital(E_CONTROLLER_DIGITAL_DOWN);
  lArrow = master.get_digital(E_CONTROLLER_DIGITAL_LEFT);
  rArrow = master.get_digital_new_press(E_CONTROLLER_DIGITAL_RIGHT);
  // Sticks
  leftStick.x = master.get_analog(E_CONTROLLER_ANALOG_LEFT_X);
  leftStick.y = master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y);
  rightStick.x = master.get_analog(E_CONTROLLER_ANALOG_RIGHT_X);
  rightStick.y = master.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y);
}
