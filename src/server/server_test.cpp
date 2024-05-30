//
// Created by 98770 on 2024/5/10.
//
#include "scheduler.h"
#include <string>
int main(int argc,char ** argv) {
    Scheduler scheduler;
    scheduler.server_start();
    while (true){
        std::this_thread::sleep_for(std::chrono::seconds(SECOND_PER_MINUTE*2));
        scheduler.schedule_service();
    }
    return 0;
}