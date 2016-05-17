//
// Created by Tristan Whitcher on 3/10/16.
//

#include <iostream>
#include "Operating.h"
#include "States.h"
#include "../ThreadUtils.h"

void Operating::onEnter(Cyclometer &cyclometer) {
    std::cout << this->getName() << std::endl;
    cyclometer.displayMode = 1;
}

void Operating::accept(Cyclometer &cyclometer, Event event) {
    switch(event) {
        case MODE_BUTTON:
            if(cyclometer.displayMode == 3) {
                cyclometer.displayMode = 1;
            } else {
                cyclometer.displayMode++;
            }
            break;
        case SET_BUTTON:
            //The cyclometer shall toggle between Manual and Auto mode each time the user presses the Set button while the display shows elapsed time or speed.
            if(cyclometer.displayMode == 1 || cyclometer.displayMode == 3) {
                cyclometer.getCalculations()->mode = !cyclometer.getCalculations()->mode;

            }
            break;
        case START_STOP_BUTTON:
            std::cout << "Toggling Should Calculate!" << std::endl;
            // In Manual mode, the Start/Stop button controls when trip calculations are performed. Pressing the Start/Stop button toggles calculation on and off.
            cyclometer.getCalculations()->shouldCalculate = !cyclometer.getCalculations()->shouldCalculate;
            break;
        default:
            break;
    }
}

void Operating::onExit(Cyclometer &cyclometer) {

}
