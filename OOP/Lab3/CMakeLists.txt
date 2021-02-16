cmake_minimum_required(VERSION 3.15)
project(Lab3)

set(CMAKE_CXX_STANDARD 17)

add_executable(Lab3
        main.cpp
        race_engine/entities/ITransport.h
        race_engine/Race.cpp
        race_engine/Race.h
        race_engine/entities/LandTransport.cpp
        race_engine/entities/LandTransport.h
        race_engine/entities/AirTransport.cpp
        race_engine/entities/AirTransport.h
        race_engine/utils/Utilities.h
        race_engine/exceptions/TransportTypeException.h race_engine/exceptions/RaceTypeException.h)