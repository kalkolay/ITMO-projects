cmake_minimum_required(VERSION 3.15)
project(Lab4)

set(CMAKE_CXX_STANDARD 17)

set(Boost_INCLUDE_DIR /usr/local/Cellar/boost/1.74.0/include/)
set(Boost_LIBRARY_DIR /usr/local/Cellar/boost/1.74.0/lib/)
find_package(Boost 1.74.0)
if(NOT Boost_FOUND)
    message(FATAL_ERROR "Could not find Boost!")
endif()
include_directories(${Boost_INCLUDE_DIR})

add_executable(Lab4
        main.cpp
        backup_system/entities/AbsoluteRestorePoint.cpp
        backup_system/entities/AbsoluteRestorePoint.h
        backup_system/entities/IncrementalRestorePoint.cpp
        backup_system/entities/IncrementalRestorePoint.h
        backup_system/entities/Backup.cpp
        backup_system/entities/Backup.h
        backup_system/entities/FileInfo.cpp
        backup_system/entities/FileInfo.h
        backup_system/utilities/Utilities.h)