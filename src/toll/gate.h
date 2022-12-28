//
// Created by thgir on 02/12/2022.
//

#ifndef PROJET_PEAGE_GATE_H
#define PROJET_PEAGE_GATE_H

#include <pthread.h>
#include "../car/car_queue.h"

typedef struct {
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    pthread_t thread;
    car_queue_t car_queue;
    bool opened;
} gate_t;

void init_gate(gate_t *gate);
void open_gate(gate_t *gate);
void close_gate(gate_t *gate);
void free_gate(gate_t *gate);
void gate_add_car(gate_t *gate, car_t *car);
car_t *gate_remove_car(gate_t *gate);

#endif //PROJET_PEAGE_GATE_H
