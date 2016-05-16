//
// Created by Tristan Whitcher on 3/9/16.
//

#ifndef CYCLOMETERCONTROLLER_CYCLOMETER_H
#define CYCLOMETERCONTROLLER_CYCLOMETER_H


#include <queue>
#include <pthread.h>
#include "Event.h"
#include "CyclometerData.h"

class State;
class Cyclometer {

    bool enabled;

    State* currentState;

    std::queue<Event> eventQueue;

    void sendEvent();

    pthread_mutexattr_t mutexAttr; //Mutex attribute variable
    pthread_mutex_t queueMutex; //Mutex for event queue

    CyclometerData* cyclometerData;

    /**
     * Display modes:
     * 0: in configuration
     * 1: Current speed and Average speed
     * 2: Distance
     * 3: elapsed time
     */
    int displayMode = 0;

public:

    //static void* run(void *cyclometer);

    Cyclometer();

    void transition(State* state);

    void queueEvent(Event event);

    void run();

    CyclometerData* getCyclometerData();

    State *priorState;
};


#endif //CYCLOMETERCONTROLLER_CYCLOMETER_H
