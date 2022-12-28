//
// Created by thgir on 02/12/2022.
//

#ifndef PROJET_PEAGE_DATABASE_H
#define PROJET_PEAGE_DATABASE_H

#include <stdlib.h>
#include "../car/car.h"

void db_init();
void db_car_arrival(car_t *car);
void db_close();

#endif //PROJET_PEAGE_DATABASE_H
