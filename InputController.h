//
// Created by Tristan Whitcher on 3/9/16.
//

#ifndef GARAGECONTROLLER_INPUTCONTROLLER_H
#define GARAGECONTROLLER_INPUTCONTROLLER_H


#include "CyclometerLaunch.h"

class InputController : public Observer {

    Cyclometer* garage;
    bool enabled;

public:

    InputController(Cyclometer* garage);

    void forwardEvent(Event event);

    void update(Event event);

    void overcurrent();

    void ir_beam();

    void button_pressed();

    void run();

};


#endif //GARAGECONTROLLER_INPUTCONTROLLER_H
