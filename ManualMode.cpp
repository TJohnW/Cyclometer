//
// Created by Tristan Whitcher on 3/10/16.
//

#include <iostream>
#include "ManualMode.h"
#include "States.h"
#include "SafeOutput.h"


void ManualMode::onEnter(Cyclometer &cyclometer) {
    SafeOutput::safe_output("State: ManualMode");
}

void ManualMode::accept(Cyclometer &cyclometer, Event event) {
    switch(event) {
        case FULL_RESET:
            cyclometer.transition(States::UNIT_SET);
            break;
        default:
            break;
    }
}

void ManualMode::onExit(Cyclometer &cyclometer) {

}
