#include "../include/Airport.h"

Airport::Airport()
{
    for (int i = 0; i < 10; i++)
    {
        std::string id = "RUNWAY" + std::to_string(i);
        this->runways.emplace_back(id);
        id = "PARKING STAND" + std::to_string(i);
        this->parkingStands.emplace_back(id);
        //this->runways.back().state = Runway::State::AVAILABLE;
    }
}

void Airport::reserveResources(Runway& runway)
{
    runway.state = Runway::State::RESERVED;
}

void Airport::reserveResources(Runway& runway, ParkingStand& parkingStand)
{
    runway.state = Runway::State::RESERVED;
    parkingStand.state = ParkingStand::State::RESERVED;
}

// Do we need to use a recursive mutex?
// Do we need to return a pointer or just an object?
std::unique_ptr<const LandingRequestToken> Airport::RequestLanding(const std::string& aircraftID)
{
    std::lock_guard<std::recursive_mutex> lg(_smutex);

    std::unique_ptr<const LandingRequestToken> lrt;

    auto availableRunway = std::find_if(runways.begin(), runways.end(), isAvailable<Runway>);

    if (availableRunway != runways.end())
    {
        auto availableParkingStand = std::find_if(parkingStands.begin(), parkingStands.end(),
                                                  isAvailable<ParkingStand>);

        if (availableParkingStand != parkingStands.end())
        {
            reserveResources(*availableRunway, *availableParkingStand);

            lrt = LandingRequestToken::build(aircraftID, availableRunway->ID, availableParkingStand->ID);
        }
    }

    return lrt;
}

// if (airport.RequestLanding)...

Airport::TakeOffFlag Airport::PerformLanding(LandingRequestToken& lrt)
{
    nb
    // setTimerForReactivation
    setTimerForReactivation(runways.back()); //<-- change this to the actual runway!!

    // std::lock_guard<std::recursive_mutex> lg(_smutex);

    // need to read off of lrt
    //
    // need to start some kind of timer thread?

};

void Airport::setTimerForReactivation(Runway& runway)
{
    std::this_thread::sleep_for(std::chrono::seconds(kOperationDurationSec));

    std::lock_guard<std::recursive_mutex> lg(_smutex);

    runway.state = RunwayState::AVAILABLE;
}