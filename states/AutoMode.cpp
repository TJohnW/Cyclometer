//
// Created by Tristan Whitcher on 3/10/16.
//

#include <iostream>
#include "AutoMode.h"
#include "States.h"
#include "../ThreadUtils.h"

void AutoMode::onEnter(Cyclometer &cyclometer) {
}

void AutoMode::accept(Cyclometer &cyclometer, Event event) {
    switch(event) {
        default:
            break;
    }
}

void AutoMode::onExit(Cyclometer &cyclometer) {

}
