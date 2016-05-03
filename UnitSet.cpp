//
// Created by Tristan Whitcher on 3/10/16.
//

#include <iostream>
#include "UnitSet.h"
#include "States.h"
#include "SafeOutput.h"

void UnitSet::onEnter(Cyclometer &garage) {
    SafeOutput::safe_output("State: UnitSet");
    garage.getMotor()->setDirection(false);
    garage.getMotor()->turnOn();
    SafeOutput::safe_output("IR Beam on.");
}

void UnitSet::accept(Cyclometer &garage, Event event) {
    switch(event) {
        case BUTTON_PRESSED:
        case FULLY_CLOSED:
            garage.transition(States::AUTO_MODE);
            break;
        case OVERCURRENT:
        case IR_BEAM:
            garage.transition(States::TIRE_SET);
            break;
        default:
            break;
    }
}

void UnitSet::onExit(Cyclometer &garage) {
    garage.getMotor()->turnOff();
    SafeOutput::safe_output("IR Beam off.");
}
