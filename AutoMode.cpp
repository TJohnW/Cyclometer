//
// Created by Tristan Whitcher on 3/10/16.
//

#include <iostream>
#include "AutoMode.h"
#include "States.h"
#include "SafeOutput.h"

void AutoMode::onEnter(Cyclometer &cyclometer) {
    SafeOutput::safe_output("State: AutoMode");
}

void AutoMode::accept(Cyclometer &cyclometer, Event event) {
    switch(event) {
        case BUTTON_PRESSED:
            cyclometer.transition(States::TIRE_SET);
            break;
        default:
            break;
    }
}

void AutoMode::onExit(Cyclometer &cyclometer) {

}
