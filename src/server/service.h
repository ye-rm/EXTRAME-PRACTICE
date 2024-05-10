//
// Created by 98770 on 2024/5/10.
//

#ifndef EXTRAME_PRACTICE_SERVICE_H
#define EXTRAME_PRACTICE_SERVICE_H
#define DEFAULT_TARGET_TEMP 27
#define DEFAULT_WIND_SPEED 1
#define FREE 0
#define WORKING 1
#include <ctime>

class service{
private:
    int sub_id;
    int cur_temp;
    int target_temp;
    int cur_wind_speed;
    bool cooling;
    int cur_status;
    time_t create_time;
    time_t start_time;
public:
    service(int sub_id);
    ~service();
    int get_status();
    int get_power();
    bool check_finished();
    int get_sub_id();
    int update_cur_temp(int temp);
    int get_cur_wind_speed();
    int change_wind_speed(int speed);
    int change_target_temp(int temp);
    void generate_detailed_record();
};

#endif //EXTRAME_PRACTICE_SERVICE_H
