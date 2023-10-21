
#ifndef AIRPORTSIMULATOR_PARKINGSTAND_H
#define AIRPORTSIMULATOR_PARKINGSTAND_H
#include <string>

enum class ParkingStandState
{
    AVAILABLE,
    RESERVED,
    OCCUPIED
};

class ParkingStand
{
public:
    explicit ParkingStand(const std::string& id);

    std::string ID;
    ParkingStandState state;
};


#endif //AIRPORTSIMULATOR_PARKINGSTAND_H
