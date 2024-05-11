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
    if (mood == 1) {
        cooling = true;
    } else {
        cooling = false;
    }
    return cooling;
}

void service::generate_detailed_record() {
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    rc = sqlite3_open("../sqlite/airconditioner.sqlite", &db);
    if (rc) {
        LOG_F(ERROR, "Can't open database: %s\n", sqlite3_errmsg(db));
        return;
    }
    char start[20];
    char create[20];
    char fan_speed[10];
    time_t now = time(nullptr);
    double diff = difftime(now, start_time);
    long duration = static_cast<long>(diff/60);
    if (start_time == 0) {
        duration = 0;
    }
    struct tm *s = localtime(&start_time);
    struct tm *c = localtime(&create_time);
    strftime(start, 20, "%Y-%m-%d %H:%M:%S", s);
    strftime(create, 20, "%Y-%m-%d %H:%M:%S", c);
    switch (cur_wind_speed) {
        case 1:
            sprintf(fan_speed, "low");
            break;
        case 2:
            sprintf(fan_speed, "medium");
            break;
        case 3:
            sprintf(fan_speed, "high");
            break;
    };
    char sql[200];
    sprintf(sql,
            "INSERT INTO ServiceRecords(extension_number,service_creation_time,service_start_time,service_duration,target_temperature,fan_speed) VALUES (%d, '%s', '%s', %ld, %f, '%s');",
            sub_id, create, start, duration, target_temp, fan_speed);
    rc = sqlite3_exec(db, sql, nullptr, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        LOG_F(ERROR, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    sqlite3_close(db);
}

int service::start_service() {
    start_time = time(nullptr);
    cur_status = WORKING;
    return 0;
}

int service::stop_service() {
    cur_status = FREE;
    return 0;
}
