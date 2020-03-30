cmake_minimum_required(VERSION 3.15)
project(lab3)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_RELEASE "-DNDEBUG -Wall -O2")

add_executable(lab3 main.cpp file_exceptions.cpp file_exceptions.h pnm.cpp pnm.h config.h)