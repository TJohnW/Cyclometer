//
// Created by Tristan Whitcher on 3/10/16.
//

#include <iostream>
#include "TireSet.h"
#include "States.h"
#include "../OutputController.h"

void TireSet::onEnter(Cyclometer &cyclometer) {

    std::cout << this->getName() << std::endl;
    cyclometer.getCalculations()->circumference = 210;
    updateDisplayData(cyclometer);
}

void TireSet::accept(Cyclometer &cyclometer, Event event) {
    switch(event) {
        case FULL_RESET:
            cyclometer.transition(States::UNIT_SET);
            break;
        case RESET_TRIP: break;
        case MODE_BUTTON:
            if(isTicking) {
                isTicking = false;
            } else {
                incrementCircumference(cyclometer);
            }
            break;
        case MODE_TICK:
            isTicking = true;
            incrementCircumference(cyclometer);
            break;
        case SET_BUTTON:
            cyclometer.transition(States::OPERATING);
        case START_STOP_BUTTON: break;
        default: break;
    }
}

void TireSet::onExit(Cyclometer &cyclometer) {

}

void TireSet::updateDisplayData(Cyclometer &cyclometer) {
    Calculations* data = cyclometer.getCalculations();
    OutputController::resetDisplay();
    OutputController::setSegments(data->circumference);
}

void TireSet::incrementCircumference(Cyclometer &cyclometer) {
    cyclometer.getCalculations()->circumference++;
    if (cyclometer.getCalculations()->circumference > 220) {
        cyclometer.getCalculations()->circumference = 190;
    }
    updateDisplayData(cyclometer);
}


