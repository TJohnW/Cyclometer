//
// Created by Tristan Whitcher on 3/9/16.
//

#include <pthread.h>
#include <iostream>
#include "Application.h"
#include "Cyclometer.h"

bool Application::SIMULATION = false;
Application::Application(bool simulation) {
	SIMULATION = simulation;
    cyclometer = new Cyclometer();
    inputController = new InputController(cyclometer);
    outputController = new OutputController(cyclometer);
}

