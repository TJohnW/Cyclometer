//
// Created by Tristan Whitcher on 3/9/16.
//

#ifndef CYCLOMETERCONTROLLER_STATE_H
#define CYCLOMETERCONTROLLER_STATE_H


#include <iosfwd>
#include <string>
#include "Event.h"
#include "Cyclometer.h"

class State {

    std::string name;

public:
    State(std::string name);

    virtual void onEnter(Cyclometer& cyclometer) = 0;
    virtual void accept(Cyclometer& cyclometer, Event event) = 0;
    virtual void onExit(Cyclometer& cyclometer) = 0;

    std::string getName();

};


#endif //CYCLOMETERCONTROLLER_STATE_H
