//
// Created by Tristan Whitcher on 3/10/16.
//

#include <iostream>
#include "TireSet.h"
#include "States.h"
#include "../OutputController.h"

void TireSet::onEnter(Cyclometer &cyclometer) {

    std::cout << this->getName() << std::endl;
    cyclometer.getCyclometerData()->circumference = 210;
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
            if(cyclometer.priorState == States::UNIT_SET)
                cyclometer.transition(States::MANUAL_MODE);
            else
                cyclometer.transition(cyclometer.priorState);
            break;
        case START_STOP_BUTTON: break;
        default: break;
    }
}

void TireSet::onExit(Cyclometer &cyclometer) {

}

void TireSet::updateDisplayData(Cyclometer &cyclometer) {
    CyclometerData* data = cyclometer.getCyclometerData();
    OutputController::resetDisplay();
    data->setSegments(data->circumference);
}

void TireSet::incrementCircumference(Cyclometer &cyclometer) {
    cyclometer.getCyclometerData()->circumference++;
    if (cyclometer.getCyclometerData()->circumference > 220) {
        cyclometer.getCyclometerData()->circumference = 190;
    }
    updateDisplayData(cyclometer);
}


