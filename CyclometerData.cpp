//
// Created by Tristan Whitcher on 5/15/16.
//

#include <vector>
#include <deque>
#include "CyclometerData.h"
#include "OutputController.h"


void CyclometerData::fullReset() {
    OutputController::resetDisplay();
    kilometers = true;
    wheelRotating = false;
    mode = false;
    currentSpeed = 0;
    tripAverageSpeed = 0;
    tripDistance = 0;
    tripElapsedTime = 0;
    circumference = 210;
}

void CyclometerData::setSegments(int value) {

    std::deque<int> digits = numToDeque(value);
    padToLength(&digits, 4);

    OutputController::digitOne = digits.at(0);
    OutputController::digitTwo = digits.at(1);
    OutputController::digitThree = digits.at(2);
    OutputController::digitFour = digits.at(3);
}

std::deque<int> CyclometerData::numToDeque(int value) {
    std::deque<int> digits;

    while (value > 0) {
        digits.push_back(value % 10); //push the last digit in
        value /= 10; //truncate the digit
    }

    std::reverse(digits.begin(), digits.end()); // the digits were in reverse order
    return digits;
}

void CyclometerData::padToLength(std::deque<int>* deque, int length) {
    while(deque->size() != length) {
        deque->push_front(-1);
    }
}



