//
// Created by Tristan Whitcher on 5/11/16.
//

#ifndef CYCLOMETER_OUTPUTCONTROLLER_H
#define CYCLOMETER_OUTPUTCONTROLLER_H


#include "Cyclometer.h"

class OutputController {

    static Cyclometer* cyclometer;

public:

    static std::atomic<int> digitOne; // left digit
    static std::atomic_bool decimalOne;

    static std::atomic<int> digitTwo;
    static std::atomic_bool decimalTwo;

    static std::atomic<int> digitThree;
    static std::atomic_bool decimalThree;

    static std::atomic<int> digitFour; // right digit
    static std::atomic_bool decimalFour;


    OutputController(Cyclometer *pCyclometer);

    void run();

    static void updateDisplayValues(int displayMode);

    static void resetDisplay();

    static void setSpeedDisplay(Cyclometer* cyclometer);

    static void setTimeDisplay(Cyclometer *pCyclometer);

    static void setDistanceDisplay(Cyclometer *pCyclometer);
};


#endif //CYCLOMETER_OUTPUTCONTROLLER_H
