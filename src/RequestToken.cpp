#include "../include/RequestToken.h"

RequestToken::RequestToken(const std::string& acID, const std::string& rwID) :
        aircraftID(acID), runwayID(rwID), expirationTime(RequestToken::makeExpiration(2))
{}

RequestToken::~RequestToken()
{}


std::unique_ptr<LandingRequestToken> LandingRequestToken::build(const std::string& acID,
                                                                const std::string& rwID,
                                                                const std::string& psID)
{
    return std::unique_ptr<LandingRequestToken>(new LandingRequestToken(acID, rwID, psID));
}

LandingRequestToken::LandingRequestToken(const std::string& acID, const std::string& rwID, const std::string& psID) :
        RequestToken(acID, rwID), parkingStandID(psID)
{}


std::unique_ptr<TakeOffRequestToken> TakeOffRequestToken::build(const std::string& acID,
                                                                const std::string& rwID)
{
    return std::unique_ptr<TakeOffRequestToken>(new TakeOffRequestToken(acID, rwID));
}

TakeOffRequestToken::TakeOffRequestToken(const std::string& acID, const std::string& rwID) : RequestToken(acID, rwID)
{}


std::chrono::time_point<std::chrono::steady_clock> RequestToken::makeExpiration(int secs)
{
    return std::chrono::steady_clock::now() + std::chrono::seconds(secs);
}


