#ifndef AIRPORTSIMULATOR_AIRPORTLOCATION_H
#define AIRPORTSIMULATOR_AIRPORTLOCATION_H
#include <iostream>


class AirportLocation
{
public:
    enum class State;

private:
    std::string ID;

    static std::string generateID(const std::string& locationName, int numLocations);
};


#endif //AIRPORTSIMULATOR_AIRPORTLOCATION_H
