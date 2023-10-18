#include "../include/Airport.h"

Airport::Airport()
{
//    for (int i = 0; i < 10; i++)
//    {
//        std::string id = "RUNWAY" + std::to_string(i);
//        this->runways.emplace_back(id);
//        id = "PARKING STAND" + std::to_string(i);
//        this->parkingStands.emplace_back(id);
//        //this->runways.back().state = Runway::State::AVAILABLE;
//    }
}

// Do we need to use a recursive mutex?
// Do we need to return a pointer or just an object?
std::unique_ptr<RequestToken> Airport::RequestLanding(const std::string& aircraftID)
{
    std::unique_ptr<RequestToken> lRt;

    Runway* availableRunway = runways.findAvailable();

    if (availableRunway)
    {
        ParkingStand* availableParkingStand = parkingStands.findAvailable();

        if (availableParkingStand)
        {
            // reserve resources
            availableRunway->setState(Runway::State::RESERVED);
            availableParkingStand->setState(ParkingStand::State::RESERVED);

            lRt = RequestToken::buildLandingRequest(aircraftID, availableRunway->getID(), availableParkingStand->getID());
        }
    }

    return lRt;
}

// if (lRt)
    // PerformLanding(lRt)

Airport::SuccessFlag Airport::PerformLanding(RequestToken& lRt)
{
    // check expiration
    if (RequestToken::reservationExpired(lRt))
    {
        freeResources(lRt);
        return SuccessFlag::EXPIRED_TOKEN;
    }

    // if not expired, set runway to in_operation and start thread to make runway available and parkingStand occupied after wait time

    runways[lRt.runwayID].setState(Runway::State::IN_OPERATION);

    std::thread opTime(setTimerForReactivation, std::ref(runways[lRt.runwayID]), std::ref(parkingStands[lRt.parkingStandID]));


    return SuccessFlag::SUCCESS;
}

std::unique_ptr<RequestToken> Airport::RequestTakeOff(const std::string& aircraftID)
{
    std::unique_ptr<RequestToken> toRt;

    Runway* availableRunway = runways.findAvailable();

    if (availableRunway)
    {
        // reserve resources
        availableRunway->setState(Runway::State::RESERVED);

        toRt = RequestToken::buildTakeOffRequest(aircraftID, availableRunway->getID());
    }

    return toRt;
}

// if (toRt)
    // toRt->parkingStandID = lRt->parkingStandID
    // PerformTakeOff(toRt)

Airport::SuccessFlag Airport::PerformTakeOff(RequestToken& toRt)
{
    // make sure the parkingStandID where the aircraft is was added to requestToken
    if (toRt.parkingStandID.empty())
    {
        return SuccessFlag::MISSING_PARKING_STAND_ID;
    }

    // check expiration
    if (RequestToken::reservationExpired(toRt))
    {
        freeResources(toRt);
        return SuccessFlag::EXPIRED_TOKEN;
    }

    // if not expired, change states
    runways[toRt.runwayID].setState(Runway::State::IN_OPERATION);
    parkingStands[toRt.parkingStandID].setState(ParkingStand::State::AVAILABLE);

    return SuccessFlag::SUCCESS;
}

void Airport::setTimerForReactivation(Runway& runway, ParkingStand& parkingStand)
{
    std::this_thread::sleep_for(std::chrono::seconds(kOperationDurationSec));

    runway.setState(Runway::State::AVAILABLE);
    parkingStand.setState(ParkingStand::State::OCCUPIED);
}


//void Airport::setTimerForReactivation(Runway& runway, ParkingStand& parkingStand)
//{
//    std::this_thread::sleep_for(std::chrono::seconds(kOperationDurationSec));
//
//    std::lock_guard<std::recursive_mutex> lg(smutex);
//
//    runway.state = Runway::State::AVAILABLE;
//    parkingStand.state = ParkingStand::State::OCCUPIED;
//}
//
//void Airport::reserveResources(const RequestToken& reqToken)
//{
//    std::lock_guard<std::recursive_mutex> lg(smutex);
//
//    switch (reqToken.requestType)
//    {
//        case RequestToken::RequestType::LANDING:
//            runways[reqToken.runwayID].state = Runway::State::RESERVED;
//            parkingStands[reqToken.parkingStandID].state = ParkingStand::State::RESERVED;
//            break;
//
//        case RequestToken::RequestType::TAKE_OFF:
//            runways[reqToken.runwayID].state = Runway::State::RESERVED;
//            break;
//    }
//}
//
//void Airport::freeResources(const RequestToken& reqToken)
//{
//    std::lock_guard<std::recursive_mutex> lg(smutex);
//
//    switch (reqToken.requestType)
//    {
//        case RequestToken::RequestType::LANDING:
//            runways[reqToken.runwayID].state = Runway::State::AVAILABLE;
//            parkingStands[reqToken.parkingStandID].state = ParkingStand::State::AVAILABLE;
//            break;
//
//        case RequestToken::RequestType::TAKE_OFF:
//            runways[reqToken.runwayID].state = Runway::State::AVAILABLE;
//            break;
//    }
//
//}
