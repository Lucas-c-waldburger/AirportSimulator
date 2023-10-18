cmake_minimum_required(VERSION 3.7)
project(AirportSimulator)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp src/StateManager.cpp include/StateManager.h src/AircraftRequest.cpp include/AircraftRequest.h src/Airport.cpp include/Airport.h src/Location.cpp include/Location.h src/RequestToken.cpp include/RequestToken.h)
add_executable(AirportSimulator ${SOURCE_FILES})