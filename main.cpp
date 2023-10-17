#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

using namespace std;
using namespace std::chrono;

/**
 * @defgroup Boilerplate
 * Basic support for logging and random sleeps. Nothing exciting to see here.
 * @{ */

/** Some simple thread-safe logging functionality. */
namespace {

class Logger
{
 public:
  static void Log()
  {
    lock_guard<recursive_mutex> lock(s_mutex);
    std::cout << std::endl;
  }

  // calls lock_guard for each recursion
  // prints each Arg to cout
  template<typename First, typename ...Rest>
  static void Log(First&& first, Rest&& ...rest)
  {
    lock_guard<recursive_mutex> lock(s_mutex);
    std::cout << std::forward<First>(first);
    Log(std::forward<Rest>(rest)...);
  }

 private:
  static recursive_mutex s_mutex;
};

recursive_mutex Logger::s_mutex;

/** Produces a random integer within the [1..max] range. */
int RandomInt(int maxValue = 6)
{
  const int minValue = 1;
  return minValue + (rand() % static_cast<int>(maxValue - minValue + 1));
}

}

/** @} */

/** A runway, essential for air travel. */
class Runway {
  /* TODO: implement :-) */
};

/** Parking stand. Useful whether you're in a 747-800 or a station wagon. */
class ParkingStand {
  /* TODO: implement :-) */
};

/** Simulation of an airport. Tiny preview of the headaches that come with the real thing. */
class Airport {
 public:
  /** Duration of an airport operation. */
  static constexpr const int kOperationDurationSec = 5;
  /** Validity of a token. Provided for convenience only, client should not rely on this time to assume the token is valid. */
  static constexpr const int kTokenExpirationTimeSec = 2;

  Airport(unsigned numberOfRunways, unsigned numberOfParkingStands)
  {}

  /* TODO: implement :-) */

//  unsigned mNumRunways;
//  unsigned mNumParkingStands;

};

int main() {
  const unsigned numberOfClients = 30;
  const unsigned numberOfRunways = 5;
  const unsigned numberOfParkingStands = 10;

  // Init Airport
  Airport airport{numberOfRunways, numberOfParkingStands};

  // Now spin a number of threads simulating some aircrafts.

  vector<shared_ptr<thread>> aircrafts;

  for (int i = 0; i < numberOfClients; i++)
  {
    aircrafts.push_back(make_shared<thread>([&airport, i]() // <- here we are initilaizing a thread with a lambda "aircraftOperations" function
    {
      string id = "Aircraft " + to_string(i);

      bool landingSuccessful = false;

      while (!landingSuccessful)
      {

        /////////////////////////////////////////////////////////////////////////////////////////////////////////
        // TODO:
        // Attempt calling into Airport::RequestLanding until landing token is successfully received.
        // Repeat otherwise.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////

        Logger::Log(id, " received a landing token.");

        // Wait some random time. In some cases the token will expire, that's OK.
        this_thread::sleep_for(seconds{RandomInt(2*Airport::kTokenExpirationTimeSec)}); // <- sleep main thread

        // if (tokenNotExpired)
        /////////////////////////////////////////////////////////////////////////////////////////////////////////
        // TODO:
        // Attempt calling into Airport::PerformLanding and break out of the loop if it's successful.
        // Allow the loop to repeat otherwise.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////

        if (!landingSuccessful)
        {
          Logger::Log(id, " landing token expired. It will try again.");
        }

      }

      Logger::Log(id + " has successfully landed.");

      // Sleep for at least the time of landing operation plus some random time
      this_thread::sleep_for(seconds{seconds{Airport::kOperationDurationSec + RandomInt()}});

      Logger::Log(id, " is attempting a take-off.");

      bool takeOffSuccessful = false;

      while (!takeOffSuccessful)
      {
        /////////////////////////////////////////////////////////////////////////////////////////////////////////
        // TODO:
        // Attempt calling into Airport::RequestTakeoff until take-off token is successfully received.
        // Repeat otherwise.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////

        Logger::Log(id, " received a take-off token.");

        // Wait some random time. In some cases the token will expire, that's OK.
        this_thread::sleep_for(seconds{RandomInt(2*Airport::kTokenExpirationTimeSec)});

        /////////////////////////////////////////////////////////////////////////////////////////////////////////
        // TODO:
        // Attempt calling into Airport::PerformTakeoff and break out of the loop if it's successful.
        // Allow the loop to repeat otherwise.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////

        if (!takeOffSuccessful)
        {
          Logger::Log(id, " take-off token expired. It will try again.\n");
        }
      }

      Logger::Log(id + " has successfully departed.");

    }));
  }

  for (auto aircraft : aircrafts) {
    aircraft->join();
  }

  Logger::Log("All done. Simulation terminating.");

  return 0;
}