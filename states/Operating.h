//
// Created by Tristan Whitcher on 3/10/16.
//

#ifndef CYCLOMETERCONTROLLER_OPERATING_H
#define CYCLOMETERCONTROLLER_OPERATING_H


#include "../util/State.h"

class Operating : public State {

public:
    Operating(const std::string &name) : State(name) { }

    virtual void onEnter(Cyclometer &cyclometer);

    virtual void accept(Cyclometer &cyclometer, Event event);

    virtual void onExit(Cyclometer &cyclometer);
};


#endif //CYCLOMETERCONTROLLER_OPERATING_H
