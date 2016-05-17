//
// Created by Tristan Whitcher on 5/15/16.
//

#include <pthread.h>
#include <iostream>
#include <sys/time.h>

#include "Calculations.h"
#include "ThreadUtils.h"
#include "OutputController.h"

Calculations::Calculations() {
    pthread_mutexattr_init(&mutexAttr); //Initialize mutex attribute variable
    pthread_mutexattr_settype(&mutexAttr, PTHREAD_MUTEX_ERRORCHECK); //Set mutex attribute to error-checking type
    pthread_mutex_init(&queueMutex, &mutexAttr); //Initialize queue mutex with attributes
}

Calculations::~Calculations() {

}


void Calculations::pulse() {
    //Calculations* cyclometerCalculations = (Calculations*) arg;

    //update the value at the current position in the buffer
    pulses[pulseIndex]++;

    if(shouldCalculate)
        distanceCount++;

    //clear the interrupt.
    //out8(self->cmd_handle, (0b00001111));
}

void Calculations::run() {
    //try to associate our interrupt with the board...
    /*
    int interruptID = InterruptAttach(DAQ_IRQ, interruptReceived, this, sizeof(this), 0);
    if (interruptID == -1) {
        fprintf(stderr, "can't attach to IRQ %d\n", DAQ_IRQ);
        perror(NULL);
        exit(-1);
    }
     */


    bool toggle = false;

    // clear any lingering interrupts.
    //out8(cmd_handle, (0b00001111));

    char ledMask = 0;
    for(int i = 0; i < 3; i++) {
        //ledMask |= LED_MASK[i];
    }

    //out8(ledHandle, in8(ledHandle) & ~ledMask);

    //while running...
    while(true) {

        timeval timeStart;
        gettimeofday(&timeStart, NULL);

        //so long as we have gotten pulses...keep flashing the LEDs for calculating (if applicable)
        // and the calculating LED (if applicable)

        handleLEDS(toggle);
        calculate();
        toggle = !toggle;


        //periodically clear the interrupt here so it can recover if the frequency changes too quickly
        //out8(cmd_handle, (0b00001111));


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
    //std::cout << "Calculating.." << std::endl;
    //iterate over the available pulses and accumulate the total.
    unsigned int cachedPulse = 0;

    for(int i = 0; i < MAX_SEC_CALC; i++) {
        cachedPulse += pulses[i];
    }

    /* Reset the ones we visited */
    pulseIndex = (pulseIndex + 1) % MAX_SEC_CALC;
    pulses[pulseIndex] = 0;

    //calculate the distance travelled in that time and the speed based on that distance.
    double td = ((double) circumference * cachedPulse * 0.01) * .001;
    double s = ((td) / MAX_SEC_CALC) * 3600;

    currentSpeed = s;

    //if we are calculating, accrue time and distance travelled.
    if(shouldCalculate) {
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
    wheelRotating = false;
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





















