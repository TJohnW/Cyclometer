//
// Created by Tristan Whitcher on 3/9/16.
//

#ifndef CYCLOMETERCONTROLLER_CYCLOMETER_H
#define CYCLOMETERCONTROLLER_CYCLOMETER_H


#include <queue>
#include <pthread.h>
#include "Event.h"

class State;
class Cyclometer {

    bool enabled;

    State* currentState;

    std::queue<Event> eventQueue;

    void sendEvent();

    pthread_mutexattr_t mutexAttr; //Mutex attribute variable
    pthread_mutex_t queueMutex; //Mutex for event queue

public:

    //static void* run(void *cyclometer);

    Cyclometer();

    void transition(State* state);

    void queueEvent(Event event);

    void run();
};


#endif //CYCLOMETERCONTROLLER_CYCLOMETER_H
