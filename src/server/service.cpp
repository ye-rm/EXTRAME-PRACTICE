//
// Created by 98770 on 2024/5/10.
//

#include "service.h"

service::service(int sub_id) {
    this->sub_id = sub_id;
    serviced = false;
    start_time = 0;
    cur_temp = DEFAULT_TARGET_TEMP;
    target_temp = DEFAULT_TARGET_TEMP;
    cur_wind_speed = DEFAULT_SPEED;
    create_time = time(nullptr);
    working_mood = COOLING_MODE;
    cur_status = WAITING;
}

int service::change_target_temp(double temp) {
    target_temp = temp;
    return 0;
}

int service::change_wind_speed(int speed) {
    cur_wind_speed = speed;
    return 0;
}

bool service::check_finished() const {
    if (working_mood==COOLING_MODE) {
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

int service::get_status() const {
    return cur_status;
}

int service::get_working_mood() const {
    return working_mood;
}

int service::get_sub_id() const {
    return sub_id;
}

int service::get_cur_wind_speed() const {
    return cur_wind_speed;
}

int service::chahge_working_mood(int mood) {
    if (mood == COOLING_MODE) {
        working_mood = COOLING_MODE;
    } else {
        working_mood = HEATING_MODE;
    }
    return mood;
}

void service::generate_detailed_record() {
    sqlite3 *db;
    char *zErrMsg = nullptr;
    int rc;
    rc = sqlite3_open("../sqlite/airconditioner.sqlite", &db);
    if (rc) {
        LOG_F(ERROR, "Can't open database: %s\n", sqlite3_errmsg(db));
        return;
    }
    char start[20];
    char create[20];
    char fan_speed[10];
    char work_mode[10];
    double fee;
    time_t now = time(nullptr);
    double diff = difftime(now, start_time);
    diff =  diff*(60.0/SECOND_PER_MINUTE);
    long duration = static_cast<long>(diff / 60);
    if (start_time == 0) {
        duration = 0;
    }
    struct tm *s = localtime(&start_time);
    struct tm *c = localtime(&create_time);
    strftime(start, 20, "%Y-%m-%d %H:%M:%S", s);
    strftime(create, 20, "%Y-%m-%d %H:%M:%S", c);
    switch (cur_wind_speed) {
        case LOW_SPEED:
            fee = (double) duration * PRICE_PER_MINUTE_AT_LOW_SPEED;
            sprintf(fan_speed, "low");
            break;
        case MEDIUM_SPEED:
            fee = (double) duration * PRICE_PER_MINUTE_AT_MEDIUM_SPEED;
            sprintf(fan_speed, "medium");
            break;
        case HIGH_SPEED:
            fee = (double) duration * PRICE_PER_MINUTE_AT_HIGH_SPEED;
            sprintf(fan_speed, "high");
            break;
    }
    if (working_mood == COOLING_MODE) {
        sprintf(work_mode, "cooling");
    } else {
        sprintf(work_mode, "heating");
    }
    char sql[512];
    sprintf(sql,
            "INSERT INTO ServiceRecords(extension_number,service_creation_time,service_start_time,service_duration,target_temperature, fan_speed, fee , mode) VALUES (%d,'%s', '%s', %ld, %f, '%s', %f,'%s');",
            sub_id, create, start, duration, target_temp, fan_speed, fee, work_mode);

    rc = sqlite3_exec(db, sql, nullptr, nullptr, &zErrMsg);
    if (rc != SQLITE_OK) {
        LOG_F(ERROR, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    sqlite3_close(db);
}

int service::start_service() {
    start_time = time(nullptr);
    serviced = true;
    cur_status = WORKING;
    return 0;
}

int service::stop_service() {
    cur_status = WAITING;
    return 0;
}

bool service::ever_serviced() const {
    return serviced;
}
