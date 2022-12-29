//
// Created by thgir on 27/11/2022.
//

#include <stdlib.h>
#include <stdio.h>
#include "car.h"
#include "../utils/symbols.h"
#include "../utils/random.h"

char *payment_mean_to_str(payment_mean_e payment_mean) {
    static char *electronic_poll = "ELECTRONIC POLL";
    static char *cash = "CASH";
    if (payment_mean == ELECTRONIC_TOLL) {
        return electronic_poll;
    } else {
        return cash;
    }
}

void car_display(car_t *car) {
    printf("{%d; %d; %d}\n", car->type, car->nb_passengers, car->nb_kilometers);
}

bool is_carpool(car_t *car) {
    return car->nb_passengers > 1
           or car->taxi
           or car->low_carbon;
}

unsigned int get_payment_duration_s(car_t *car) {
    int seconds = (int) rnd_normal(60, 10);
    seconds = max(30, seconds);
    if (car->payment_mean == ELECTRONIC_TOLL) {
        seconds /= 2;
    }
    return (unsigned int) seconds;
}

float car_get_fee(car_t *car) {
    static float lookup[] = {
            0.066f, 0.1f, 0.1648f, 0.219f, 0.0402f
    };
    return lookup[car->type] * (float) car->nb_kilometers;
}

car_t *new_car() {
    car_t *car = malloc(sizeof(car_t));
    // on considère que 85% des véhicules sont de classe 1, 10% de classe 2, 4% de classe 3 et 1% de classe 4
    int rnd = rnd_uniform_i(0, 100);
    if (rnd < 80) {
        car->type = LIGHT;
    } else if (rnd < 85) {
        car->type = INTERMEDIATE;
    } else if (rnd < 95) {
        car->type = TRUCK;
    } else if (rnd < 99) {
        car->type = HEAVY_TRUCK;
    } else {
        car->type = MOTORCYCLE;
    }

    if (car->type == LIGHT) {
        // on considère le nombre de passagers en plus du conducteur
        // est décrit par une loi géométrique d'espérance 1/2
        car->nb_passengers = 1 + rnd_geometric(0.5f);
        car->nb_passengers = min(8, car->nb_passengers);
        // 1% des véhicules ont la vignette crit'air E
        car->low_carbon = rnd_bernoulli(0.01f);
    } else {
        car->nb_passengers = 1;
        car->low_carbon = false;
        car->taxi = false;
    }

    if (car->type == LIGHT or car->type == MOTORCYCLE) {
        car->nb_kilometers = (int) rnd_normal(60.0f, 10);
        // 52% des voitures paient par télépéage
        car->payment_mean = rnd_bernoulli(0.52f) ? ELECTRONIC_TOLL : CASH;
    } else {
        car->nb_kilometers = (int) rnd_normal(76.2f, 10);
        // 94% des poids lourds paient par télépéage
        car->payment_mean = rnd_bernoulli(0.94f) ? ELECTRONIC_TOLL : CASH;
    }
    car->nb_kilometers = max(30, car->nb_kilometers);
    return car;
}