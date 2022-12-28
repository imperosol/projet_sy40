//
// Created by thgir on 02/12/2022.
//

#include "database.h"
#include <sqlite3.h>
#include <stdio.h>
#include <time.h>

sqlite3 *db;

void db_init() {
    int res;
    res = sqlite3_open("db.sqlite3", &db);
    if (res) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(1);
    }
    char *query = "create table vehicle ("
                  "    id            INTEGER not null"
                  "        constraint id"
                  "            primary key autoincrement,"
                  "    kilometers    INTEGER not null,"
                  "    nb_passengers INTEGER not null,"
                  "    type          INTEGER not null,"
                  "    payment_mean  TEXT    not null,"
                  "    arrival       TEXT    not null,"
                  "    departure     TEXT,"
                  "    constraint type_check_1"
                  "        check (type > 0),"
                  "    constraint type_check_2"
                  "        check (type < 5)"
                  ");"
                  "create unique index vehicle_id_uindex"
                  "    on vehicle (id);";
    sqlite3_exec(db, query, NULL, NULL, NULL);
    sqlite3_close(db);
}


void db_car_arrival(car_t *car) {
    char query[300];
    char timestamp[40];
    time_t t = time(NULL);
    struct tm *time_tm = localtime(&t);
    strftime(timestamp, 40, "%Y%m%d %H:%M:%S", time_tm);
    sprintf(query,
            "insert into vehicle (kilometers, nb_passengers, type, payment_mean, arrival) "
            "values (%d, %d, %d, \"%s\", \"%s\");",
            car->nb_kilometers, car->nb_passengers, car->type,
            payment_mean_to_str(car->payment_mean), timestamp);
    char *z_err = 0;
    puts(query);
//    int res = sqlite3_exec(db, query, NULL, NULL, &z_err);
    int res = sqlite3_exec(db, "insert into vehicle (kilometers, nb_passengers, type, payment_mean, arrival) values (70, 1, 2, \"ELECTRONIC POLL\", \"20221202 18:51:03\");", NULL, NULL, &z_err);
    if (res != SQLITE_OK) {
        fprintf(stderr, "%s\n", z_err);
        sqlite3_free(z_err);
    }
}

void db_close() {

}