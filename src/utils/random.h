//
// Created by thgir on 27/11/2022.
//

#ifndef PROJET_PEAGE_RANDOM_H
#define PROJET_PEAGE_RANDOM_H

void rnd_init();
float rnd_exponential(float expectancy);
float rnd_uniform(float a, float b);
int rnd_uniform_i(int a, int b);
float rnd_normal(float expectancy, float variance);
_Bool rnd_bernoulli(float expectancy);
unsigned int rnd_geometric(float expectancy);

#endif //PROJET_PEAGE_RANDOM_H
