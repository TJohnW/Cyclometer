//
// Created by Tristan Whitcher on 3/9/16.
//

#ifndef CYCLOMETERCONTROLLER_INPUTCONTROLLER_H
#define CYCLOMETERCONTROLLER_INPUTCONTROLLER_H


#include <GLFW/glfw3.h>
#include "Cyclometer.h"
#include "Calculations.h"

class InputController {

    static Cyclometer* cyclometer;
    static Calculations *calculations;
    static bool enabled;

public:

    InputController(Cyclometer *pCyclometer, Calculations *pCalculations);

    static void forwardEvent(Event event);

    static void run();

    static void key_callback(struct GLFWwindow *window, int key, int scancode, int action, int mods);

};


#endif //CYCLOMETERCONTROLLER_INPUTCONTROLLER_H
