//
// Created by Tristan Whitcher on 5/11/16.
//

#include <string>
#include <iostream>
#include "OutputController.h"

static Cyclometer* OutputController::cyclometer;

std::atomic<int> OutputController::digitOne = {-1}; // left digit
std::atomic_bool OutputController::decimalOne = {false};

std::atomic<int> OutputController::digitTwo = {-1};
std::atomic_bool OutputController::decimalTwo = {false};

std::atomic<int> OutputController::digitThree = {-1};
std::atomic_bool OutputController::decimalThree = {false};

std::atomic<int> OutputController::digitFour = {-1}; // right digit
std::atomic_bool OutputController::decimalFour = {false};


OutputController::OutputController(Cyclometer *pCyclometer) : cyclometer(pCyclometer) {

}

void OutputController::run() {
    CyclometerData* data = cyclometer->getCyclometerData();
    while(true) {
        std::string out = "";

        out += (OutputController::digitOne != -1) ? std::to_string(OutputController::digitOne) : "-";
        if(OutputController::decimalOne)
            out += ".";

        out += (OutputController::digitTwo != -1) ? std::to_string(OutputController::digitTwo) : "-";
        if(OutputController::decimalTwo)
            out += ".";

        out += (OutputController::digitThree != -1) ? std::to_string(OutputController::digitThree) : "-";
        if(OutputController::decimalThree)
            out += ".";

        out += (OutputController::digitFour != -1) ? std::to_string(OutputController::digitFour) : "-";
        if(OutputController::decimalFour)
            out += ".";

        std::cout << out << std::endl;
        sleep(1);
    }
}


/**
 * Called to reset the display values
 */
void OutputController::resetDisplay() {
    decimalOne = false;
    decimalTwo = false;
    decimalThree = false;
    decimalFour = false;
    digitOne = -1;
    digitTwo = -1;
    digitThree = -1;
    digitFour = -1;
}


/**
 * Called by a different thread to update the display values based on the display mode
 */
void OutputController::updateDisplayValues(int displayMode) {
    Cyclometer* cyclometer = OutputController::cyclometer;
    switch(displayMode) {
        case 0: break;
        case 1:
            OutputController::setSpeedDisplay(cyclometer);
            break;
        case 2:
            OutputController::setDistanceDisplay(cyclometer);
            break;
        case 3:
            OutputController::setTimeDisplay(cyclometer);
            break;
        default:
            break;
    }
}

void OutputController::setSpeedDisplay(Cyclometer* cyclometer) {

}

void OutputController::setDistanceDisplay(Cyclometer *pCyclometer) {

}

void OutputController::setTimeDisplay(Cyclometer *pCyclometer) {

}



















