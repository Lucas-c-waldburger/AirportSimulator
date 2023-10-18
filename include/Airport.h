
#ifndef AIRPORTSIMULATOR_AIRPORT_H
#define AIRPORTSIMULATOR_AIRPORT_H
#include "AircraftRequest.h"
#include "Location.h"
#include "RequestToken.h"
#include <vector>
#include <mutex>

static std::recursive_mutex _smutex;

template <typename T>
bool isAvailable(const T& location);

class Airport
{
public:
    Airport();

    static constexpr const int kOperationDurationSec = 5;
    static constexpr const int kTokenExpirationTimeSec = 2;

    struct TakeOffFlag
    {
        enum
        {
            SUCCESS = 1 << 0,
            EXPIRED_TOKEN = 1 << 1,
            INVALID_PARAMETERS = 1 << 2
        };

    private:
        std::string errMsg;
    };

    std::unique_ptr<const LandingRequestToken> RequestLanding(const std::string& aircraftID);
    TakeOffFlag PerformLanding(LandingRequestToken& lrt);


    void setTimerForReactivation(Runway& runway);

    std::vector<Runway> runways;
    std::vector<ParkingStand> parkingStands;

    void reserveResources(Runway& runway);
    void reserveResources(Runway& runway, ParkingStand& parkingStand);

};

template<typename T>
inline bool isAvailable(const T& location)
{
    return location.state == T::State::AVAILABLE;
}


#endif //AIRPORTSIMULATOR_AIRPORT_H
