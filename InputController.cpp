//
// Created by Tristan Whitcher on 3/9/16.
//

#include <iostream>
#include <stdio.h>
#include <termios.h>
#include <sys/time.h>
#include "InputController.h"

Cyclometer* InputController::cyclometer;
Calculations* InputController::calculations;
std::atomic_bool InputController::buttons[3];


InputController::InputController(Cyclometer* cyclometer, Calculations *pCalculations) {
    InputController::cyclometer = cyclometer;
    InputController::calculations = pCalculations;
}


void InputController::forwardEvent(Event event) {
    if(event == PULSE) {
        calculations->pulse();
    } else {
        cyclometer->queueEvent(event);
    }
}

void InputController::run() {

    bool ticking = false;

    while(true) {
        usleep(10000);

        if(ticking) {
            if(buttons[MODE_BUTTON_IN] && !buttons[START_STOP_BUTTON_IN] && !buttons[SET_BUTTON_IN]) {
                forwardEvent(MODE_TICK);
                usleep(1000000);
                continue;
            } else {
                ticking = false;
                continue;
            }
        }

        // if any buttons are down
        if(buttons[SET_BUTTON_IN] || buttons[MODE_BUTTON_IN] || buttons[START_STOP_BUTTON_IN]) {
            // wait for a moderate amount of time for inputs to settle
            usleep(200000);
        }

        // what event is this


        // ALL THREE
        if(buttons[SET_BUTTON_IN] && buttons[MODE_BUTTON_IN] && buttons[START_STOP_BUTTON_IN]) {
            if(waitTwoValidate(true, true, true)) {
                forwardEvent(FULL_RESET);
                waitForClear();
            }

            continue;
        }

        // MODE AND START STOP
        if(buttons[MODE_BUTTON_IN] && buttons[START_STOP_BUTTON_IN]) {
            if(waitTwoValidate(false, true, true)) {
                forwardEvent(RESET_TRIP);
                waitForClear();
            }

            continue;
        }

        // ONLY MODE
        if(buttons[MODE_BUTTON_IN] && !buttons[START_STOP_BUTTON_IN] && !buttons[SET_BUTTON_IN]) {
            if(waitTwoValidate(false, true, false)) {
                ticking = true;
            } else {
                forwardEvent(MODE_BUTTON);
                std::cout << "MODE BUTTON" << std::endl;
            }

            continue;
        }


        // ONLY SET
        if(buttons[SET_BUTTON_IN] && !buttons[START_STOP_BUTTON_IN] && !buttons[MODE_BUTTON_IN]) {
            forwardEvent(SET_BUTTON);
            waitForClear();
            continue;

        }

        // ONLY START STOP
        if(buttons[START_STOP_BUTTON_IN] && !buttons[SET_BUTTON_IN] && !buttons[MODE_BUTTON_IN]) {
            forwardEvent(START_STOP_BUTTON);
            waitForClear();
            continue;

        }

    }
}

bool InputController::waitTwoValidate(bool set, bool mode, bool startStop) {

    timeval startTV, endTV;

    gettimeofday(&startTV, NULL);
    gettimeofday(&endTV, NULL);

    while((endTV.tv_sec * 1e6 + endTV.tv_usec - (startTV.tv_sec * 1e6 + startTV.tv_usec)) <= 2000000 - 200000) {
        if(buttons[SET_BUTTON_IN] == set && buttons[MODE_BUTTON_IN] == mode && buttons[START_STOP_BUTTON_IN] == startStop) {
        } else {
            return false;
        }
        usleep(10000);
        gettimeofday(&endTV, NULL);
    }

    return true;
}

bool InputController::waitForClear() {
    while(buttons[SET_BUTTON_IN] || buttons[MODE_BUTTON_IN] || buttons[START_STOP_BUTTON_IN]) {
        usleep(10000);
    }
}



