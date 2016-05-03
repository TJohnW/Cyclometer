//
// Created by Tristan Whitcher on 3/10/16.
//

#ifndef GARAGECONTROLLER_OPENINGSTOPPED_H
#define GARAGECONTROLLER_OPENINGSTOPPED_H


#include "State.h"

class ManualMode : public State {

public:
    ManualMode(const std::string &name) : State(name) { }

    virtual void onEnter(Cyclometer &garage);
    virtual void accept(Cyclometer &garage, Event event);
    virtual void onExit(Cyclometer &garage);
};


#endif //GARAGECONTROLLER_OPENINGSTOPPED_H
