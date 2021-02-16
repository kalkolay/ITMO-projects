cmake_minimum_required(VERSION 3.17)
project(Lab5)

set(CMAKE_CXX_STANDARD 17)

set(Boost_INCLUDE_DIR /usr/local/Cellar/boost/1.74.0/include/)
set(Boost_LIBRARY_DIR /usr/local/Cellar/boost/1.74.0/lib/)
find_package(Boost 1.74.0)
if(NOT Boost_FOUND)
    message(FATAL_ERROR "Could not find Boost!")
endif()
include_directories(${Boost_INCLUDE_DIR})

add_executable(Lab5
               main.cpp
               banks/entities/Bank.cpp
               banks/entities/Bank.h
               banks/entities/Client.cpp
               banks/entities/Client.h
               banks/entities/Account.cpp
               banks/entities/Account.h
               banks/entities/DebitAccount.cpp
               banks/entities/DebitAccount.h
               banks/entities/Deposit.cpp
               banks/entities/Deposit.h
               banks/entities/CreditAccount.cpp
               banks/entities/CreditAccount.h
               banks/utilities/Utilities.cpp
               banks/utilities/Utilities.h
        banks/entities/AccountManager.cpp
        banks/entities/AccountManager.h banks/entities/Transaction.cpp banks/entities/Transaction.h)