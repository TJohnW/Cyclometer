//
// Created by Tristan Whitcher on 3/10/16.
//

#include <iostream>
#include "TireSet.h"
#include "States.h"
#include "SafeOutput.h"
#include "Cyclometer.h"

void TireSet::onEnter(Cyclometer &cyclometer) {
    SafeOutput::safe_output("State: TireSet");
    // do stuff
}

void TireSet::accept(Cyclometer &cyclometer, Event event) {
    switch(event) {
        case FULLY_OPEN:
        case BUTTON_PRESSED:
        case OVERCURRENT:
            cyclometer.transition(States::MANUAL_MODE);
            break;
        default:
            break;
    }
}

void TireSet::onExit(Cyclometer &cyclometer) {
    // do stuff
}
