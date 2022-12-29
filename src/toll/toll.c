//
// Created by thgir on 02/12/2022.
//

#include "toll.h"
#include "gate.h"
#include "../car/car_queue.h"
#include "../utils/symbols.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

void toll_init(toll_t *toll) {
    toll->open_gates = 0;
    for (int i = 0; i < NB_GATES; ++i) {
        init_gate(&toll->gates[i], toll);
        toll->gates[i].id = i + 1;
    }
    toll->clock.h = 7;
    toll->clock.m = 30;
    toll->clock.s = 0;
    pthread_mutex_init(&toll->clock.mutex, NULL);
    db_init(&toll->log_db);
}

void toll_free(toll_t *toll) {
    for (int i = 0; i < toll->open_gates; ++i) {
        free_gate(&toll->gates[i]);
    }
    free(toll->gates);
    pthread_mutex_destroy(&toll->clock.mutex);
}

void toll_open_gate(toll_t *toll) {
    assert(toll->open_gates < NB_GATES);
    size_t i = toll->open_gates;
    open_gate(&toll->gates[i]);
    toll->open_gates += 1;
}

void toll_close_gate(toll_t *toll) {
    if (toll->open_gates == 0) {
        return;
    }
    toll->open_gates--;
    close_gate(&toll->gates[toll->open_gates]);
}

void toll_add_car(toll_t *toll, car_t *car) {
    if (toll->open_gates == 0) {
        toll_open_gate(toll);
    }
    gate_t *gate = &toll->gates[0];
    pthread_mutex_lock(&gate->mutex);
    size_t min_len = car_queue_len(&gate->car_queue);
    pthread_mutex_unlock(&gate->mutex);
    size_t max_len = min_len;
    // si la voiture est considérée comme covoiturage
    // et que toutes les voies sont ouvertes,
    // elle peut emprunter la voie la plus à gauche
    int max_bound = is_carpool(car) ? NB_GATES : (NB_GATES - 1);
    max_bound = min(toll->open_gates, max_bound);

    // on cherche la voie qui a le moins de voitures en attente
    for (int i = 1; i < max_bound; ++i) {
        pthread_mutex_lock(&toll->gates[i].mutex);
        size_t len = car_queue_len(&toll->gates[i].car_queue);
        pthread_mutex_unlock(&toll->gates[i].mutex);
        if (len < min_len) {
            min_len = len;
            gate = &toll->gates[i];
        }
        max_len = max(len, max_len);
    }

    if ((max_len == 0) and (toll->open_gates > 1)) {
        // si plusieurs portes sont ouvertes et qu'il n'y a pas de queue
        // à l'une d'entre elles, on ferme une porte
        toll_close_gate(toll);
        toll_add_car(toll, car);
        return;
    }

    if ((min_len >= 5) and (toll->open_gates < NB_GATES)) {
        // quand les portes commencent à s'engorger,
        // on en ouvre une nouvelle
        toll_open_gate(toll);
        if (toll->open_gates != NB_GATES or is_carpool(car)) {
            gate = &toll->gates[toll->open_gates - 1];
        }
    }
    pthread_mutex_lock(&toll->clock.mutex);
    sprintf(car->arrival_timestamp,
            "%02dH%02dm%02d",
            toll->clock.h, toll->clock.m, toll->clock.s);
    pthread_mutex_unlock(&toll->clock.mutex);
    gate_add_car(gate, car);
}