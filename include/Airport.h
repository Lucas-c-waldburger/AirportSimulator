
#ifndef AIRPORTSIMULATOR_AIRPORT_H
#define AIRPORTSIMULATOR_AIRPORT_H
#include "AircraftRequest.h"
#include "Location.h"
#include "LocationMap.h"
#include "RequestToken.h"
#include <vector>
#include <mutex>
#include <thread>

class Airport
{
public:
    Airport();

    static constexpr const int kOperationDurationSec = 5;
    static constexpr const int kTokenExpirationTimeSec = 2;

    enum class SuccessFlag
    {
        SUCCESS = 1 << 0,
        EXPIRED_TOKEN = 1 << 1,
        INCORRECT_TOKEN_TYPE = 1 << 2,
        INVALID_ID = 1 << 3,
        MISSING_RUNWAY_ID = 1 << 4,
        MISSING_PARKING_STAND_ID = 1 << 5
    };

    std::unique_ptr<RequestToken> RequestLanding(const std::string& aircraftID);
    SuccessFlag PerformLanding(RequestToken& lRt);

    std::unique_ptr<RequestToken> RequestTakeOff(const std::string& aircraftID);
    SuccessFlag PerformTakeOff(RequestToken& toRt);

    // CHANGE TO NEUTRAL TIMER
    static void setTimerForLandingOp(Runway& runway, ParkingStand& parkingStand);
    static void setTimerForTakeOffOp(Runway& runway, ParkingStand& parkingStand);

    LocationMap<Runway> runways;
    LocationMap<ParkingStand> parkingStands;

    void reserveResources(const RequestToken& reqToken);
    void freeResources(const RequestToken& reqToken);

};



#endif //AIRPORTSIMULATOR_AIRPORT_H
