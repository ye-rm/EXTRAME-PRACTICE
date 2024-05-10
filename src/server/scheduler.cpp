#include "scheduler.h"

void Scheduler::init_socket() {
    server_socket = new Socket(0);
}

Scheduler::Scheduler() {
    init_socket();
    server_socket->listen_client();
}

Scheduler::~Scheduler() {
    delete server_socket;
}

void Scheduler::listen_client() {
    server_socket->get_msg_queue_and_clear(message_queue);
}

void Scheduler::handle_message() {
    while (!message_queue.empty()) {
        message msg = message_queue.front();
        message_queue.pop();
        switch (msg.type) {
            case CHANGE_TEMPERATURE:
                update_service_target_temp(msg.sub_id,msg.paramter);
                break;
            case CHANEG_WIND_SPEED:
                update_service_wind_speed(msg.sub_id,msg.paramter);
                break;
            case POWER_ON:
                create_new_service(msg.sub_id);
                break;
            case POWER_OFF:
                delete_service(msg.sub_id);
                break;
            default:
                break;
        }
    }
}

void Scheduler::update_temp(int sub_id) {
    message msg{sub_id,REQUEST_TEMPERATURE, 0};
    server_socket->send_to_client(sub_id, msg);
}

void Scheduler::update_service_target_temp(int sub_id,int temp) {
    service *s = find_service_by_sub_id(sub_id);
    if (s!= nullptr){
        s->change_target_temp(temp);
    }
}

void Scheduler::update_service_wind_speed(int sub_id, int speed) {
    service *s = find_service_by_sub_id(sub_id);
    if (s!= nullptr){
        s->change_wind_speed(speed);
    }
}

void Scheduler::create_new_service(int sub_id) {
    service *s = find_service_by_sub_id(sub_id);
    if (s== nullptr){
        auto *new_s = new service(sub_id);
        waiting.push_back(new_s);
    }
}

service* Scheduler::find_service_by_sub_id(int sub_id) {
    for(auto s: servicing){
        if (s->get_sub_id() == sub_id){
            return s;
        }
    }
    for (auto s: waiting){
        if (s->get_sub_id() == sub_id){
            return s;
        }
    }
    return nullptr;
}

void Scheduler::delete_service(int sub_id) {
    service *s = find_service_by_sub_id(sub_id);
    if (s!= nullptr){
        s->generate_detailed_record();
        delete s;
    }
}

