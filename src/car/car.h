//
// Created by thgir on 27/11/2022.
//

#ifndef PROJET_PEAGE_CAR_H
#define PROJET_PEAGE_CAR_H

#include <stdbool.h>

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
    bool taxi;
    bool low_carbon;
    payment_mean_e payment_mean;
    car_type_e type;
    unsigned int nb_kilometers;
} car_t;

char *payment_mean_to_str(payment_mean_e payment_mean);
/**
 * @example @code
 * #include <assert.h>
 * @endcode
 * @param car
 * @return
 */
bool is_carpool(car_t *car);
unsigned int get_payment_duration_s(car_t *car);
float car_get_fee(car_t *car);
car_t *new_car();
void car_display(car_t *car);


#endif //PROJET_PEAGE_CAR_H
