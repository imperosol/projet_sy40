#include "toll/toll.h"
#include "toll/display.h"
#include "car/car.h"
#include "utils/symbols.h"
#include "utils/random.h"
#include "struct.h"
#include <unistd.h>
#include <stdio.h>

#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
int main() {
    rnd_init();
    toll_t toll;
    toll_init(&toll);
    pthread_t fmt_thread;
    int res = pthread_create(&fmt_thread, NULL, printer, &toll);
    if (res != 0) {
        fprintf(stderr, "erreur création thread");
        exit(1);
    }
    pthread_detach(fmt_thread);
    loop {
        usleep(time_until_next_car(&toll.clock) * 10000);
        toll_add_car(&toll, new_car());
    }
    /* Comme le programme tout entier est une boucle infinie,
     * il ne peut se terminer que par un message d'interruption */
}
#pragma clang diagnostic pop
