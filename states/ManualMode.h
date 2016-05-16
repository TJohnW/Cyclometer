//
// Created by Tristan Whitcher on 3/10/16.
//

#ifndef CYCLOMETERCONTROLLER_MANUALMODE_H
#define CYCLOMETERCONTROLLER_MANUALMODE_H


#include "../util/State.h"

class ManualMode : public State {

public:
    ManualMode(const std::string &name) : State(name) { }

    virtual void onEnter(Cyclometer &cyclometer);
    virtual void accept(Cyclometer &cyclometer, Event event);
    virtual void onExit(Cyclometer &cyclometer);
};


#endif //CYCLOMETERCONTROLLER_MANUALMODE_H
