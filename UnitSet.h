//
// Created by Tristan Whitcher on 3/10/16.
//

#ifndef GARAGECONTROLLER_CLOSING_H
#define GARAGECONTROLLER_CLOSING_H


#include "State.h"

class UnitSet : public State {

public:
    UnitSet(const std::string &name) : State(name) { }

    virtual void onEnter(Cyclometer &garage);

    virtual void accept(Cyclometer &garage, Event event);

    virtual void onExit(Cyclometer &garage);
};


#endif //GARAGECONTROLLER_CLOSING_H
