//
// Created by thgir on 27/11/2022.
//

#include "random.h"
#include "symbols.h"
#include <time.h>
#include <stdlib.h>
#include <math.h>

void rnd_init() {
    srand(time(NULL));
}

float rnd_uniform(const float a, const float b) {
    const float rnd = ((float) rand() / (float) (RAND_MAX));
    return a + (b - a) * rnd;
}

int rnd_uniform_i(const int a, const int b) {
    const int rnd = rand() % (b - a);
    return a + rnd;
}

float rnd_exponential(const float expectancy) {
    const float t = rnd_uniform(0, 1);
    return -expectancy * logf(1 - t);
}

float rnd_normal(const float expectancy, const float variance) {
    const float a = rnd_uniform(0, 1);
    const float b = rnd_uniform(0, 1);
    const float rnd = sqrtf(-2.0f * logf(a)) * cosf(2.0f * (float) M_PI * b);
    return expectancy + rnd * variance;
}

_Bool rnd_bernoulli(const float expectancy) {
    const float rnd = rnd_uniform(0, 1);
    return expectancy > rnd;
}

unsigned int rnd_geometric(const float expectancy) {
    unsigned int res = 0;
    while (expectancy > rnd_uniform(0, 1)) {
        res++;
    }
    return res;
}