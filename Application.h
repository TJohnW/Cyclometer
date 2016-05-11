//
// Created by Tristan Whitcher on 3/9/16.
//

#ifndef CYCLOMETERCONTROLLER_CYCLOMETERCONTROLLER_H
#define CYCLOMETERCONTROLLER_CYCLOMETERCONTROLLER_H


#include "InputController.h"
#include "Cyclometer.h"
#include "OutputController.h"

class Application {
public:

	static bool SIMULATION;

    Cyclometer* cyclometer;
    InputController* inputController;
	OutputController* outputController;

    Application(bool simulation);
};


#endif //CYCLOMETERCONTROLLER_CYCLOMETERCONTROLLER_H
