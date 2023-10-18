#ifndef AIRPORTSIMULATOR_LOCATION_H
#define AIRPORTSIMULATOR_LOCATION_H
#include <iostream>
#include <string>

// using base location as template for the state enum means we can't have state belong to the derived class
// unfortunately. However, we are now able to encapsulate the state member var inside Location.
// Not sure which is preferable


template <typename StateEnum>
struct Location
{
    Location(const std::string& id, StateEnum st);
    virtual ~Location() = 0;

    std::string ID;
    StateEnum state;

};

template<typename StateEnum>
inline Location<StateEnum>::Location(const std::string& id, StateEnum st) : ID(id), state(st)
{}

template<typename StateEnum>
inline Location<StateEnum>::~Location()
{}




enum class RunwayState
{
    IN_OPERATION,
    RESERVED,
    AVAILABLE
};

struct Runway : public Location<RunwayState>
{
    Runway(const std::string& id);
    virtual ~Runway() = default;
};


enum class ParkingStandState
{
    OCCUPIED,
    RESERVED,
    AVAILABLE
};

struct ParkingStand : public Location<ParkingStandState>
{
    ParkingStand(const std::string& id);
    virtual ~ParkingStand() = default;
};


#endif //AIRPORTSIMULATOR_LOCATION_H
