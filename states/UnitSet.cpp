//
// Created by Tristan Whitcher on 3/10/16.
//

#include <iostream>
#include "UnitSet.h"
#include "States.h"
#include "../ThreadUtils.h"
#include "../OutputController.h"

void UnitSet::onEnter(Cyclometer &cyclometer) {
    std::cout << this->getName() << std::endl;
    cyclometer.getCyclometerData()->fullReset();
    cyclometer.getCyclometerData()->kilometers = true;
    updateDisplayData(cyclometer);
}

void UnitSet::accept(Cyclometer &cyclometer, Event event) {
    switch(event) {
        case FULL_RESET:
            cyclometer.transition(States::UNIT_SET);
            break;
        case MODE_BUTTON:
            toggleUnits(cyclometer);
            updateDisplayData(cyclometer);
            break;
        case SET_BUTTON:
            cyclometer.transition(States::TIRE_SET);
            break;
        default:
            break;
    }
}

void UnitSet::onExit(Cyclometer &cyclometer) { }

void UnitSet::updateDisplayData(Cyclometer &cyclometer) {
    CyclometerData* data = cyclometer.getCyclometerData();
    OutputController::resetDisplay();
    if(data->kilometers) {
        OutputController::digitFour = 1;
    } else {
        OutputController::digitFour = 2;
    }
}

void UnitSet::toggleUnits(Cyclometer &cyclometer) {
    cyclometer.getCyclometerData()->kilometers = !cyclometer.getCyclometerData()->kilometers;
}


/*
    case FULL_RESET: break;
    case RESET_TRIP: break;
    case MODE_BUTTON: break;
    case MODE_TICK: break;
    case SET_BUTTON: break;
    case START_STOP_BUTTON: break;
    default: break;

         */
