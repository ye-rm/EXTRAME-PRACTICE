//
// Created by 98770 on 2024/5/10.
//

#ifndef EXTRAME_PRACTICE_SERVICE_H
#define EXTRAME_PRACTICE_SERVICE_H
#define DEFAULT_TARGET_TEMP 27
#define DEFAULT_WIND_SPEED 2
#define FREE 0
#define WORKING 1
#define HIGH 3
#define MEDIUM 2
#define LOW 1

#include <ctime>
#include <string>
#include "../../lib/loguru/loguru.hpp"
#include "../../sqlite/sqlite3.h"

class service {
private:
    int sub_id;
    double cur_temp;
    double target_temp;
    int cur_wind_speed;
    bool cooling;
    int cur_status;
    time_t create_time;
    time_t start_time;
public:
    service(int sub_id);

    ~service();

    int get_status();

    int start_service();

    int stop_service();

    int get_power();

    bool check_finished();

    int get_sub_id();

    int update_cur_temp(double temp);

    int get_cur_wind_speed();

    int chahge_working_mood(int mood);

    int change_wind_speed(int speed);

    int change_target_temp(double temp);

    void generate_detailed_record();
};

#endif //EXTRAME_PRACTICE_SERVICE_H
