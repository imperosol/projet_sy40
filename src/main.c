#include <stdio.h>
#include <unistd.h>

#include "car/car_queue.h"
#include "car/car.h"
#include "utils/random.h"
#include "utils/symbols.h"

//void yo(car_queue_t *queue) {
//    for (int i = 0; i < queue->max_size; ++i) {
//        if (queue->arr[i] == NULL) {
//            printf("_ ; ");
//        } else {
//            printf("%p ; ", queue->arr[i]);
//        }
//    }
//    puts("");
//}

int main() {
    rnd_init();
    for (int j = 0; j < 20; j++) {
        for (int i = 0; i < 100; ++i) {
            int res = (int) rnd_normal(60.0f, 10);
            printf("%d, ", max(30, res));
        }
        puts("");
    }
//    char bar[] = "========================";
//    for (int i = 0; i < 20; ++i) {
//        bar[i] = '#';
//        printf("\33[2K\r");
//        printf("[%s]", bar);
//        fflush(stdout);
//        usleep(50000);
//    }
//    printf("\33[1A\33[2K\r\33[1A\33[2K\r\33[1A\33[2K\r\33[1A\33[2K\r");
//    fflush(stdout);
//    printf("^]")
//    car_t car = {
//            .nb_passengers = 1,
//            .low_carbon = false,
//            .payment_mean = CASH,
//            .nb_kilometers = 75,
//            .taxi = false,
//    };
//    car_queue_t queue;
//    car_queue_init(&queue, 5);
//    yo(&queue);
//    for (int i = 0; i < 30; ++i) {
//        car_queue_push(&queue, &car);
//        yo(&queue);
//    }
    return 0;
}
