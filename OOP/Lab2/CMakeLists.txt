cmake_minimum_required(VERSION 3.15)
project(Lab2)

set(CMAKE_CXX_STANDARD 17)

set(Boost_INCLUDE_DIR /usr/local/Cellar/boost/1.74.0/include/)
set(Boost_LIBRARY_DIR /usr/local/Cellar/boost/1.74.0/lib/)
find_package(Boost 1.74.0)
if(NOT Boost_FOUND)
    message(FATAL_ERROR "Could not find Boost!")
endif()
include_directories(${Boost_INCLUDE_DIR})

add_executable(Lab2
               main.cpp
               shop_manager/entities/Product.cpp
               shop_manager/entities/Product.h
               shop_manager/entities/ProductWrapper.cpp
               shop_manager/entities/ProductWrapper.h
               shop_manager/entities/Shop.cpp
               shop_manager/entities/Shop.h
               shop_manager/ShopManager.cpp
               shop_manager/ShopManager.h
               shop_manager/utilities/Utilities.cpp
               shop_manager/utilities/Utilities.h)