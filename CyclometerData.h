//
// Created by Tristan Whitcher on 5/15/16.
//

#ifndef CYCLOMETER_CYCLOMETERDATA_H
#define CYCLOMETER_CYCLOMETERDATA_H


#include <atomic>
#include <deque>

class CyclometerData {
public:

    /**
     * These values are all atomic because they are being read / written by potentially more than
     * one thread(s).
     */


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


    std::atomic<float> currentSpeed = {0};

    std::atomic<float> tripAverageSpeed = {0};

    std::atomic<float> tripDistance = {0};

    std::atomic<float> tripElapsedTime = {0};

    std::atomic<int> circumference = {210};

    void resetDisplay();

    void fullReset();

    void setSegments(int value);

    std::deque<int> numToDeque(int value);

    void padToLength(std::deque<int>* deque, int length);
};


#endif //CYCLOMETER_CYCLOMETERDATA_H
