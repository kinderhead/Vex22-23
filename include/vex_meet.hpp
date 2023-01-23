#pragma once

// Forward declaration
class Robot;

class VexMeet
{
public:
    Robot* robot;

    virtual void initialize() = 0;
    virtual void autonomous() = 0;
    virtual void opcontrolLoop() = 0;
};
