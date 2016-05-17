//
// Created by Tristan Whitcher on 5/11/16.
//

#include <string>
#include <iostream>
#include "OutputController.h"

Cyclometer* OutputController::cyclometer;

std::atomic_bool OutputController::updateValues = {true};

std::atomic<int> OutputController::digitOne = {-1}; // left digit
std::atomic_bool OutputController::decimalOne = {false};

std::atomic<int> OutputController::digitTwo = {-1};
std::atomic_bool OutputController::decimalTwo = {false};

std::atomic<int> OutputController::digitThree = {-1};
std::atomic_bool OutputController::decimalThree = {false};

std::atomic<int> OutputController::digitFour = {-1}; // right digit
std::atomic_bool OutputController::decimalFour = {false};


OutputController::OutputController(Cyclometer *pCyclometer) {
    OutputController::cyclometer = pCyclometer;
}

void OutputController::run() {
    while(true) {

        std::string out = "";

        out += (digitOne != -1) ? std::to_string(digitOne) : "-";
        if(decimalOne)
            out += ".";

        out += (digitTwo != -1) ? std::to_string(digitTwo) : "-";
        if(decimalTwo)
            out += ".";

        out += (digitThree != -1) ? std::to_string(digitThree) : "-";
        if(decimalThree)
            out += ".";

        out += (digitFour != -1) ? std::to_string(digitFour) : "-";
        if(decimalFour)
            out += ".";

        std::cout << out << std::endl;

        sleep(1);

        if(updateValues) {
            updateDisplayValues(cyclometer->displayMode);
        }

    }
}


/**
 * Called to reset the display values
 */
void OutputController::resetDisplay() {
    decimalOne = false;
    decimalTwo = false;
    decimalThree = false;
    decimalFour = false;
    digitOne = -1;
    digitTwo = -1;
    digitThree = -1;
    digitFour = -1;
}


/**
 * Called by a different thread to update the display values based on the display mode
 */
void OutputController::updateDisplayValues(int displayMode) {
    Cyclometer* cyclometer = OutputController::cyclometer;
    switch(displayMode) {
        case 0: break;
        case 1:
            setSpeedDisplay(cyclometer);
            break;
        case 2:
            setDistanceDisplay(cyclometer);
            break;
        case 3:
            setTimeDisplay(cyclometer);
            break;
        default:
            break;
    }

    updateValues = false;
}

void OutputController::setSpeedDisplay(Cyclometer* cyclometer) {

    resetDisplay();

    Calculations* data = cyclometer->getCalculations();
    double currentSpeed = data->getCurrentSpeed();

    //std::cout << "Current Speed: " << currentSpeed << std::endl;
    if(currentSpeed >= 10) {
        int outInt = (int) currentSpeed;
        std::deque<int> digits = numToDeque(outInt);
        digitOne = digits.at(0);
        digitTwo = digits.at(1);
    } else {
        int firstDigit = (int) currentSpeed;
        int secondDigit = (int) (currentSpeed*10) % 10;
        digitOne = firstDigit;
        decimalOne = true;
        digitTwo = secondDigit;
    }


    //std::cout << data->tripDistance << " " << data->tripElapsedTime << std::endl;

    double averageSpeed = data->getAverageSpeed();

    if(data->tripElapsedTime == 0) {
        averageSpeed = 0;
    }

    //std::cout << averageSpeed << std::endl;

    if(averageSpeed >= 10) {
        int outInt = (int) averageSpeed;
        std::deque<int> digits = numToDeque(outInt);
        digitThree = digits.at(0);
        digitFour = digits.at(1);
    } else {
        int firstDigit = (int) averageSpeed;
        int secondDigit = (int) (averageSpeed*10) % 10;
        digitThree = firstDigit;
        decimalThree = true;
        digitFour = secondDigit;
    }

}

void OutputController::setDistanceDisplay(Cyclometer *pCyclometer) {
    /**
     * The cyclometer shall display distance to the nearest tenth of a measurement unit using all
     * four displays with a decimal point separating the tenths and units digits. Distance shall
     * display with leading zeros suppressed except that a 0 shall be displayed when the distance
     * is less than one measurement unit. The tenths digit shall always be displayed when
     * displaying distance.
     **/

    resetDisplay();

    double distance = pCyclometer->getCalculations()->getTripDistance();

    int km = (int) distance;
    int tenth = (int) (distance*10) % 10;
    if(distance < 1) {
        digitThree = 0;
        decimalThree = true;
        digitFour = tenth;
    } else {
        std::deque<int> digits = numToDeque(km);
        padToLength(&digits, 3, -1);
        digitOne = digits.at(0);
        digitTwo = digits.at(1);
        digitThree = digits.at(2);
        decimalThree = true;
        digitFour = tenth;
    }
}

void OutputController::setTimeDisplay(Cyclometer *pCyclometer) {
    resetDisplay();

    Calculations* data = cyclometer->getCalculations();
    int minutes = data->getMinutes();
    int seconds = data->getSeconds();

    std::deque<int> minutesDigits = numToDeque(minutes);
    padToLength(&minutesDigits, 2, 0);

    std::deque<int> secondsDigits = numToDeque(seconds);
    padToLength(&secondsDigits, 2, 0);

    digitOne = minutesDigits.at(0);
    digitTwo = minutesDigits.at(1);
    decimalTwo = true;
    digitThree = secondsDigits.at(0);
    digitFour = secondsDigits.at(1);

}

void OutputController::setSegments(int value) {

    std::deque<int> digits = numToDeque(value);
    padToLength(&digits, 4, -1);

    digitOne = digits.at(0);
    digitTwo = digits.at(1);
    digitThree = digits.at(2);
    digitFour = digits.at(3);
}

std::deque<int> OutputController::numToDeque(int value) {
    std::deque<int> digits;

    while (value > 0) {
        digits.push_back(value % 10); //push the last digit in
        value /= 10; //truncate the digit
    }

    std::reverse(digits.begin(), digits.end()); // the digits were in reverse order
    return digits;
}

void OutputController::padToLength(std::deque<int>* deque, int length, int padValue) {
    while(deque->size() != length) {
        deque->push_front(padValue);
    }
}

void OutputController::wheelLED(bool b) {

}

void OutputController::calcLED(bool toggle) {

}























