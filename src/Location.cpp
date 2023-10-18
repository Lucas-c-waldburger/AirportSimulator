#include "../include/Location.h"

Runway::Runway(const std::string& id) : Location(id, RunwayState::AVAILABLE)
{}

ParkingStand::ParkingStand(const std::string& id) : Location(id, ParkingStandState::AVAILABLE)
{}
