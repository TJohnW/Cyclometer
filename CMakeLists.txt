cmake_minimum_required(VERSION 3.3)
project(Cyclometer)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    Application.cpp
    Application.h
    Closing.cpp
    Closing.h
    ClosingStopped.cpp
    ClosingStopped.h
    Event.h
    Garage.cpp
    Garage.h
    GarageController.cc
    InputController.cpp
    InputController.h
    IOPort.cpp
    IOPort.h
    Motor.cpp
    Motor.h
    Observer.cpp
    Observer.h
    Opening.cpp
    Opening.h
    OpeningStopped.cpp
    OpeningStopped.h
    SafeOutput.cpp
    SafeOutput.h
    State.cpp
    State.h
    States.cpp
    States.h
    Subject.cpp
    Subject.h)

add_executable(Cyclometer ${SOURCE_FILES})