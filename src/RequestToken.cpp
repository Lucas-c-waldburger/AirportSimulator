#include "../include/RequestToken.h"


RequestToken::RequestToken(RequestType reqType, const std::string& acId, const std::string& rwId, const std::string& psId, const unsigned secsTillExp) :
        aircraftID(acId), runwayID(rwId), parkingStandID(psId), expirationTime(RequestToken::makeExpiration(secsTillExp))
{}


std::unique_ptr<RequestToken> RequestToken::buildLandingRequestToken(const std::string& acId, const std::string& rwId, const std::string& psId, const unsigned secsTillExp)
{
    return std::unique_ptr<RequestToken>(new RequestToken(RequestType::LANDING, acId, rwId, psId, secsTillExp));
}


std::unique_ptr<RequestToken> RequestToken::buildTakeOffRequestToken(const std::string& acId, const std::string& rwId, const unsigned secsTillExp)
{
    return std::unique_ptr<RequestToken>(new RequestToken(RequestType::TAKEOFF, acId, rwId, "", secsTillExp));
}


const uint64_t RequestToken::makeExpiration(const unsigned secsTillExp)
{
    //auto now = std::chrono::steady_clock::now();
    //auto exp = now + std::chrono::seconds(secs);
    //Logger::Log("Given an expiration time of ", exp - now);

    auto expiration = std::chrono::steady_clock::now() + std::chrono::seconds(secsTillExp);

    return expiration.time_since_epoch().count();
}

const bool RequestToken::tokenExpired(const uint64_t expirationTime)
{

    auto now = std::chrono::steady_clock::now().time_since_epoch().count();
    // Logger::Log("NOW: ", now, "   EXPIR: ", expirationTime);
    return now >= expirationTime;
    //return (std::chrono::duration_cast<std::chrono::seconds>(expirationTime - now).count() < 0);
}

