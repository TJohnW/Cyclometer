//
// Created by Tristan Whitcher on 3/10/16.
//

#include <iostream>
#include "UnitSet.h"
#include "States.h"
#include "SafeOutput.h"

void UnitSet::onEnter(Cyclometer &cyclometer) {
    SafeOutput::safe_output("State: UnitSet");
    cyclometer.getMotor()->setDirection(false);
    cyclometer.getMotor()->turnOn();
    SafeOutput::safe_output("IR Beam on.");
}

void UnitSet::accept(Cyclometer &cyclometer, Event event) {
    switch(event) {
        case BUTTON_PRESSED:
        case FULLY_CLOSED:
            cyclometer.transition(States::AUTO_MODE);
            break;
        case OVERCURRENT:
        case IR_BEAM:
            cyclometer.transition(States::TIRE_SET);
            break;
        default:
            break;
    }
}

void UnitSet::onExit(Cyclometer &cyclometer) {
    cyclometer.getMotor()->turnOff();
    SafeOutput::safe_output("IR Beam off.");
}
