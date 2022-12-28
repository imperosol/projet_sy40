//
// Created by thgir on 02/12/2022.
//

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "gate.h"

static void *gate_thread(void *args) {
    gate_t *gate = (gate_t *) args;
    pthread_mutex_lock(&gate->mutex);
    while (gate->opened) {
        while (car_queue_empty(&gate->car_queue)) {
            pthread_cond_wait(&gate->cond, &gate->mutex);
        }
        pthread_mutex_unlock(&gate->mutex);
        car_t *removed = gate_remove_car(gate);
        // on divise le temps d'attente réel par 10,
        // sinon la simulation traine du cul
        sleep(get_payment_duration_s(removed) / 10);
        printf("Départ d'une voiture : ");
        car_display(removed);
        free(removed);
        pthread_mutex_lock(&gate->mutex);
    }
    car_queue_trim(&gate->car_queue);
    pthread_mutex_unlock(&gate->mutex);
    return NULL;
}

void init_gate(gate_t *const gate) {
    car_queue_init(&gate->car_queue, 20);
    pthread_mutex_init(&gate->mutex, NULL);
    pthread_cond_init(&gate->cond, NULL);
    gate->opened = false;
}

void free_gate(gate_t *gate) {
    car_queue_free(&gate->car_queue);
    pthread_mutex_destroy(&gate->mutex);
    pthread_cond_destroy(&gate->cond);
    pthread_cancel(gate->thread);
}

void open_gate(gate_t *gate) {
    if (gate->opened) {
        fprintf(stderr, "Tried to open already opened door");
        return;
    }
    gate->opened = true;
    pthread_create(&gate->thread, NULL, gate_thread, gate);
    pthread_detach(gate->thread);
}

void close_gate(gate_t *gate) {
    gate->opened = false;
}

/**
 * Signale l'arrivée d'une voiture dans cette voie de péage
 * thread safe
 */
void gate_add_car(gate_t *restrict gate, car_t *restrict car) {
    pthread_mutex_lock(&gate->mutex);
    bool must_wake = car_queue_empty(&gate->car_queue);
    car_queue_push(&gate->car_queue, car);
    if (must_wake) {
        pthread_cond_signal(&gate->cond);
    }
    pthread_mutex_unlock(&gate->mutex);
}


/**
 * Retire une voiture de cette voie de péage.
 * La voiture retirée est celle en tête de la file
 */
car_t *gate_remove_car(gate_t *gate) {
    car_t *res = NULL;
    pthread_mutex_lock(&gate->mutex);
    res = car_queue_pop(&gate->car_queue);
    pthread_mutex_unlock(&gate->mutex);
    return res;
}

