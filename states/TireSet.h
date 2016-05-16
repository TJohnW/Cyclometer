//
// Created by Tristan Whitcher on 3/10/16.
//

#ifndef CYCLOMETERCONTROLLER_TIRESET_H
#define CYCLOMETERCONTROLLER_TIRESET_H


#include "../util/State.h"
#include "../Cyclometer.h"

class TireSet : public State {

public:
    TireSet(const std::string &name) : State(name) { }

    virtual void onEnter(Cyclometer &cyclometer);

    virtual void accept(Cyclometer &cyclometer, Event event);

    virtual void onExit(Cyclometer &cyclometer);

    void updateDisplayData(Cyclometer &cyclometer);

private:
    bool isTicking = false;

    void incrementCircumference(Cyclometer &cyclometer);
};


#endif //CYCLOMETERCONTROLLER_TIRESET_H
