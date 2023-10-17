//
// Created by Lower School Music on 10/17/23.
//

#ifndef AIRPORTSIMULATOR_AIRCRAFTREQUEST_H
#define AIRPORTSIMULATOR_AIRCRAFTREQUEST_H


// Base request Functor class
// declares request function
// *Need separate function/struct inside Airport to do stuff with the reply received from LandingRequest & TakeOffRequest

// class LandingRequest : public Aircraft Request
// initialized with an aircraft ID
// stored for use when creating token
// iterate through available runways, get their state
// if (found available runway)
    // assemble corresponding request token with:
        // the ID of the aircraft making the request
        // the ID of the runway/parkingStand found to be available
        //

class AircraftRequest
{
public:

    // virtual



    // enum class Reply
    // {
        // HOLD,
        // PROCEED
    // };
    //
    // class RequestToken
    // {
    // public:
        //
        //
    // private:
        //
        // std::string aircraftID;
        //
    // };

    //

private:

};


#endif //AIRPORTSIMULATOR_AIRCRAFTREQUEST_H
