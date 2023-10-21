
#ifndef AIRPORTSIMULATOR_AIRPORT_H
#define AIRPORTSIMULATOR_AIRPORT_H
#include "LocationManager.h"
#include "RequestToken.h"
#include <thread>
#include <memory>


static constexpr const int kOperationDurationSec = 5;
static constexpr const int kTokenExpirationTimeSec = 2;


class Airport
{
public:


    Airport(unsigned numberOfRunways, unsigned numberOfParkingStands);

    enum PerformOperationFlag
    {
        SUCCESS,
        EXPIRED_TOKEN,
        STATE_CONFLICT
    };

    std::unique_ptr<RequestToken> requestLanding(const std::string& aircraftID);
    std::unique_ptr<std::thread> performLanding(const RequestToken& lrt);
    std::unique_ptr<RequestToken> requestTakeOff(const std::string& aircraftID);
    std::unique_ptr<std::thread> performTakeOff(const RequestToken& tort);

    // std::mutex apMutex;



    // void makeAvailable(const std::string& runwayID, const std::string& parkingStandID);

private:
    LocationManager<Runway, RunwayState> runways;
    LocationManager<ParkingStand, ParkingStandState> parkingStands;

    //void setOpStateChangeTimer(const std::string& runwayID, RunwayState rwStateChange, const std::string& parkingStandID, ParkingStandState psStateChange);
    void setLandingOpTimer(const std::string& runwayID, const std::string& parkingStandID);
    void setTakeOffOpTimer(const std::string& runwayID);
};





#endif //AIRPORTSIMULATOR_AIRPORT_H
