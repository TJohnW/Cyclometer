//
// Created by Tristan Whitcher on 3/10/16.
//

#ifndef CYCLOMETERCONTROLLER_AUTOMODE_H
#define CYCLOMETERCONTROLLER_AUTOMODE_H


#include "State.h"

class AutoMode : public State {

public:
    AutoMode(const std::string &name) : State(name) { }

    virtual void onEnter(Cyclometer &cyclometer);

    virtual void accept(Cyclometer &cyclometer, Event event);

    virtual void onExit(Cyclometer &cyclometer);
};


#endif //CYCLOMETERCONTROLLER_AUTOMODE_H
