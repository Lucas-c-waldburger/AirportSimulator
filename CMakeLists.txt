cmake_minimum_required(VERSION 3.7)
project(AirportSimulator)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp src/Airport.cpp include/Airport.h src/RequestToken.cpp include/RequestToken.h include/LocationManager.h src/Runway.cpp include/Runway.h src/ParkingStand.cpp include/ParkingStand.h src/Logger.cpp include/Logger.h)
add_executable(AirportSimulator ${SOURCE_FILES})