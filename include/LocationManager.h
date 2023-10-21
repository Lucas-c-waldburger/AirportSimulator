
#ifndef AIRPORTSIMULATOR_LOCATIONMANAGER_H
#define AIRPORTSIMULATOR_LOCATIONMANAGER_H

#include <string>
#include <mutex>
#include <unordered_map>
#include <typeinfo>
#include "Runway.h"
#include "ParkingStand.h"
#include "Logger.h"

struct LocStrings
{
    template<class T>
    static inline std::string stateAsStr(T locSt)
    {
        return "SPECIALIZED TEMPLATE FOR STATE_AS_STR NOT CALLED";
    }
};

template <>
inline std::string LocStrings::stateAsStr<RunwayState>(RunwayState rwSt)
{
    switch (rwSt)
    {
        case RunwayState::AVAILABLE:
            return "AVAILABLE"; break;
        case RunwayState::RESERVED:
            return "RESERVED"; break;
        case RunwayState::IN_OPERATION:
            return "IN OPERATION"; break;
    }
}

template <>
inline std::string LocStrings::stateAsStr<ParkingStandState>(ParkingStandState psSt)
{
    switch (psSt)
    {
        case ParkingStandState::AVAILABLE:
            return "AVAILABLE"; break;
        case ParkingStandState::RESERVED:
            return "RESERVED"; break;
        case ParkingStandState::OCCUPIED:
            return "OCCUPIED"; break;
    }
}


template <class T, class U>
class LocationManager
{
public:
    LocationManager(const std::string& locName, int numLocs);

    const U readState(const std::string& locId);
    void setState(const std::string& locId, U newSt);
    bool conditionalSetState(const std::string& locId, U ifThisSt, U thenSetSt);

    std::unordered_map<std::string, T> locations;

private:
    std::unordered_map<std::string, std::unique_ptr<std::mutex>> mutexes;
};


template<class T, class U>
inline LocationManager<T, U>::LocationManager(const std::string& locName, int numLocs)
{
    for (int i = 1; i <= numLocs; i++)
    {
        std::string locId = locName + ' ' + std::to_string(i);

        if (locations.count(locId))
            throw std::invalid_argument("ID already exists within Map");

        locations.insert({ locId, T(locId) });
        mutexes.insert({ locId, std::unique_ptr<std::mutex>(new std::mutex) });
    }

}

template<class T, class U>
inline const U LocationManager<T, U>::readState(const std::string& locId)
{
    std::lock_guard<std::mutex> lg(*mutexes.at(locId));

    return locations.at(locId).state;
}

// write only operation
template<class T, class U>
inline void LocationManager<T, U>::setState(const std::string& locId, U newSt)
{
    std::lock_guard<std::mutex> lg(*mutexes.at(locId));

    locations.at(locId).state = newSt;
}

// combined read/write operation
template<class T, class U>
inline bool LocationManager<T, U>::conditionalSetState(const std::string& locId, U ifThisSt, U thenSetSt)
{
    std::lock_guard<std::mutex> lg(*mutexes.at(locId));

    if (locations.at(locId).state == ifThisSt)
    {
        locations.at(locId).state = thenSetSt;
        return true;
    }

    //if (ifThisSt != U::AVAILABLE)
        //Logger::Log("At ", locId, " - Expected ", LocStrings::stateAsStr<U>(ifThisSt), ", but found ", LocStrings::stateAsStr<U>(locations.at(locId).state), " instead");

    /*else if (typeid(ifThisSt) == typeid(ParkingStandState))
        Logger::Log("At ", locId, " - Expected ", LocStrings::pStandStateAsStr(ifThisSt), ", but found ", LocStrings::pStandStateAsStr(locations.at(locId).state), " instead");*/

    return false;
}


#endif //AIRPORTSIMULATOR_LOCATIONMANAGER_H
