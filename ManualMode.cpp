//
// Created by Tristan Whitcher on 3/10/16.
//

#include <iostream>
#include "ManualMode.h"
#include "States.h"
#include "SafeOutput.h"


void ManualMode::onEnter(Cyclometer &garage) {
    SafeOutput::safe_output("State: ManualMode");
}

void ManualMode::accept(Cyclometer &garage, Event event) {
    switch(event) {
        case BUTTON_PRESSED:
            garage.transition(States::UNIT_SET);
            break;
        default:
            break;
    }
}

void ManualMode::onExit(Cyclometer &garage) {

}
