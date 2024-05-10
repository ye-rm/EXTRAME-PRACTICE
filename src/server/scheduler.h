//
// Created by 98770 on 2024/5/9.
//

#ifndef EXTRAME_PRACTICE_SCHEDULER_H
#define EXTRAME_PRACTICE_SCHEDULER_H
#include <iostream>
#include "../common/socket.h"
#include <vector>
#include <queue>
#include "service.h"

class Scheduler{
private:
    std::vector<service*> servicing;
    std::vector<service*> waiting;
    std::queue<message> message_queue;
    int capicity;
    Socket *server_socket;
    void init_socket();
    void update_temp(SUB_ID sub_id);
    void create_new_service(SUB_ID sub_id);
    void delete_service(SUB_ID sub_id);
    void update_service_target_temp(SUB_ID sub_id,int temp);
    void update_service_wind_speed(SUB_ID sub_id,int speed);
    service* find_service_by_sub_id(SUB_ID sub_id);
public:
    Scheduler();
    ~Scheduler();
    void schedule_service();
    void send_temp_request(SUB_ID sub_id);
    void listen_client();
    void handle_message();
};
#endif //EXTRAME_PRACTICE_SCHEDULER_H
