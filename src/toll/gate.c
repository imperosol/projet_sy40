//
// Created by thgir on 02/12/2022.
//

#include <unistd.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <pthread.h>
#include "gate.h"
#include "../car/car_queue.h"
#include "../utils/symbols.h"
#include "../database/database.h"

typedef struct {
    gate_t *gate;
    toll_t *toll;
} thread_args;

_Noreturn static void *gate_thread(void *args) {
    thread_args *_args = (thread_args *) args;
    gate_t *gate = _args->gate;
    toll_t *toll = _args->toll;
    free_gate(args);
    pthread_mutex_lock(&gate->mutex);
    loop {
        while (car_queue_empty(&gate->car_queue)) {
            pthread_cond_wait(&gate->cond, &gate->mutex);
        }
        car_t *next = car_queue_pop(&gate->car_queue);
        pthread_mutex_unlock(&gate->mutex);
        // on divise le temps d'attente réel par 10,
        // sinon la simulation traine du cul
        usleep(get_payment_duration_s(next) * 10000);
        char departure_timestamp[10];
        pthread_mutex_lock(&toll->clock.mutex);
        sprintf(departure_timestamp,
                "%02dH%02dm%02ds",
                toll->clock.h, toll->clock.m, toll->clock.s);
        pthread_mutex_unlock(&toll->clock.mutex);
        db_log_car(&toll->log_db, next, departure_timestamp, gate->id);
        free(next);
        pthread_mutex_lock(&gate->mutex);
    }
}

void init_gate(gate_t *restrict gate, toll_t *restrict toll) {
    car_queue_init(&gate->car_queue, 20);
    pthread_mutex_init(&gate->mutex, NULL);
    pthread_cond_init(&gate->cond, NULL);
    gate->opened = false;
    thread_args *args = malloc(sizeof(thread_args));
    args->toll = toll;
    args->gate = gate;
    pthread_create(&gate->thread, NULL, gate_thread, args);
    pthread_detach(gate->thread);
}

void free_gate(gate_t *gate) {
    car_queue_free(&gate->car_queue);
    pthread_mutex_destroy(&gate->mutex);
    pthread_cond_destroy(&gate->cond);
    pthread_cancel(gate->thread);
}

void open_gate(gate_t *gate) {
    assert(!gate->opened);
    gate->opened = true;
}

void close_gate(gate_t *gate) {
    assert(gate->opened);
    gate->opened = false;
}

/**
 * Signale l'arrivée d'une voiture dans cette voie de péage
 * Locks the mutex of the gate
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

