cmake_minimum_required(VERSION 3.3)
project(Cyclometer)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        states/UnitSet.cpp
        states/UnitSet.h
        states/Operating.cpp
        states/Operating.h
        Event.h
        Cyclometer.cpp
        Cyclometer.h
        CyclometerLaunch.cc
        InputController.cpp
        InputController.h
        states/TireSet.cpp
        states/TireSet.h
        ThreadUtils.cpp
        ThreadUtils.h
        util/State.cpp
        util/State.h
        states/States.cpp
        states/States.h
        OutputController.cpp
        OutputController.h
        Calculations.cpp
        Calculations.h
    )

link_directories(
        "/usr/local/lib"
)

add_executable(Cyclometer ${SOURCE_FILES})
target_link_libraries(Cyclometer glfw)
