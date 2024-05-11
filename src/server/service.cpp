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

int service::change_target_temp(double temp) {
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

int service::update_cur_temp(double temp) {
    cur_temp = temp;
    return 0;
}

service::~service() {
}

int service::get_status() {
    if (cur_status == FREE) {
        return FREE;
    } else {
        return WORKING;
    }
}

int service::get_sub_id() {
    return sub_id;
}

int service::get_cur_wind_speed() {
    return cur_wind_speed;
}

int service::chahge_working_mood(int mood) {
    if (mood == 1){
        cooling = true;
    }else{
        cooling = false;
    }
    return cooling;
}
