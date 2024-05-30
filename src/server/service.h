//
// Created by yewenyu on 2024/5/10. the service class of airconditioner
//

#ifndef EXTRAME_PRACTICE_SERVICE_H
#define EXTRAME_PRACTICE_SERVICE_H

#include <ctime>
#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>
#include "../../loguru.hpp"
#include "../../sqlite/sqlite3.h"
#include "../common/common.h"

class service {
private:
    int sub_id;
    double cur_temp;
    double target_temp;
    int cur_wind_speed;
    int working_mood;
    bool serviced;
    int cur_status;
    time_t start_time;
    time_t end_time;
public:
    service(int sub_id);

    ~service();

    int get_status() const;

    int start_service();

    int stop_service();

    int get_working_mood() const;

    double get_cur_temp() const;

    double get_target_temp() const;

    time_t get_start_time() const;

    bool check_finished() const;

    int get_sub_id() const;

    bool ever_serviced() const;

    int update_cur_temp(double temp);

    int get_cur_wind_speed() const;

    int chahge_working_mood(int mood);

    int change_wind_speed(int speed);

    int change_target_temp(double temp);

    void generate_detailed_record();

    void update_start_time();
};

#endif //EXTRAME_PRACTICE_SERVICE_H
