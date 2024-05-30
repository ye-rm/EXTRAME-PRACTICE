//
// Created by yewenyu on 2024/5/30, monitor ui for air conditioner
//
#include "MainWindow.h"
#include "../../src/server/scheduler.h"
#include <thread>
#include <QApplication>


void thread_func(Scheduler& scheduler){
    while (true){
        std::this_thread::sleep_for(std::chrono::seconds(SECOND_PER_MINUTE));
        scheduler.schedule_service();
    }
}

int ui_func(int argc, char **argv, Scheduler& scheduler){
    QApplication a(argc, argv);
    MainWindow w;
    w.linkScheduler(&scheduler);
    w.show();
    return a.exec();
}

int main(int argc, char **argv) {
    Scheduler s;
    s.server_start();
    std::thread t(thread_func,std::ref(s));
    std::thread t_ui(ui_func,argc,argv,std::ref(s));

    t.join();
    t_ui.join();
    return 0;
}
