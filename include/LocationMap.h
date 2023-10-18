//
// Created by Lower School Music on 10/18/23.
//

#ifndef AIRPORTSIMULATOR_LOCATIONMAP_H
#define AIRPORTSIMULATOR_LOCATIONMAP_H
#include "Location.h"
#include <vector>
#include <unordered_map>
#include <mutex>
#include <iostream>

template <class T>
class LocationMap
{
public:
    LocationMap() = default;

    T& operator[](const std::string& locID);

    void populate(const std::string& locName, int numLocs);

    T* findAvailable();

private:
    std::unordered_map<std::string, T> mMap;
};

template<class T>
T &LocationMap<T>::operator[](const std::string& locID)
{
    try
    {
        return mMap.at(locID);
    }

    catch (std::out_of_range& ex)
    {
        throw ex;
    }
}

// DO I NEED TO LOCK WHILE IM LOOKING?
template<class T>
T* LocationMap<T>::findAvailable()
{
    for (auto& l : mMap)
    {
        if (l.second.getState() == T::State::AVAILABLE)
            return &l.second;
    }

    return nullptr;
}




#endif //AIRPORTSIMULATOR_LOCATIONMAP_H
