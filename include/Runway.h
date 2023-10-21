
#ifndef AIRPORTSIMULATOR_RUNWAY_H
#define AIRPORTSIMULATOR_RUNWAY_H

#include <iostream>

enum class RunwayState
{
    AVAILABLE,
    RESERVED,
    IN_OPERATION
};

class Runway
{
public:
    explicit Runway(const std::string& id);

    std::string ID;
    RunwayState state;
    int length; // implement this
};


#endif //AIRPORTSIMULATOR_RUNWAY_H
