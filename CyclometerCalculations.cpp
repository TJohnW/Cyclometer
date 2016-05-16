//
// Created by Tristan Whitcher on 5/15/16.
//

#include <pthread.h>
#include "CyclometerCalculations.h"
#include "ThreadUtils.h"

CyclometerCalculations::CyclometerCalculations(CyclometerData* data) : data(data) {
    pthread_mutexattr_init(&mutexAttr); //Initialize mutex attribute variable
    pthread_mutexattr_settype(&mutexAttr, PTHREAD_MUTEX_ERRORCHECK); //Set mutex attribute to error-checking type
    pthread_mutex_init(&queueMutex, &mutexAttr); //Initialize queue mutex with attributes
}

CyclometerCalculations::~CyclometerCalculations() {

}


void CyclometerCalculations::tick() {
    tripDistance = tripDistance + circumference;
    if(lastTime == 0) {
        time(&lastTime);
    } else {
        time_t presentTime;
        time(&presentTime);
        tempTime = tempTime + (presentTime - lastTime);
        lastTime = presentTime;
        tempDistance = tempDistance + circumference;
    }
}

void CyclometerCalculations::run() {
    while(true) {
        // check for queued pulses and handle them if were active

    }
}

void CyclometerCalculations::queuePulse(time_t pulse) {
    //Get mutex
    ThreadUtils::lock(&queueMutex);
    //Add event
    this->pulseQueue.push(pulse);
    //Release mutex
    ThreadUtils::unlock(&queueMutex);
}











