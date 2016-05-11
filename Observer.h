//
// Created by Tristan Whitcher on 3/10/16.
//

#ifndef CYCLOMETERCONTROLLER_OBSERVER_H
#define CYCLOMETERCONTROLLER_OBSERVER_H


#include "Event.h"

class Observer {
public:
    virtual void update(Event event) = 0;
};


#endif //CYCLOMETERCONTROLLER_OBSERVER_H
