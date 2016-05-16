//
// Created by Tristan Whitcher on 3/29/16.
//

#include <iostream>
#include "ThreadUtils.h"

void ThreadUtils::lock(pthread_mutex_t *mutex) {
    int result = pthread_mutex_trylock(mutex);
    while (result != 0) {
        result = pthread_mutex_trylock(mutex);
    }
}

void ThreadUtils::unlock(pthread_mutex_t *mutex) {
    int result = pthread_mutex_unlock(mutex);
    while (result != 0) {
        result = pthread_mutex_unlock(mutex);
    }
}

