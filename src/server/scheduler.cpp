#include "scheduler.h"


Scheduler::Scheduler() {
    capicity = 10;
    server_socket = new Socket(0);
    server_socket->listen_client();
    LOG_F(INFO,"Scheduler started with capicity %d",capicity);
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
            case CHANGE_WIND_SPEED:
                update_service_wind_speed(msg.sub_id,msg.paramter);
                break;
            case CHANGE_WORKING_MOOD:
                update_service_working_mode(msg.sub_id,msg.paramter);
                break;
            case REQUEST_STATUS:
                send_service_status(msg.sub_id);
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
    LOG_F(INFO,"scheduler request temp to %d",sub_id);
    server_socket->send_to_client(sub_id, msg);
}

void Scheduler::update_service_target_temp(int sub_id,int temp) {
    service *s = find_service_by_sub_id(sub_id);
    if (s!= nullptr){
        s->change_target_temp(temp);
        LOG_F(INFO,"service %d target temp changed to %d",sub_id,temp);
        return;
    }
    LOG_F(WARNING,"can not change temp service %d not found",sub_id);
}

void Scheduler::update_service_wind_speed(int sub_id, int speed) {
    service *s = find_service_by_sub_id(sub_id);
    if (s!= nullptr){
        s->change_wind_speed(speed);
        LOG_F(INFO,"service %d wind speed changed to %d",sub_id,speed);
        return;
    }
    LOG_F(WARNING,"can not change wind speed service %d not found",sub_id);
}

void Scheduler::create_new_service(int sub_id) {
    service *s = find_service_by_sub_id(sub_id);
    if (s== nullptr){
        auto *new_s = new service(sub_id);
        waiting.push_back(new_s);
        LOG_F(INFO,"service %d created",sub_id);
        return;
    }
    LOG_F(WARNING,"service %d already exist",sub_id);
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
//        s->generate_detailed_record();
        delete s;
    }
    LOG_F(INFO,"service %d deleted",sub_id);
}

void Scheduler::update_service_working_mode(int sub_id, int mode) {
    service *s = find_service_by_sub_id(sub_id);
    if (s!= nullptr){
        s->chahge_working_mood(mode);
        LOG_F(INFO,"service %d working mode changed to %d",sub_id,mode);
        return;
    }
    LOG_F(WARNING,"can not change working mode service %d not found",sub_id);
}

void Scheduler::send_service_status(int sub_id) {
    service *s = find_service_by_sub_id(sub_id);
    if (s!= nullptr){
        message msg{sub_id,SEND_STATUS,s->get_status()};
        server_socket->send_to_client(sub_id, msg);
        LOG_F(INFO,"server send status to %d",sub_id);
    }
    LOG_F(WARNING,"request status of service %d not found",sub_id);
}
