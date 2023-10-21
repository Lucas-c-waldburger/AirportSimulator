#include <chrono>
#include <iostream>
#include <thread>
#include <vector>
#include "include/Airport.h"

using namespace std;
using namespace chrono;


int RandomInt(int maxValue = 6)
{
  const int minValue = 1;
  return minValue + (rand() % static_cast<int>(maxValue - minValue + 1));
}


int main()
{
    const unsigned numberOfClients = 30;
    const unsigned numberOfRunways = 5;
    const unsigned numberOfParkingStands = 10;

    Airport airport{ numberOfRunways, numberOfParkingStands };

    vector<shared_ptr<thread>> aircrafts;

    for (int i = 0; i < numberOfClients; i++)
    {
        aircrafts.push_back(make_shared<thread>([&airport, i]()
        {
            string id = "Aircraft " + to_string(i);

            bool landingSuccessful = false;

            unique_ptr<RequestToken> landingRequestToken;
            std::unique_ptr<std::thread> landingOpTimer;

            while (!landingSuccessful)
            {
                // AIRCRAFT IS NOT in runway and NOT in parkingStand
                //
                // keep requesting, once non-null pointer to request token recieved, proceed
                do
                {
                    landingRequestToken = airport.requestLanding(id);

                } while (!landingRequestToken);
                Logger::Log(id, " - found RW: ", landingRequestToken->runwayID, "& found parking stand: ", landingRequestToken->parkingStandID, '\n');

                Logger::Log(id, " received a landing token.");

                // Wait some random time. In some cases the token will expire, that's OK.
                this_thread::sleep_for(seconds{ RandomInt(2 * kTokenExpirationTimeSec) });

                landingOpTimer = airport.performLanding(*landingRequestToken);

                if (landingOpTimer)
                {
                    landingSuccessful = true;
                    break;
                }

                if (!landingSuccessful)
                {
                    Logger::Log(id, " landing token expired. It will try again.");
                }

            }

            landingOpTimer->join(); // wait until landing procedure complete

            Logger::Log(id + " has successfully landed.");

            // Sleep for at least the time of landing operation plus some random time
            this_thread::sleep_for(seconds{ seconds{kOperationDurationSec + RandomInt()} });

            Logger::Log(id, " is attempting a take-off.");

            bool takeOffSuccessful = false;

            unique_ptr<RequestToken> takeOffRequestToken;
            unique_ptr<std::thread> takeOffOpTimer;

            while (!takeOffSuccessful)
            {
                // AIRCRAFT IS IN PARKING STAND, NOT IN RUNWAY

                do
                {
                    takeOffRequestToken = airport.requestTakeOff(id);
                } while (!takeOffRequestToken);

                Logger::Log(id, " - found RW: ", takeOffRequestToken->runwayID, "& found parking stand: ", takeOffRequestToken->parkingStandID);

                Logger::Log(id, " received a take-off token.");

                // Wait some random time. In some cases the token will expire, that's OK.
                this_thread::sleep_for(seconds{ RandomInt(2 * kTokenExpirationTimeSec) });

                // put parkingStandID from the landingRequestToken into the TakeOffRequest token so the timer inside PerformTakeOff
                // can use it for its timer
                Logger::Log(id, " - exp time before setting pStand id: ", takeOffRequestToken->expirationTime);
                takeOffRequestToken->parkingStandID = landingRequestToken->parkingStandID;
                Logger::Log(id, " - exp time after: ", takeOffRequestToken->expirationTime);

                takeOffOpTimer = airport.performTakeOff(*takeOffRequestToken);

                if (takeOffOpTimer)
                {
                    Logger::Log(id, " had a non-null takeOffTimer thread");

                    takeOffSuccessful = true;
                    break;
                }

                if (!takeOffSuccessful)
                {
                    //Logger::Log(id, " take-off token expired. It will try again.\n");
                }
            }

            takeOffOpTimer->join();

            Logger::Log(id + " has successfully departed.");
        }));
    }

    for (auto& aircraft : aircrafts) {
        aircraft->join();
    }

    Logger::Log("All done. Simulation terminating.");

    return 0;
}