//
// Created by thgir on 27/11/2022.
//

#include <stdlib.h>
#include <string.h>
#include "car_queue.h"
#include "../utils/symbols.h"

#define index_increment(idx, max) if(++idx == max) idx = 0
#define index_decrement(idx, max) idx = idx == 0 ? max - 1 : 0;


void car_queue_init(car_queue_t *const queue, const size_t size) {
    queue->arr = calloc(size, sizeof(car_t *));
    queue->max_size = size;
    queue->tail = 0;
    queue->head = 0;
}

void car_queue_free(car_queue_t *queue) {
    free(queue->arr);
}

_Bool car_queue_empty(const car_queue_t *const queue) {
    return queue->arr[queue->tail] == NULL;
}

size_t car_queue_len(const car_queue_t *const queue) {
    if (queue->arr[queue->head] == NULL) {
        return 0;
    } else if (queue->tail > queue->head) {
        return queue->tail - queue->head + 1;
    } else {
        return queue->max_size - queue->tail + queue->head + 1;
    }
}

car_t *car_queue_pop(car_queue_t *const queue) {
    if (car_queue_empty(queue)) {
        return NULL;
    }
    car_t *res = queue->arr[queue->tail];
    queue->arr[queue->tail] = NULL;
    if (queue->head != queue->tail) {
        index_increment(queue->tail, queue->max_size);
    }
    return res;
}

void car_queue_push(car_queue_t *restrict const queue, car_t *restrict const car) {
    if (queue->arr[queue->tail] != NULL) {  // the queue isn't empty
        index_increment(queue->head, queue->max_size);
        if (queue->tail == queue->head) {  // the queue is full
            index_decrement(queue->head, queue->max_size);
            car_queue_extend(queue);
            index_increment(queue->head, queue->max_size);
        }
    }
    queue->arr[queue->head] = car;
}

void car_queue_extend(car_queue_t *const queue) {
    size_t new_size = queue->max_size + queue->max_size / 2 + 1;
    queue->arr = realloc(queue->arr, new_size * sizeof(car_t *));
    if (queue->tail > queue->head) {
        // configuration like [4, 5, _, _, _, 1, 2, 3]
        // need to be converted to smth like [4, 5, _, _, _, _, _, _, 1, 2, 3]
        size_t move_size = (queue->max_size - queue->tail) * sizeof(car_t *); // size of the chunk of memory to move
        size_t diff_size = (new_size - queue->max_size) * sizeof(car_t *); // size of memory added
        void *old_tail = queue->arr + queue->tail;
        void *new_tail = old_tail + diff_size;
        memmove(new_tail, old_tail, move_size);
        memset(old_tail, 0, diff_size);
        queue->tail += new_size - queue->max_size;
    }
    queue->max_size = new_size;
}

void car_queue_trim(car_queue_t *const queue) {
    const size_t new_size = car_queue_len(queue);
    u_int8_t buf[new_size * sizeof(car_t *)];
    if (queue->tail > queue->head) {
        memcpy(buf, queue->arr, queue->head * sizeof(car_t *));
        memcpy(buf + queue->head, queue->arr + queue->tail, (queue->max_size - queue->tail) * sizeof(car_t *));
    } else {
        memcpy(buf, queue->arr + queue->head, new_size * sizeof(car_t *));
    }
    queue->arr = realloc(queue->arr, new_size * sizeof(car_t *));
    memcpy(queue->arr, buf, new_size * sizeof(car_t *));
    queue->head = 0;
    queue->tail = new_size - 1;
    queue->max_size = new_size;
}


