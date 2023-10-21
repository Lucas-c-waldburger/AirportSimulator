#include "../include/Runway.h"

Runway::Runway(const std::string& id) : ID(id), state(RunwayState::AVAILABLE)
{};
