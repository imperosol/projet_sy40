cmake_minimum_required(VERSION 3.16)
project(projet_peage C)

set(CMAKE_C_STANDARD 11)

add_executable(projet_peage src/main.c src/car/car.c src/car/car.h src/utils/random.c src/utils/random.h src/utils/symbols.h src/car/car_queue.c src/car/car_queue.h src/utils/concurrent.c src/utils/concurrent.h)
target_link_libraries(projet_peage -pthread -lm)