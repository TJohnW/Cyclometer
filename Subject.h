//
// Created by Tristan Whitcher on 3/10/16.
//

#ifndef CYCLOMETERCONTROLLER_SUBJECT_H
#define CYCLOMETERCONTROLLER_SUBJECT_H


#include <vector>
#include "Event.h"
#include "Observer.h"

class Subject {

    std::vector<Observer*> observers;

public:
    void attach(Observer* observer);
    void notifyObservers(Event event);
    void detach(Observer* observer);
};


#endif //CYCLOMETERCONTROLLER_SUBJECT_H
