//
// Created by 98770 on 2024/5/10.
//
#include "scheduler.h"
#include <iostream>

int main(){
    Scheduler scheduler;
    while (true){
#ifdef _WIN32
        Sleep(1000);
#else
        sleep(1);
#endif
        scheduler.listen_client();
        scheduler.handle_message();
    }
    return 0;
}