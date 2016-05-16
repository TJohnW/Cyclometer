//
// Created by Tristan Whitcher on 3/29/16.
//

#ifndef APPLICATION_SAFEOUTPUT_H
#define APPLICATION_SAFEOUTPUT_H

#include <pthread.h>
#include <string>

class ThreadUtils {
public:

    static void lock(pthread_mutex_t* mutex);

    static void unlock(pthread_mutex_t* mutex);

};


#endif //APPLICATION_SAFEOUTPUT_H
