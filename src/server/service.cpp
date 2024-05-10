//
// Created by 98770 on 2024/5/10.
//

#include "service.h"

service::service(int sub_id) {
    this->sub_id = sub_id;
    cur_temp = DEFAULT_TARGET_TEMP;
    target_temp = DEFAULT_TARGET_TEMP;
    cur_wind_speed = DEFAULT_WIND_SPEED;
    create_time = time(nullptr);
    cooling = true;
    cur_status = FREE;
}

int service::change_target_temp(int temp) {
    target_temp = temp;
    return 0;
}

int service::change_wind_speed(int speed) {
    cur_wind_speed = speed;
    return 0;
}

bool service::check_finished() {
    if (cooling) {
        if (cur_temp <= target_temp) {
            return true;
        } else {
            return false;
        }
    } else {
        if (cur_temp >= target_temp) {
            return true;
        } else {
            return false;
        }
    }
}

int service::update_cur_temp(int temp) {
    cur_temp = temp;
    return 0;
}

service::~service() {
}
