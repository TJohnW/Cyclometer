//
// Created by Tristan Whitcher on 3/10/16.
//

#ifndef GARAGECONTROLLER_CONCRETESTATE_H
#define GARAGECONTROLLER_CONCRETESTATE_H


#include "State.h"

class AutoMode : public State {

public:
    AutoMode(const std::string &name) : State(name) { }

    virtual void onEnter(Cyclometer &garage);

    virtual void accept(Cyclometer &garage, Event event);

    virtual void onExit(Cyclometer &garage);
};


#endif //GARAGECONTROLLER_CONCRETESTATE_H
