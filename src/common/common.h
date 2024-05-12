//
// Created by 98770 on 2024/5/12.
//

#ifndef EXTRAME_PRACTICE_COMMON_H
#define EXTRAME_PRACTICE_COMMON_H
#include "../../lib/rapidcsv/rapidcsv.h"
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
#define TEST_CONFIG_FILE "../cool.csv"
#define PRICE_PER_MINUTE_AT_LOW_SPEED 0.33
#define PRICE_PER_MINUTE_AT_MEDIUM_SPEED 0.5
#define PRICE_PER_MINUTE_AT_HIGH_SPEED 1.0
#define DEFAULT_TARGET_TEMP 25

//int read_my_config(){
//    rapidcsv::Document doc(TEST_CONFIG_FILE);
//    DEFAULT_TARGET_TEMP = doc.GetCell<int>(3, 0);
//    return 0;
//}
#endif //EXTRAME_PRACTICE_COMMON_H
