cmake_minimum_required(VERSION 3.13)
project(hw8)

set(CMAKE_CXX_STANDARD 14)

add_executable(hw8 main.cpp Headers/Animal.h Headers/Bear.h Headers/Man.h Headers/ManBearPig.h Headers/Pig.h Headers/Unit.h Sources/Animal.cpp Sources/Bear.cpp Sources/Man.cpp Sources/ManBearPig.cpp Sources/Pig.cpp Sources/Unit.cpp)