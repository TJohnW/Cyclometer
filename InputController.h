//
// Created by Tristan Whitcher on 3/9/16.
//

#ifndef CYCLOMETERCONTROLLER_INPUTCONTROLLER_H
#define CYCLOMETERCONTROLLER_INPUTCONTROLLER_H


#include <GLFW/glfw3.h>
#include "Cyclometer.h"
#include "CyclometerCalculations.h"

class InputController {

    static Cyclometer* cyclometer;
    static CyclometerCalculations *calculations;
    static bool enabled;

public:

    InputController(Cyclometer *pCyclometer, CyclometerCalculations *pCalculations);

    static void forwardEvent(Event event);

    static void run();

    static void key_callback(struct GLFWwindow *window, int key, int scancode, int action, int mods);

};


#endif //CYCLOMETERCONTROLLER_INPUTCONTROLLER_H
