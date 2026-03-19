#ifndef PARKING_MANAGER_H
#define PARKING_MANAGER_H
#define TOTAL_SLOTS 10
void init_parking();
void park_car(char car_no[]);
void remove_car(char car_no[]);
void start_threads();
void view_status();
#endif
