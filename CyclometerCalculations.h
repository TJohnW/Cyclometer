//
// Created by Tristan Whitcher on 5/15/16.
//

#ifndef CYCLOMETER_CYCLOMETERCALCULATIONS_H
#define CYCLOMETER_CYCLOMETERCALCULATIONS_H


#include <ctime>
#include <queue>
#include "CyclometerData.h"

class CyclometerCalculations {
public:

    CyclometerCalculations(CyclometerData* data);
    ~CyclometerCalculations();

    void tick();

    void run();

    void queuePulse(time_t pulse);

    void setActive(bool active) {
        this->active = active;
    }

private:

    CyclometerData* data;

    bool active = true;

    long tripDistance = 0;

    int circumference;

    time_t lastTime = 0;
    time_t tempTime = 0;

    long tempDistance;

    pthread_mutexattr_t mutexAttr; //Mutex attribute variable
    pthread_mutex_t queueMutex; //Mutex for event queue

    std::queue<time_t> pulseQueue;
};


#endif //CYCLOMETER_CYCLOMETERCALCULATIONS_H
