//
// Created by thgir on 27/11/2022.
//

#ifndef PROJET_PEAGE_CONCURRENT_H
#define PROJET_PEAGE_CONCURRENT_H

#include <pthread.h>
#include <stdio.h>

#define MUTEX(mutex, function) \
    pthread_mutex_lock(mutex);     \
    function;                      \
    pthread_mutex_unlock(mutex)

#endif //PROJET_PEAGE_CONCURRENT_H
