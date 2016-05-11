//
// Created by Tristan Whitcher on 3/10/16.
//

#ifndef CYCLOMETERCONTROLLER_STATES_H
#define CYCLOMETERCONTROLLER_STATES_H


#include "State.h"
#include "AutoMode.h"
#include "ManualMode.h"
#include "UnitSet.h"
#include "TireSet.h"

class States {
public:
    static State* AUTO_MODE;
    static State* MANUAL_MODE;
    static State* UNIT_SET;
    static State* TIRE_SET;
};

#endif //CYCLOMETERCONTROLLER_STATES_H
