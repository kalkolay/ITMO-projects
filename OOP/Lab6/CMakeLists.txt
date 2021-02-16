cmake_minimum_required(VERSION 3.17)
project(Lab6)

set(CMAKE_CXX_STANDARD 17)

set(Boost_INCLUDE_DIR /usr/local/Cellar/boost/1.74.0/include/)
set(Boost_LIBRARY_DIR /usr/local/Cellar/boost/1.74.0/lib/)
find_package(Boost 1.74.0 REQUIRED COMPONENTS serialization)
if(NOT Boost_FOUND)
    message(FATAL_ERROR "Could not find Boost!")
endif()
include_directories(${Boost_INCLUDE_DIR})

find_package(SQLite3)
if(SQLITE3_FOUND)
    include_directories(${SQLITE3_INCLUDE_DIRS})
endif(SQLITE3_FOUND)

add_executable(Lab6
        main.cpp
        BLL/entities/collaborator/Collaborator.cpp
        BLL/entities/collaborator/Collaborator.h
        BLL/entities/task/Task.cpp
        BLL/entities/task/Task.h
        BLL/entities/collaborator/CollaboratorSystem.cpp
        BLL/entities/collaborator/CollaboratorSystem.h
        BLL/entities/task/TaskSystem.cpp
        BLL/entities/task/TaskSystem.h
        BLL/entities/task/TaskComment.cpp
        BLL/entities/task/TaskComment.h
        BLL/entities/report/ReportPerDay.cpp
        BLL/entities/report/ReportPerDay.h
        BLL/entities/report/ReportPerSprint.cpp
        BLL/entities/report/ReportPerSprint.h
        BLL/exceptions/UnfamiliarTaskException.h
        BLL/exceptions/UnresolvedTaskException.h
        BLL/exceptions/OverdueReportException.h
        BLL/exceptions/UnfamiliarReportException.h
        BLL/entities/report/CommandReport.cpp
        BLL/entities/report/CommandReport.h
        DAL/collaborators_bd/CollaboratorData.cpp
        DAL/collaborators_bd/CollaboratorData.h
        DAL/reports_bd/ReportData.cpp
        DAL/reports_bd/ReportData.h
        DAL/tasks_bd/TaskData.cpp
        DAL/tasks_bd/TaskData.h
        DAL/Data.cpp
        DAL/Data.h
        DAL/Utilities.h
        UIL/CollaboratorManager.cpp
        UIL/CollaboratorManager.h
        UIL/ReportManager.cpp
        UIL/ReportManager.h
        UIL/TaskManager.cpp
        UIL/TaskManager.h)

if(SQLITE3_FOUND)
    target_link_libraries(Lab6 ${SQLite3_LIBRARIES} ${Boost_LIBRARIES})
endif(SQLITE3_FOUND)