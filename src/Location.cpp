#include "../include/Location.h"


Runway::Runway(const std::string& id, Runway::State st) : ID(id), state(Runway::State::AVAILABLE)
{
    if (ID.empty())
        throw std::invalid_argument("ID cannot be an empty string"); // ensures that testing whether there are no
                                                                     // runways/parkingStands marked available by
                                                                     // returning an empty string is reliable
}

const std::string& Runway::getID() const
{
    return ID;
}

const Runway::State Runway::getState() const
{
    std::lock_guard<std::mutex> lg(mLock);
    return state;
}

void Runway::setState(Runway::State st)
{
    std::lock_guard<std::mutex> lg(mLock);
    state = st;
}

ParkingStand::ParkingStand(const std::string& id, ParkingStand::State st) : ID(id), state(ParkingStand::State::AVAILABLE)
{
    if (ID.empty())
        throw std::invalid_argument("ID cannot be an empty string");
}

const std::string& ParkingStand::getID() const
{
    return ID;
}

const ParkingStand::State ParkingStand::getState() const
{
    std::lock_guard<std::mutex> lg(mLock);
    return state;
}

void ParkingStand::setState(ParkingStand::State st)
{
    std::lock_guard<std::mutex> lg(mLock);
    state = st;
}