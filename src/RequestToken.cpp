#include "../include/RequestToken.h"

RequestToken::RequestToken(RequestToken::RequestType reqType, const std::string& acID, const std::string& rwID,
const std::string& psID) : requestType(reqType), aircraftID(acID), runwayID(rwID), expirationTime(RequestToken::makeExpiration(2))
{}

std::unique_ptr<RequestToken> RequestToken::buildLandingRequest(const std::string& acID,
                                                                const std::string& rwID,
                                                                const std::string& psID)
{
    return std::unique_ptr<RequestToken>(new RequestToken(RequestType::LANDING, acID, rwID, psID));
}

std::unique_ptr<RequestToken> RequestToken::buildTakeOffRequest(const std::string& acID,
                                                                const std::string& rwID)
{
    return std::unique_ptr<RequestToken>(new RequestToken(RequestType::TAKE_OFF, acID, rwID, ""));
}

std::chrono::time_point<std::chrono::steady_clock> RequestToken::makeExpiration(int secs)
{
    return std::chrono::steady_clock::now() + std::chrono::seconds(secs);
}

bool RequestToken::reservationExpired(const RequestToken& reqToken)
{
    return std::chrono::steady_clock::now() > reqToken.expirationTime;
}

//LandingRequestToken::LandingRequestToken(const std::string& acID, const std::string& rwID, const std::string& psID) :
//        RequestToken(acID, rwID), parkingStandID(psID)
//{}
//
//
//std::unique_ptr<TakeOffRequestToken> TakeOffRequestToken::build(const std::string& acID,
//                                                                const std::string& rwID)
//{
//    return std::unique_ptr<TakeOffRequestToken>(new TakeOffRequestToken(acID, rwID));
//}
//
//TakeOffRequestToken::TakeOffRequestToken(const std::string& acID, const std::string& rwID) : RequestToken(acID, rwID)
//{}





