//
// Created by thgir on 02/12/2022.
//

#ifndef PROJET_PEAGE_TOLL_H
#define PROJET_PEAGE_TOLL_H

#include "gate.h"

#define NB_GATES 10

typedef struct {
    gate_t gates[NB_GATES];
    size_t open_gates;
} toll_t;

void toll_init(toll_t *toll);
void toll_free(toll_t *toll);
void toll_open_gate(toll_t *toll);
void toll_add_car(toll_t *toll, car_t *car);

#endif //PROJET_PEAGE_TOLL_H
