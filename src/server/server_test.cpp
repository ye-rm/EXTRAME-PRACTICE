//
// Created by 98770 on 2024/5/10.
//
#include "scheduler.h"
int main() {
    Scheduler scheduler;
    while (true) {
#ifdef _WIN32
        Sleep(1000);
#else
        sleep(SECOND_PER_MINUTE);
#endif
        scheduler.schedule_service();
    }
    return 0;
}