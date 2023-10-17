
#ifndef AIRPORTSIMULATOR_REQUESTTOKEN_H
#define AIRPORTSIMULATOR_REQUESTTOKEN_H
#include <iostream>
#include <chrono>
#include <memory>

class RequestToken
{
public:
    RequestToken(const std::string& acID, const std::string& rwID);
    virtual ~RequestToken() = 0;

protected:
    std::string aircraftID;
    std::string runwayID;
    std::chrono::time_point<std::chrono::steady_clock> expirationTime;

    static std::chrono::time_point<std::chrono::steady_clock> makeExpiration(int secs);
};

class LandingRequestToken : public RequestToken
{
public:
    virtual ~LandingRequestToken() = default;
    static std::unique_ptr<LandingRequestToken> build(const std::string& acID,
                                                      const std::string& rwID,
                                                      const std::string& psID);
private:
    LandingRequestToken(const std::string& acID, const std::string& rwID, const std::string& psID);

    std::string parkingStandID;
};

class TakeOffRequestToken : public RequestToken
{
public:
    virtual ~TakeOffRequestToken() = default;
    static std::unique_ptr<TakeOffRequestToken> build(const std::string& acID, const std::string& rwID);
private:
    TakeOffRequestToken(const std::string& acID, const std::string& rwID);
};


#endif //AIRPORTSIMULATOR_REQUESTTOKEN_H
