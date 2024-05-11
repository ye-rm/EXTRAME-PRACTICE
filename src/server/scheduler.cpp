#include "scheduler.h"


Scheduler::Scheduler() {
    server_socket = new Socket(0);
    server_socket->listen_client();
    init_config_file();
    LOG_F(INFO, "Scheduler started with capicity %d", capicity);
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
                update_service_target_temp(msg.sub_id, (int) msg.paramter);
                break;
            case CHANGE_WIND_SPEED:
                update_service_wind_speed(msg.sub_id, (int) msg.paramter);
                break;
            case CHANGE_WORKING_MOOD:
                update_service_working_mode(msg.sub_id, (int) msg.paramter);
                break;
            case REQUEST_STATUS:
                send_service_status(msg.sub_id);
                break;
            case SEND_TEMPERATURE://client send temperature
                update_service_cur_temp(msg.sub_id, msg.paramter);
                break;
            case POWER_ON:
                create_new_service(msg.sub_id);
                break;
            case POWER_OFF:
                handle_power_off(msg.sub_id);
                break;
            default:
                break;
        }
    }
}

void Scheduler::update_service_target_temp(int sub_id, double temp) {
    service *s = find_service_by_sub_id(sub_id);
    if (s != nullptr) {
        s->change_target_temp(temp);
        LOG_F(INFO, "service %d target temp changed to %f", sub_id, temp);
        return;
    }
    LOG_F(WARNING, "can not change temp service %d not found", sub_id);
}

void Scheduler::update_service_wind_speed(int sub_id, int speed) {
    service *s = find_service_by_sub_id(sub_id);
    if (s != nullptr) {
        s->change_wind_speed(speed);
        if (s->get_status() == WORKING) {
            s->stop_service();
            s->generate_detailed_record();
            s->start_service();
            LOG_F(INFO, "running service %d wind speed changed to %d and generate detailed list", sub_id, speed);
        } else {
            LOG_F(INFO, "service %d wind speed changed to %d", sub_id, speed);
        }
        return;
    }
    LOG_F(WARNING, "can not change wind speed service %d not found", sub_id);
}

void Scheduler::create_new_service(int sub_id) {
    service *s = find_service_by_sub_id(sub_id);
    if (s == nullptr) {
        auto *new_s = new service(sub_id);
        waiting.push_back(new_s);
        LOG_F(INFO, "service %d created", sub_id);
        return;
    }
    LOG_F(WARNING, "service %d already exist", sub_id);
}

service *Scheduler::find_service_by_sub_id(int sub_id) {
    for (auto s: servicing) {
        if (s->get_sub_id() == sub_id) {
            return s;
        }
    }
    for (auto s: waiting) {
        if (s->get_sub_id() == sub_id) {
            return s;
        }
    }
    return nullptr;
}

void Scheduler::delete_service(int sub_id) {
    service *s = find_service_by_sub_id(sub_id);
    delete s;
    LOG_F(INFO, "service %d deleted", sub_id);
}

void Scheduler::update_service_working_mode(int sub_id, int mode) {
    service *s = find_service_by_sub_id(sub_id);
    if (s != nullptr) {
        s->chahge_working_mood(mode);
        LOG_F(INFO, "service %d working mode changed to %d", sub_id, mode);
        return;
    }
    LOG_F(WARNING, "can not change working mode service %d not found", sub_id);
}

void Scheduler::send_service_status(int sub_id) {
    service *s = find_service_by_sub_id(sub_id);
    if (s != nullptr) {
        message msg{sub_id, SEND_STATUS, (double) s->get_status()};
        server_socket->send_to_client(sub_id, msg);
        LOG_F(INFO, "server send status to %d", sub_id);
    }
    LOG_F(WARNING, "request status of service %d not found", sub_id);
}

void Scheduler::send_temp_request(int sub_id) {
    message msg{sub_id, REQUEST_TEMPERATURE, 0};
    server_socket->send_to_client(sub_id, msg);
    LOG_F(INFO, "scheduler request temp to %d", sub_id);
}

void Scheduler::update_service_cur_temp(int sub_id, double temp) {
    service *s = find_service_by_sub_id(sub_id);
    if (s != nullptr) {
        s->update_cur_temp(temp);
        LOG_F(INFO, "service %d cur temp updated to %f", sub_id, temp);
        return;
    }
    LOG_F(WARNING, "can not update cur temp service %d not found", sub_id);
}

void Scheduler::update_service_cur_temp() {
    for (auto s: servicing) {
        send_temp_request(s->get_sub_id());
    }
    for (auto s: waiting) {
        send_temp_request(s->get_sub_id());
    }
}

/*
 * assume all service wind speed is low, 3 waiting, 3 servicing and not finished
 * 3 waiting id 1,2,3, 3 servicing id 4,5,6
 * first in scheduler, 3 servicing pop back and push to waiting
 * waiting id 1,2,3,6,5,4
 * then in order_waitinglist
 * first low id 1,2,3,6,5,4
 * then low is 4,5,6,3,2,1
 * so this implement rr when all service wind speed is same
 */
void Scheduler::schedule_service() {
    //update cur temp of all service
    update_service_cur_temp();
    while (!servicing.empty()) {
        service *s = servicing.back();
        if (s->check_finished()) {
            s->stop_service();
            s->generate_detailed_record();
            delete_service(s->get_sub_id());
        } else {
            s->stop_service();
            s->generate_detailed_record();
            waiting.push_back(s);
        }
        servicing.pop_back();
    }
    order_waitinglist();
    for (int i = 0; i < capicity; ++i) {
        service *s = waiting.back();
        s->start_service();
        servicing.push_back(s);
        waiting.pop_back();
    }
}

void Scheduler::init_config_file() {
    rapidcsv::Document doc("../serverconfig.csv");
    capicity = doc.GetCell<int>(0, 1);
}

// after order the waiting list, the order is front: low, medium, high :end
void Scheduler::order_waitinglist() {
    std::vector<service> high;
    std::vector<service> medium;
    std::vector<service> low;
    for (auto s: waiting) {
        switch (s->get_cur_wind_speed()) {
            case HIGH:
                high.push_back(*s);
                break;
            case MEDIUM:
                medium.push_back(*s);
                break;
            case LOW:
                low.push_back(*s);
                break;
            default:
                break;
        }
    }
    waiting.clear();
    while (!low.empty()) {
        waiting.push_back(&low.back());
        low.pop_back();
    }
    while (!medium.empty()) {
        waiting.push_back(&medium.back());
        medium.pop_back();
    }
    while (!high.empty()) {
        waiting.push_back(&high.back());
        high.pop_back();
    }
}

void Scheduler::handle_power_off(int sub_id) {
    service *s = find_service_by_sub_id(sub_id);
    if (s != nullptr) {
        if (s->get_status() == WORKING){
            servicing.pop_back();
            s->stop_service();
            s->generate_detailed_record();
            delete_service(sub_id);
            service *to_add = waiting.back();
            servicing.push_back(to_add);
            waiting.pop_back();
        }else{
            delete_service(sub_id);
        }
    }
    LOG_F(WARNING, "can not power off service %d not found", sub_id);
}
