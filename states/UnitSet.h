//
// Created by Tristan Whitcher on 3/10/16.
//

#ifndef CYCLOMETERCONTROLLER_UNITSET_H
#define CYCLOMETERCONTROLLER_UNITSET_H


#include "../util/State.h"

class UnitSet : public State {

public:

    UnitSet(const std::string &name) : State(name) { }

    virtual void onEnter(Cyclometer &cyclometer);

    virtual void accept(Cyclometer &cyclometer, Event event);

    virtual void onExit(Cyclometer &cyclometer);

    void updateDisplayData(Cyclometer &cyclometer);

    void toggleUnits(Cyclometer &cyclometer);
};


#endif //CYCLOMETERCONTROLLER_UNITSET_H
