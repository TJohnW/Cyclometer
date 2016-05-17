//
// Created by Tristan Whitcher on 5/15/16.
//

#ifndef CYCLOMETER_CYCLOMETERCALCULATIONS_H
#define CYCLOMETER_CYCLOMETERCALCULATIONS_H


#include <ctime>
#include <queue>


#define MAX_SEC_CALC (5)

class Calculations {
public:

    /**
     * When kilometers is false, all of the get operations shall return values converted into miles
     */
    std::atomic_bool kilometers = {true};

    /**
     * Indicates whether or not the wheel is rotating based on the bounds defined in the spec
     */
    std::atomic_bool wheelRotating = {false};

    /**
     * This is updated by the state machine when changing states. Represents which mode in
     * by default mode = true means AUTO MODE
     */
    std::atomic_bool mode = {false};

    std::atomic_bool shouldCalculate = {false};

    std::atomic<float> currentSpeed = {0};

    std::atomic<double> tripDistance = {0};

    std::atomic<int> tripElapsedTime = {0};

    std::atomic<int> circumference = {210};

    Calculations();
    ~Calculations();

    void fullReset();

    void tripReset();

    void run();

    void pulse();

    double getAverageSpeed();

    double getTripDistance();

    double getCurrentSpeed();

    int getMinutes();

    int getSeconds();

private:

    int pulses[MAX_SEC_CALC];

    int pulseIndex = 0;

    int distanceCount = 0;

    pthread_mutexattr_t mutexAttr; //Mutex attribute variable
    pthread_mutex_t queueMutex; //Mutex for event queue

    std::deque<time_t> pulseDeque;

    void calculate();

    void handleLEDS(bool toggle);

    void reset();

};


#endif //CYCLOMETER_CYCLOMETERCALCULATIONS_H
