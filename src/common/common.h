//
// Created by yewenyu on 2024/5/12. define common const values and config path
//
//Todo 实现从配置文件中读取配置信息
#ifndef EXTRAME_PRACTICE_COMMON_H
#define EXTRAME_PRACTICE_COMMON_H

#define HIGH_SPEED 3
#define MEDIUM_SPEED 2
#define LOW_SPEED 1
#define COOLING_MODE 1
#define HEATING_MODE 0
#define WORKING 1
#define WAITING 0
#define ON 1
#define OFF 0
#define SECOND_PER_MINUTE 10
#define DEFAULT_SPEED MEDIUM_SPEED
#define TEST_CONFIG_FILE "C:\\Users\\98770\\Source\\Repos\\ye-rm\\EXTRAME-PRACTICE\\hot.csv"
#define SCHEDULER_CONFIG_FILE "C:\\Users\\98770\\Source\\Repos\\ye-rm\\EXTRAME-PRACTICE\\serverconfig.csv"
#define SOCKET_CONFIG_FILE "C:\\Users\\98770\\Source\\Repos\\ye-rm\\EXTRAME-PRACTICE\\room_msg.csv"
#define SQLITE_FILE "C:\\Users\\98770\\Source\\Repos\\ye-rm\\EXTRAME-PRACTICE\\sqlite\\bupt.sqlite"
#define PRICE_PER_MINUTE_AT_LOW_SPEED 0.33
#define PRICE_PER_MINUTE_AT_MEDIUM_SPEED 0.5
#define PRICE_PER_MINUTE_AT_HIGH_SPEED 1.0
#define DEFAULT_TARGET_TEMP 22
#define DEFAULT_WORK_MODE HEATING_MODE

#endif //EXTRAME_PRACTICE_COMMON_H
