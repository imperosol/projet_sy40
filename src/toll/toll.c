//
// Created by thgir on 02/12/2022.
//

#include "toll.h"
#include "gate.h"
#include "../utils/symbols.h"
#include <stdlib.h>

void toll_init(toll_t *toll) {
    toll->open_gates = 0;
    for (int i = 0; i < NB_GATES; ++i) {
        init_gate(&toll->gates[i]);
    }
}

void toll_free(toll_t *toll) {
    for (int i = 0; i < toll->open_gates; ++i) {
        free_gate(&toll->gates[i]);
    }
    free(toll->gates);
}

void toll_open_gate(toll_t *toll) {
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
    size_t min_len = car_queue_len(&gate->car_queue);
    // si la voiture est considérée comme covoiturage
    // et que toutes les voies sont ouvertes,
    // elle peut emprunter la voie la plus à gauche
    int max_bound = is_carpool(car) ? 20 : 19;
    max_bound = min(toll->open_gates, max_bound);

    // on cherche la voie qui a le moins de voitures en attente
    for (int i = 1; i < max_bound; ++i) {
        size_t len = car_queue_len(&toll->gates[i].car_queue);
        if (len < min_len) {
            min_len = len;
            gate = &toll->gates[i];
        }
    }
    gate_add_car(gate, car);
}