//
// Created by 98770 on 2024/5/10.
//
#include "client.h"



Client::Client(int sub_id) {
    this->sub_id = sub_id;
    power_status = false;
    cur_temp = get_environment_temp();
    target_temp = 25;
    cur_wind_speed = SPEED_MEDIUM;
    working_mode = MODE_COOLING;
    cur_status = STATUS_FREE;
    client_socket = new Socket(sub_id);
    client_socket->listen_server();
    LOG_F(INFO, "Client %d init", sub_id);
}

Client::~Client() {
    client_socket->stop_listen();
    delete client_socket;
}

int Client::get_status() {
    message req = {sub_id, message_type::REQUEST_STATUS, 0};
    client_socket->send_to_server(req);
    return 0;
}

int Client::listen_server() {
    client_socket->get_msg_queue_and_clear(message_queue);
    return 0;
}

int Client::get_sub_id() {
    return sub_id;
}

int Client::get_environment_temp() {
    // 模拟室内温度
    return 25;
}

int Client::change_working_mode(int mode) {
    if (working_mode==mode) {
        return 0;
    }
    if (mode!=MODE_COOLING && mode!=MODE_HEATING) {
        return -1;
    }
    message req = {sub_id, message_type::CHANGE_WORKING_MOOD, mode};
    client_socket->send_to_server(req);
    return 0;
}

int Client::change_wind_speed(int speed) {
    if (cur_wind_speed==speed) {
        return 0;
    }
    if (speed!=SPEED_HIGH && speed!=SPEED_MEDIUM && speed!=SPEED_LOW) {
        return -1;
    }
    message req = {sub_id, message_type::CHANGE_WIND_SPEED, speed};
    client_socket->send_to_server(req);
    return 0;
}

int Client::change_target_temp(int temp) {
    if (temp==target_temp) {
        return 0;
    }
    //防止顾客紫砂
    if (temp<16 || temp>30) {
        return -1;
    }
    message req = {sub_id, message_type::CHANGE_TEMPERATURE, temp};
    client_socket->send_to_server(req);
    return 0;
}

int Client::handle_server_response() {
    while (!message_queue.empty()) {
        message msg = message_queue.front();
        message_queue.pop();
        switch (msg.type) {
            case message_type::SEND_TEMPERATURE:
                cur_temp = msg.paramter;
                LOG_F(INFO, "Client %d get temp %d", sub_id, cur_temp);
                break;
            case message_type::SEND_STATUS:
                cur_status = msg.paramter;
                LOG_F(INFO, "Client %d get status %d", sub_id, cur_status);
                break;
            case message_type::REQUEST_TEMPERATURE:
                send_cur_temp();
                break;
            default:
                break;
        }
    }
}

int Client::send_cur_temp() {
    message req = {sub_id, message_type::SEND_TEMPERATURE, cur_temp};
    client_socket->send_to_server(req);
    return 0;
}

int Client::power_on() {
    if (power_status) {
        return 0;
    }
    message req = {sub_id, message_type::POWER_ON, 0};
    client_socket->send_to_server(req);
    power_status = true;
    return 0;
}

int Client::power_off() {
    if (!power_status) {
        return 0;
    }
    message req = {sub_id, message_type::POWER_OFF, 0};
    client_socket->send_to_server(req);
    power_status = false;
    return 0;
}