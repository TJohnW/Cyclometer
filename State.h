//
// Created by Tristan Whitcher on 3/9/16.
//

#ifndef GARAGECONTROLLER_STATE_H
#define GARAGECONTROLLER_STATE_H


#include <iosfwd>
#include <string>
#include "Event.h"
#include "CyclometerLaunch.h"

class State {

    std::string name;

public:
    State(std::string name);

    virtual void onEnter(Cyclometer& garage) = 0;
    virtual void accept(Cyclometer& garage, Event event) = 0;
    virtual void onExit(Cyclometer& garage) = 0;

    std::string getName();

};


#endif //GARAGECONTROLLER_STATE_H
