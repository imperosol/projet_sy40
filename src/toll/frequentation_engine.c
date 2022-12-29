//
// Created by thgir on 28/12/2022.
//

#include <assert.h>
#include "frequentation_engine.h"
#include "../utils/random.h"

static inline float get_expectancy(const toll_clock_t *const clock) {
    assert(clock->h < 24);
    const static float lookup[] = {
            80.0f, 100.0f, 110.0f, 80.0f, 80.0f, 70.0f,
            30.0f, 15.0f, 5.0f, 7.0f, 20.0f, 25.0f,
            25.0f, 30.0f, 35.0f, 25.0f, 10.0f, 4.0f,
            10.0f, 30.0f, 40.0f, 50.0f, 60.0f, 70.0f
    };
    return lookup[clock->h];
}

static inline void readjust_clock(toll_clock_t *const clock) {
    if (clock->s > 59) {
        clock->m += clock->s / 60;
        clock->s %= 60;
    }
    if (clock->m > 59) {
        clock->h += clock->m / 60;
        clock->m %= 60;
    }
    if (clock->h > 24) {
        clock->h %= 24;
    }
}

unsigned long time_until_next_car(toll_clock_t *const clock) {
    const float expectancy = get_expectancy(clock);
    const unsigned long seconds = (unsigned long) rnd_exponential(expectancy);
//    pthread_mutex_lock(&clock->mutex);
    clock->s += seconds;
    readjust_clock(clock);
//    pthread_mutex_unlock(&clock->mutex);
    return seconds;
}