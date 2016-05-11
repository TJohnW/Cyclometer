//
// Created by Tristan Whitcher on 3/9/16.
//

#ifndef CYCLOMETERCONTROLLER_INPUTCONTROLLER_H
#define CYCLOMETERCONTROLLER_INPUTCONTROLLER_H


#include "Cyclometer.h"
#include "Observer.h"

class InputController : public Observer {

    Cyclometer* cyclometer;
    bool enabled;

public:

    InputController(Cyclometer* cyclometer);

    void forwardEvent(Event event);

    void update(Event event);

    void overcurrent();

    void ir_beam();

    void button_pressed();

    void run();

};


#endif //CYCLOMETERCONTROLLER_INPUTCONTROLLER_H
