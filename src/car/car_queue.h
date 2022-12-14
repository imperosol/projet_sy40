//
// Created by thgir on 27/11/2022.
//

#ifndef PROJET_PEAGE_CAR_QUEUE_H
#define PROJET_PEAGE_CAR_QUEUE_H

#include <stddef.h>
#include "car.h"

void car_queue_init(car_queue_t *queue, size_t size);
void car_queue_free(car_queue_t *queue);
size_t car_queue_len(const car_queue_t *queue);
_Bool car_queue_empty(const car_queue_t *queue);
car_t *car_queue_pop(car_queue_t *queue);
void car_queue_push(car_queue_t *restrict queue, car_t *restrict car);
void car_queue_extend(car_queue_t *queue);
void car_queue_trim(car_queue_t *queue);

typedef struct {
    size_t size;
    car_t **arr;
} car_vec_t;
car_vec_t car_queue_to_vec(car_queue_t *queue);

#endif //PROJET_PEAGE_CAR_QUEUE_H
