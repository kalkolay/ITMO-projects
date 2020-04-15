cmake_minimum_required(VERSION 3.15)
project(lab7)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_RELEASE "-DNDEBUG -Wall -O2")

add_executable(lab7 main.cpp cb_details.h circular_buffer.h)