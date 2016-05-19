//
// Created by Tristan Whitcher on 3/9/16.
//

#ifndef CYCLOMETERCONTROLLER_INPUTCONTROLLER_H
#define CYCLOMETERCONTROLLER_INPUTCONTROLLER_H


#include "Cyclometer.h"
#include "Calculations.h"

#define SET_BUTTON_IN (0)
#define START_STOP_BUTTON_IN (1)
#define MODE_BUTTON_IN (2)

class InputController {

    static Cyclometer* cyclometer;
    static Calculations *calculations;
    static bool enabled;

public:

    InputController(Cyclometer *pCyclometer, Calculations *pCalculations);

    static void forwardEvent(Event event);

    void run();

    static std::atomic_bool buttons[3];

    static bool waitTwoValidate(bool set, bool mode, bool startStop);

    static long timevaldiff(timeval *starttime, timeval *finishtime);

    bool waitForClear();
};


#endif //CYCLOMETERCONTROLLER_INPUTCONTROLLER_H
