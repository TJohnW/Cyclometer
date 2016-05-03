//
// Created by Tristan Whitcher on 3/10/16.
//

#ifndef GARAGECONTROLLER_OPENING_H
#define GARAGECONTROLLER_OPENING_H


#include "State.h"

class TireSet : public State {

public:
    TireSet(const std::string &name) : State(name) { }

    virtual void onEnter(Cyclometer &garage);

    virtual void accept(Cyclometer &garage, Event event);

    virtual void onExit(Cyclometer &garage);
};


#endif //GARAGECONTROLLER_OPENING_H
