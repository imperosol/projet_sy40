//
// Created by thgir on 28/12/2022.
//

#include "display.h"
#include "toll.h"
#include "../utils/symbols.h"
#include "../struct.h"
#include "../car/car_queue.h"
#include <unistd.h>
#include <stdio.h>


_Noreturn void *printer(void *args) {
    toll_t *toll = (toll_t *) args;
    loop {
        sleep(1);
        pthread_mutex_lock(&toll->clock.mutex);
        printf("\n%dH%d\n", toll->clock.h, toll->clock.m);
        pthread_mutex_unlock(&toll->clock.mutex);
        for (int i = 0; i < NB_GATES; ++i) {
            gate_t *gate = &toll->gates[i];
            pthread_mutex_lock(&gate->mutex);
            printf("%d | ", i);
            if (gate->opened) {
                car_vec_t vec = car_queue_to_vec(&gate->car_queue);
                for (int j = 0; j < vec.size; ++j) {
                    printf("%d ", vec.arr[j]->type);
                }
                printf("\n");
            } else {
                printf("X\n");
            }
            pthread_mutex_unlock(&gate->mutex);
        }
    }
}