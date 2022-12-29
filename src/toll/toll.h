//
// Created by thgir on 02/12/2022.
//

#ifndef PROJET_PEAGE_TOLL_H
#define PROJET_PEAGE_TOLL_H

#include "../database/database.h"
#include "../struct.h"

void toll_init(toll_t *toll);
void toll_free(toll_t *toll);
void toll_open_gate(toll_t *toll);
void toll_add_car(toll_t *toll, car_t *car);

#endif //PROJET_PEAGE_TOLL_H
