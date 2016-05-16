//
// Created by Tristan Whitcher on 3/9/16.
//

#include <iostream>
#include "states/States.h"
#include <pthread.h>
#include "ThreadUtils.h"
#include "CyclometerData.h"


Cyclometer::Cyclometer() : currentState(States::UNIT_SET) {
    enabled = true;
    pthread_mutexattr_init(&mutexAttr); //Initialize mutex attribute variable
    pthread_mutexattr_settype(&mutexAttr, PTHREAD_MUTEX_ERRORCHECK); //Set mutex attribute to error-checking type
    pthread_mutex_init(&queueMutex, &mutexAttr); //Initialize queue mutex with attributes
    cyclometerData = new CyclometerData();
}

void Cyclometer::transition(State *state) {
    this->currentState->onExit(*this);
    this->priorState = this->currentState;
    this->currentState = state;
    this->currentState->onEnter(*this);
}

void Cyclometer::queueEvent(Event event) {
    //Get mutex
    ThreadUtils::lock(&queueMutex);
    //Add event
    this->eventQueue.push(event);
    //Release mutex
    ThreadUtils::unlock(&queueMutex);
}

void Cyclometer::sendEvent() {
    //Get mutex
    ThreadUtils::lock(&queueMutex);
    //Send event if one exists
    if(this->eventQueue.size() > 0) {
        this->currentState->accept(*this, this->eventQueue.front());
        this->eventQueue.pop();
    }
    //Release mutex
    ThreadUtils::unlock(&queueMutex);
}


void Cyclometer::run() {
    this->currentState->onEnter(*this);
    while(enabled) {
        this->sendEvent();
    }
}

CyclometerData* Cyclometer::getCyclometerData() {
    return cyclometerData;
}



