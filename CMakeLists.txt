cmake_minimum_required(VERSION 3.3)
project(Cyclometer)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    Application.cpp
    Application.h
        UnitSet.cpp
        UnitSet.h
        AutoMode.cpp
        AutoMode.h
    Event.h
        Cyclometer.cpp
        Cyclometer.h
        CyclometerLaunch.cc
    InputController.cpp
    InputController.h
    IOPort.cpp
    IOPort.h
    Observer.cpp
    Observer.h
        TireSet.cpp
        TireSet.h
        ManualMode.cpp
        ManualMode.h
    SafeOutput.cpp
    SafeOutput.h
    State.cpp
    State.h
    States.cpp
    States.h
    Subject.cpp
    Subject.h OutputController.cpp OutputController.h)

add_executable(Cyclometer ${SOURCE_FILES})