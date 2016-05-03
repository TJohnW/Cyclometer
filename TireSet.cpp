//
// Created by Tristan Whitcher on 3/10/16.
//

#include <iostream>
#include "TireSet.h"
#include "States.h"
#include "SafeOutput.h"

void TireSet::onEnter(Cyclometer &garage) {
    SafeOutput::safe_output("State: TireSet");
    garage.getMotor()->setDirection(true);
    garage.getMotor()->turnOn();
}

void TireSet::accept(Cyclometer &garage, Event event) {
    switch(event) {
        case FULLY_OPEN:
        case BUTTON_PRESSED:
        case OVERCURRENT:
            garage.transition(States::MANUAL_MODE);
            break;
        default:
            break;
    }
}

void TireSet::onExit(Cyclometer &garage) {
    garage.getMotor()->turnOff();
}
