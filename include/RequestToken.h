
#ifndef AIRPORTSIMULATOR_REQUESTTOKEN_H
#define AIRPORTSIMULATOR_REQUESTTOKEN_H
#include <iostream>
#include <chrono>
#include <memory>

class RequestToken
{
public:
    enum RequestType { LANDING, TAKEOFF };

    RequestType reqType;
    std::string aircraftID;
    std::string runwayID;
    std::string parkingStandID;
    const uint64_t expirationTime;

    static std::unique_ptr<RequestToken> buildLandingRequestToken(const std::string& acId, const std::string& rwId, const std::string& psId, const unsigned secsTillExp);
    static std::unique_ptr<RequestToken> buildTakeOffRequestToken(const std::string& acId, const std::string& rwId, const unsigned secsTillExp);

    static const bool tokenExpired(const uint64_t expirationTime);

private:
    RequestToken(RequestType reqType, const std::string& acId, const std::string& rwId, const std::string& psId, const unsigned secsTillExp);

    static const uint64_t makeExpiration(const unsigned secsTillExp);
};

#endif //AIRPORTSIMULATOR_REQUESTTOKEN_H
