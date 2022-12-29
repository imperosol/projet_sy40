//
// Created by thgir on 02/12/2022.
//

#ifndef PROJET_PEAGE_DATABASE_H
#define PROJET_PEAGE_DATABASE_H

#include <stdlib.h>

#include "../car/car.h"
#include "../toll/frequentation_engine.h"
#include "../struct.h"


void db_init(database *db);
void db_log_car(database *restrict db, const car_t *restrict car, char *restrict departure_timestamp, int gate_idx);
void db_close(database *db);

#endif //PROJET_PEAGE_DATABASE_H
