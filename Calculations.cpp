//
// Created by Tristan Whitcher on 5/15/16.
//

#include <pthread.h>
#include <iostream>
#include <sys/time.h>

#include "Calculations.h"
#include "OutputController.h"

Calculations::Calculations() {

}

Calculations::~Calculations() {

}


void Calculations::pulse() {
    //add a pulse to where we are in the buffer
    pulses[pulseIndex]++;

    if(shouldCalculate)
        distanceCount++;
}

void Calculations::run() {

    bool toggle = false;

    while(true) {

        timeval timeStart;
        gettimeofday(&timeStart, NULL);

        handleLEDS(toggle);
        calculate();
        toggle = !toggle;

        timeval timeStop;
        gettimeofday(&timeStart, NULL);
        long microSecDiff = timeStop.tv_usec - timeStop.tv_usec;
        usleep((useconds_t) (1000000 - microSecDiff));
    }
}


void Calculations::handleLEDS(bool toggle) {
    int countedPulses = 0;

    for(int i = 0; i < MAX_SEC_CALC; i++) {
        countedPulses += pulses[i];
    }

    if(countedPulses > 0) {
        if(mode) {
            shouldCalculate = true;
        }
        OutputController::wheelLED(toggle);
    } else if (countedPulses == 0) {
        if(mode) {
            shouldCalculate = false;
        }
        OutputController::wheelLED(false);
    }

    OutputController::calcLED(toggle);
}

void Calculations::calculate() {

    int cachedPulse = 0;

    for(int i = 0; i < MAX_SEC_CALC; i++) {
        cachedPulse += pulses[i];
    }

    pulseIndex = (pulseIndex + 1) % MAX_SEC_CALC;
    pulses[pulseIndex] = 0;


    double totalDistance = ((double) circumference * cachedPulse * 0.01) * .001;
    currentSpeed = ((totalDistance) / MAX_SEC_CALC) * 3600;

    if(shouldCalculate) {
        // add distance and time if we are currently calculating trip values
        tripElapsedTime += 1;
        cachedPulse = distanceCount;
        distanceCount = 0;
        tripDistance = tripDistance + (double) ((circumference * cachedPulse * 0.01) * 0.001);
    }

    OutputController::updateValues = true;
}

void Calculations::reset() {
    distanceCount = 0;
    shouldCalculate = false;
    pulseIndex = 0;

    for(int i = 0; i < MAX_SEC_CALC; i++) {
        pulses[i] = 0;
    }
}

void Calculations::fullReset() {
    OutputController::resetDisplay();
    shouldCalculate = false;
    kilometers = true;
    mode = false;
    currentSpeed = 0;
    tripDistance = 0;
    tripElapsedTime = 0;
    circumference = 210;
}

void Calculations::tripReset() {
    OutputController::resetDisplay();
    tripDistance = 0;
    tripElapsedTime = 0;
}

double Calculations::getAverageSpeed() {
    return (getTripDistance() / ((double) tripElapsedTime / (double)3600));
}

double Calculations::getCurrentSpeed() {
    return (currentSpeed * (kilometers ? 1 : 0.621371));
}

double Calculations::getTripDistance() {
    return (tripDistance * (kilometers ? 1 : 0.621371));
}

int Calculations::getMinutes() {
    return tripElapsedTime / 60;
}

int Calculations::getSeconds() {
    return tripElapsedTime % 60;
}





















