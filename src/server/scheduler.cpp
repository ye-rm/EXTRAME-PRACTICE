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
    LOG_F(INFO, "scheduler fetch message from client");
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
            case FINISHED:
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
        //正在执行的任务改变风速，需要重新生成详单
        if (s->get_status() == WORKING) {
            s->stop_service();
            s->generate_detailed_record();
            s->start_service();
            LOG_F(INFO, "running service %d wind speed changed to %d and generate detailed list", sub_id, speed);
        } else if(s->ever_serviced()){//曾经服务过的任务被调度程序放入等待队列，此时改变风速，需要重新生成详单
            s->generate_detailed_record();
            LOG_F(INFO, "waiting service have serviced %d wind speed changed to %d and generate detailed list", sub_id, speed);
        }
        LOG_F(INFO, "service %d wind speed changed to %d no need to generate", sub_id, speed);
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
    if (s != nullptr) {
        auto it = std::find(servicing.begin(), servicing.end(), s);
        if (it != servicing.end()) {
            servicing.erase(it);
        }
        it = std::find(waiting.begin(), waiting.end(), s);
        if (it != waiting.end()) {
            waiting.erase(it);
        }
        delete s;
    }
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
    }else {
        message tmsg{sub_id, SEND_STATUS, WAITING};
        server_socket->send_to_client(sub_id, tmsg);
        LOG_F(WARNING, "request status of service %d not found, send free back", sub_id);
    }
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
    LOG_F(INFO, "scheduler request temp to all service");
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
    // update all service cur temp

    update_service_cur_temp();
    sleep(1);
    listen_client();
    handle_message();

    LOG_F(INFO, "start schedule procedure");
    if (servicing.empty() && waiting.empty()) {
        LOG_F(INFO, "no service to schedule");
        return;
    }

    std::vector<service *> not_finished;
    // 遍历servicing，将已经完成的服务删除，未完成的服务放入not_finished
    while (!servicing.empty()) {
        service *s = servicing.back();
//        if (s->check_finished()) {
//            s->stop_service();
//            s->generate_detailed_record();
//            delete_service(s->get_sub_id());
//            continue;
//        } else{
            not_finished.push_back(s);
            servicing.pop_back();
//        }
    }
    // 如果等待队列和未完成队列的总和小于等于容量，此时将等待和未完成的服务放入服务队列
    if(waiting.size()+not_finished.size()<=capicity) {
        for (auto s: not_finished) {
            servicing.push_back(s);
        }
        for (auto s: waiting) {
            s->start_service();
            servicing.push_back(s);
        }
        waiting.clear();
        not_finished.clear();
        return;
    }else{
        // 如果等待队列和未完成队列的总和大于容量，此时需要启动调度算法，将未完成的服务停止并生成详单放入等待队列
        for (auto s: not_finished) {
            s->stop_service();
            s->generate_detailed_record();
            waiting.push_back(s);
        }
    }
    // 按风速由低到高排序等待队列
    order_waitinglist();
    // 将等待队列的服务放入服务队列
    for (int i = 0; i < capicity && !waiting.empty(); ++i) {
        service *s = waiting.back();
        s->start_service();
        servicing.push_back(s);
        waiting.pop_back();
    }
}

void Scheduler::init_config_file() {
    rapidcsv::Document doc("../serverconfig.csv");
    capicity = doc.GetCell<int>(0, 0);
}

// after order the waiting list, the order is front: low, medium, high :end
void Scheduler::order_waitinglist() {
    std::vector<service*> high;
    std::vector<service*> medium;
    std::vector<service*> low;
    for (auto s: waiting) {
        switch (s->get_cur_wind_speed()) {
            case HIGH_SPEED:
                high.push_back(s);
                break;
            case MEDIUM_SPEED:
                medium.push_back(s);
                break;
            case LOW_SPEED:
                low.push_back(s);
                break;
            default:
                break;
        }
    }
    waiting.clear();
    while (!low.empty()) {
        waiting.push_back(low.back());
        low.pop_back();
    }
    while (!medium.empty()) {
        waiting.push_back(medium.back());
        medium.pop_back();
    }
    while (!high.empty()) {
        waiting.push_back(high.back());
        high.pop_back();
    }
}

void Scheduler::handle_power_off(int sub_id) {
    service *s = find_service_by_sub_id(sub_id);
    if (s != nullptr) {
        // 要关闭的服务在服务队列中，此时需要将其从服务队列中删除，如果等待队列不为空，将等待队列的一个服务放入服务队列
        if (s->get_status() == WORKING) {
            // 从服务队列中删除指定服务
            auto it = std::find(servicing.begin(), servicing.end(), s);
            if (it != servicing.end()) {
                servicing.erase(it);
            }
            // 删除前生成详单
            s->stop_service();
            s->generate_detailed_record();
            // 如果等待队列不为空，将等待队列的最后一个服务放入服务队列
            if (!waiting.empty()) {
                service *to_add = waiting.back();
                to_add->start_service();
                servicing.push_back(to_add);
                waiting.pop_back();
            }
        } else {
            // 要关闭的服务在等待队列中，此时只需要将其从等待队列中删除
            auto it = std::find(waiting.begin(), waiting.end(), s);
            if (it != waiting.end()) {
                waiting.erase(it);
            }
            // 如果要关闭的服务曾经服务过，生成详单
            if (s->ever_serviced()){
                s->generate_detailed_record();
            }
        }
        delete s;
        LOG_F(INFO, "service %d power off", sub_id);
    }
    LOG_F(WARNING, "can not power off service %d not found", sub_id);
}
