#include "toll/toll.h"
#include "car/car.h"
#include "car/car_queue.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main() {
    toll_t toll;
    toll_init(&toll);
    toll_open_gate(&toll);
    toll_open_gate(&toll);
    for (int i = 0; i < 30; ++i) {
        toll_add_car(&toll, new_car());
        sleep(2);
    }
    toll_free(&toll);
    return 0;
}
