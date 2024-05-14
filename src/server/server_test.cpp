//
// Created by 98770 on 2024/5/10.
//
#include "scheduler.h"
#include <string>
int main() {
    Scheduler scheduler;
    scheduler.server_start();
    while (true){
        sleep(SECOND_PER_MINUTE*2);
        scheduler.schedule_service();
        auto service = scheduler.get_queue_info();
        LOG_F(INFO, "%s", (*service).c_str());
        delete service;
    }
    return 0;
}