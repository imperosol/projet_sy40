cmake_minimum_required(VERSION 3.16)
project(projet_peage C)

set(CMAKE_C_STANDARD 11)

add_executable(projet_peage src/main.c src/car/car.c src/car/car.h src/utils/random.c src/utils/random.h
        src/utils/symbols.h src/car/car_queue.c src/car/car_queue.h
        src/database/database.c src/database/database.h
        src/toll/toll.c src/toll/toll.h src/toll/gate.c src/toll/gate.h
        src/toll/frequentation_engine.c src/toll/frequentation_engine.h
        src/toll/display.c src/toll/display.h src/struct.h)
target_link_libraries(projet_peage -pthread -lm -lsqlite3)