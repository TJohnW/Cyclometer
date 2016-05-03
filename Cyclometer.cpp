//
// Created by Tristan Whitcher on 3/9/16.
//

#include <iostream>
#include "CyclometerLaunch.h"
#include "States.h"
#include <pthread.h>
#include "SafeOutput.h"


Cyclometer::Cyclometer() : currentState(States::AUTO_MODE) {
    enabled = true;
    pthread_mutexattr_init(&mutexAttr); //Initialize mutex attribute variable
    pthread_mutexattr_settype(&mutexAttr, PTHREAD_MUTEX_ERRORCHECK); //Set mutex attribute to error-checking type
    pthread_mutex_init(&queueMutex, &mutexAttr); //Initialize queue mutex with attributes
}

void Cyclometer::transition(State *state) {
    this->currentState->onExit(*this);
    this->currentState = state;
    this->currentState->onEnter(*this);
}


Motor* Cyclometer::getMotor() {
    return &motor;
}

void Cyclometer::queueEvent(Event event) {
    //Get mutex
    SafeOutput::lock(&queueMutex);
    //Add event
    this->eventQueue.push(event);
    //Release mutex
    SafeOutput::unlock(&queueMutex);
}

void Cyclometer::sendEvent() {
    //Get mutex
    SafeOutput::lock(&queueMutex);
    //Send event if one exists
    if(this->eventQueue.size() > 0) {
        this->currentState->accept(*this, this->eventQueue.front());
        this->eventQueue.pop();
    }
    //Release mutex
    SafeOutput::unlock(&queueMutex);
}


void Cyclometer::run() {
    this->currentState->onEnter(*this);
    while(enabled) {
        this->sendEvent();
    }
}

