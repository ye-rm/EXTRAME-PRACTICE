//
// Created by 98770 on 2024/5/10.
//
#include "scheduler.h"
#include <iostream>

int main() {
    Scheduler scheduler;
    while (true) {
#ifdef _WIN32
        Sleep(1000);
#else
        sleep(2);
#endif
        scheduler.listen_client();
        scheduler.handle_message();
        scheduler.update_service_cur_temp();
    }
    return 0;
}