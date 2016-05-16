//
// Created by Tristan Whitcher on 3/10/16.
//

#include "ManualMode.h"
#include "States.h"


void ManualMode::onEnter(Cyclometer &cyclometer) {

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
