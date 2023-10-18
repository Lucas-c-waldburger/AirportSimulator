
#ifndef AIRPORTSIMULATOR_REQUESTTOKEN_H
#define AIRPORTSIMULATOR_REQUESTTOKEN_H
#include <iostream>
#include <chrono>
#include <memory>


class RequestToken
{
public:
    enum RequestType { LANDING, TAKE_OFF };

    static std::unique_ptr<RequestToken> buildLandingRequest(const std::string& acID, const std::string& rwID, const std::string& psID);
    static std::unique_ptr<RequestToken> buildTakeOffRequest(const std::string& acID, const std::string& rwID);
    static bool reservationExpired(const RequestToken& reqToken);


    RequestType requestType;
    std::string aircraftID;
    std::string runwayID;
    std::string parkingStandID;
    std::chrono::time_point<std::chrono::steady_clock> expirationTime;

private:
    RequestToken(RequestType reqType, const std::string& acID, const std::string& rwID, const std::string& psID);
    static std::chrono::time_point<std::chrono::steady_clock> makeExpiration(int secs);
};


//class RequestToken
//{
//public:
//    RequestToken(const std::string& acID, const std::string& rwID);
//    virtual ~RequestToken() = 0;
//
//    std::string aircraftID;
//    std::string runwayID;
//    std::chrono::time_point<std::chrono::steady_clock> expirationTime;
//
//    static std::chrono::time_point<std::chrono::steady_clock> makeExpiration(int secs);
//    static bool reservationExpired(const RequestToken& reqToken);
//};
//
//class LandingRequestToken : public RequestToken
//{
//public:
//    virtual ~LandingRequestToken() = default;
//    static std::unique_ptr<LandingRequestToken> build(const std::string& acID,
//                                                      const std::string& rwID,
//                                                      const std::string& psID);
//
//    std::string parkingStandID;
//
//private:
//    LandingRequestToken(const std::string& acID, const std::string& rwID, const std::string& psID);
//
//};
//
//class TakeOffRequestToken : public RequestToken
//{
//public:
//    virtual ~TakeOffRequestToken() = default;
//    static std::unique_ptr<TakeOffRequestToken> build(const std::string& acID, const std::string& rwID);
//private:
//    TakeOffRequestToken(const std::string& acID, const std::string& rwID);
//};


#endif //AIRPORTSIMULATOR_REQUESTTOKEN_H
