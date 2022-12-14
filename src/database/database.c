//
// Created by thgir on 02/12/2022.
//

#include "database.h"
#include <stdio.h>
#include <string.h>

typedef struct {
    database *db;
    car_t car;
    char departure_timestamp[10];
    int gate_idx;
} thread_register_args;

void db_init(database *db) {
    int mutex_init = pthread_mutex_init(&db->mutex, NULL);
    if (mutex_init != 0) {
        fprintf(stderr, "Erreur initialisation mutex db");
        exit(1);
    }
    int res;
    res = sqlite3_open("db.sqlite3", &db->db);
    if (res) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db->db));
        sqlite3_close(db->db);
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
                  "    gate          INTEGER not null,"
                  "    arrival       TEXT    not null,"
                  "    departure     TEXT,"
                  "    constraint type_check_1"
                  "        check (type >= 0),"
                  "    constraint type_check_2"
                  "        check (type < 6)"
                  ");"
                  "create unique index vehicle_id_uindex"
                  "    on vehicle (id);";
    sqlite3_exec(db->db, query, NULL, NULL, NULL);
}


static inline void *db_log_car_thread(void *args) {
    thread_register_args *_args = (thread_register_args *) args;
    pthread_mutex_lock(&_args->db->mutex);
    char query[400];
    sprintf(query,
            "insert into vehicle ("
            "   kilometers, nb_passengers, type,"
            "   payment_mean, gate, arrival, departure"
            ") "
            "values (%d, %d, %d, %d, \"%s\", \"%s\", \"%s\");",
            _args->car.nb_kilometers, _args->car.nb_passengers, _args->car.type, _args->gate_idx,
            payment_mean_to_str(_args->car.payment_mean), _args->car.arrival_timestamp,
            _args->departure_timestamp);
    char *z_err = NULL;
    int res = sqlite3_exec(_args->db->db,
                           query,
//                           "insert into vehicle (kilometers, nb_passengers, type, payment_mean, arrival) values (70, 1, 2, \"ELECTRONIC POLL\", \"20221202 18:51:03\");",
                           NULL, NULL, &z_err);
    if (res != SQLITE_OK) {
        fprintf(stderr, "%s\n", z_err);
        sqlite3_free(z_err);
    }
    pthread_mutex_unlock(&_args->db->mutex);
    free(args);
    return NULL;
}

void db_log_car(database *restrict db, const car_t *restrict car, char *restrict departure_timestamp, const int gate_idx) {
    /*
     * Comme l'??criture en base de donn??es est une op??ration qui peut ??tre relativement
     * lente, on fait une copie en m??moire de la voiture ?? enregistrer,
     * puis on effectue l'enregistrement de cette copie dans un thread que l'on d??tache
     * du thread principal
     */
    thread_register_args *args = malloc(sizeof(thread_register_args));
    strcpy(args->departure_timestamp, departure_timestamp);
    args->db = db;
    args->car = *car;
    args->gate_idx = gate_idx;
    pthread_t thread;
    pthread_create(&thread, NULL, db_log_car_thread, args);
    pthread_detach(thread);
}


void db_close(database *db) {
    sqlite3_close(db->db);
    pthread_mutex_destroy(&db->mutex);
}