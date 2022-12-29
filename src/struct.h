//
// Created by thgir on 29/12/2022.
//

#ifndef PROJET_PEAGE_STRUCT_H
#define PROJET_PEAGE_STRUCT_H

#include <pthread.h>
#include <sqlite3.h>

#define NB_GATES 1

typedef enum {
    LIGHT = 0,
    INTERMEDIATE = 1,
    TRUCK = 2,
    HEAVY_TRUCK = 3,
    MOTORCYCLE = 4
} car_type_e;

typedef enum {
    ELECTRONIC_TOLL,
    CASH
} payment_mean_e;

typedef struct {
    unsigned short nb_passengers;
    _Bool taxi;
    _Bool low_carbon;
    payment_mean_e payment_mean;
    car_type_e type;
    unsigned int nb_kilometers;
    char arrival_timestamp[10];
} car_t;


typedef struct {
    car_t **arr;
    size_t max_size;
    size_t head;
    size_t tail;
} car_queue_t;

struct simple_time_t {
    unsigned int h;
    unsigned int m;
    unsigned int s;
};
typedef struct simple_time_t toll_clock_t;


typedef struct {
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    pthread_t thread;
    car_queue_t car_queue;
    _Bool opened;
} gate_t;

typedef struct {
    sqlite3 *db;
    pthread_mutex_t mutex;
} database;

typedef struct {
    gate_t gates[NB_GATES];
    size_t open_gates;
    toll_clock_t clock;
    database log_db;
} toll_t;

#endif //PROJET_PEAGE_STRUCT_H
