//
// Created by 98770 on 2024/5/9.
//

#ifndef EXTRAME_PRACTICE_SCHEDULER_H
#define EXTRAME_PRACTICE_SCHEDULER_H

#include <iostream>
#include "../common/socket.h"
#include <vector>
#include <queue>
#include <thread>
#include <string>
#include "service.h"
#include "../../lib/loguru/loguru.hpp"
#include "../../lib/rapidcsv/rapidcsv.h"


class Scheduler {
private:
    std::vector<service *> servicing;
    std::vector<service *> waiting;
    std::queue<message> message_queue;
    int capicity;
    Socket *server_socket;
    std::thread handle_msg_thread;
    bool scheduler_running= false;
    void update_service_cur_temp(SUB_ID sub_id, double temp);

    void create_new_service(SUB_ID sub_id);

    void delete_service(SUB_ID sub_id);

    void update_service_target_temp(SUB_ID sub_id, double temp);

    void update_service_wind_speed(SUB_ID sub_id, int speed);

    void update_service_working_mode(SUB_ID sub_id, int mode);

    void send_service_status(SUB_ID sub_id);

    void send_temp_request(SUB_ID sub_id);

    service *find_service_by_sub_id(SUB_ID sub_id);

    void init_config_file();

    void order_waitinglist();

    void handle_power_off(SUB_ID sub_id);

    void handle_msg();

public:
    Scheduler();

    ~Scheduler();

    void schedule_service();

    void update_service_cur_temp();

    std::string* get_queue_info();

    void server_start();

    void listen_client();

    void handle_message();
};

#endif //EXTRAME_PRACTICE_SCHEDULER_H
