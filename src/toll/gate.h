//
// Created by thgir on 02/12/2022.
//

#ifndef PROJET_PEAGE_GATE_H
#define PROJET_PEAGE_GATE_H

#include "../struct.h"

void init_gate(gate_t *restrict gate, toll_t *restrict toll);
void open_gate(gate_t *gate);
void close_gate(gate_t *gate);
void free_gate(gate_t *gate);
void gate_add_car(gate_t *gate, car_t *car);

#endif //PROJET_PEAGE_GATE_H
