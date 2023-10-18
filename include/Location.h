#ifndef AIRPORTSIMULATOR_LOCATION_H
#define AIRPORTSIMULATOR_LOCATION_H
#include <iostream>
#include <string>

// using base location as template for the state enum means we can't have state belong to the derived class
// unfortunately. However, we are now able to encapsulate the state member var inside Location.
// Not sure which is preferable

struct Runway
{
    enum State
    {
        AVAILABLE,
        RESERVED,
        IN_OPERATION
    };

    Runway(const std::string& id, State st);

    const std::string& getID() const;
    const State getState() const;
    void setState(State st);

private:
    std::string ID;
    State state;
    mutable std::mutex mLock;
};

struct ParkingStand
{
    enum State
    {
        AVAILABLE,
        RESERVED,
        OCCUPIED
    };

    ParkingStand(const std::string& id, State st);
    const std::string& getID() const;
    const State getState() const;
    void setState(State st);

private:
    std::string ID;
    State state;
    mutable std::mutex mLock;
};

//struct Location
//{
//    Location(const std::string& id);
//    virtual ~Location() = 0;
//
//    std::string ID;
//};
//
//
//struct Runway : public Location
//{
//    Runway(const std::string& id);
//    virtual ~Runway() = default;
//
//    enum class State
//    {
//        IN_OPERATION,
//        RESERVED,
//        AVAILABLE
//    };
//
//    State state;
//};
//
//
//
//
//struct ParkingStand : public Location
//{
//    ParkingStand(const std::string& id);
//    virtual ~ParkingStand() = default;
//
//    enum class State
//    {
//        OCCUPIED,
//        RESERVED,
//        AVAILABLE
//    };
//
//    State state;
//};


#endif //AIRPORTSIMULATOR_LOCATION_H
