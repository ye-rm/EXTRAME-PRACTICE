//
// Created by 98770 on 2024/5/10.
//
#include "client.h"


Client::Client(int sub_id) {
    this->sub_id = sub_id;
    power_status = false;
    init_default_temp();
    cur_temp = default_temp;
    target_temp = DEFAULT_TARGET_TEMP;
    cur_wind_speed = DEFAULT_SPEED;
    working_mode = DEFAULT_WORK_MODE;
    cur_status = WAITING;
    client_socket = new Socket(sub_id);
    client_socket->listen_server();
    LOG_F(INFO, "Client %d init", sub_id);
}

Client::~Client() {
    client_socket->stop_listen();
    delete client_socket;
}

// ask scheduler whether scheduler put this in servicing queue
int Client::get_status() {
    message req = {sub_id, message_type::REQUEST_STATUS, 0};
    client_socket->send_to_server(req);
    LOG_F(INFO, "Client %d request status from server", sub_id);
    return 0;
}

int Client::listen_server() {
    client_socket->get_msg_queue_and_clear(message_queue);
    return 0;
}

int Client::get_sub_id() const {
    return sub_id;
}

void Client::get_environment_temp() {
    emulation_thread = std::thread(&Client::temp_emulation, this);
}

void Client::temp_emulation() {
    while (true) {
        // 开机且总机正在服务分机
        if (power_status == ON && cur_status == WORKING) {
            //制冷模式
            if (working_mode == COOLING_MODE) {
                //房间现在温度大于目标温度，继续制冷
                if (cur_temp > target_temp) {
                    switch (cur_wind_speed) {
                        case HIGH_SPEED:
                            cur_temp = cur_temp - 1;
                            break;
                        case MEDIUM_SPEED:
                            cur_temp = cur_temp - 0.5;
                            break;
                        case LOW_SPEED:
                            cur_temp = cur_temp - 0.33;
                            break;
                        default:
                            break;
                    }
                }
            } else if (working_mode == HEATING_MODE) {
                //房间现在温度小于目标温度，继续制热
                if (cur_temp < target_temp) {
                    switch (cur_wind_speed) {
                        case HIGH_SPEED:
                            cur_temp = cur_temp + 1;
                            break;
                        case MEDIUM_SPEED:
                            cur_temp = cur_temp + 0.5;
                            break;
                        case LOW_SPEED:
                            cur_temp = cur_temp + 0.33;
                            break;
                        default:
                            break;
                    }
                }
            }
        } else {
            //房间空调关机或总机未服务分机
            //如果当前温度和默认温度相差小于0.2度，认为房间回到默认温度
            if (fabs(cur_temp - default_temp) < 0.2) {
                continue;
            }
            //如果当前温度大于默认温度，缓慢降温
            if (cur_temp > default_temp) {
                cur_temp = cur_temp - 0.5;
            } else {
                cur_temp = cur_temp + 0.5;
            }
        }
        LOG_F(INFO, "Client %d cur temp changed to %f", sub_id, double (cur_temp));
        // run per minute
		std::this_thread::sleep_for(std::chrono::seconds(SECOND_PER_MINUTE));
    }
}

int Client::change_working_mode(int mode) {
    if (working_mode == mode) {
        return 0;
    }
    if (mode != COOLING_MODE && mode != HEATING_MODE) {
        return -1;
    }
    message req = {sub_id, message_type::CHANGE_WORKING_MOOD, (double) mode};
    client_socket->send_to_server(req);
    working_mode = mode;
    char mode_str[10];
    if (mode == COOLING_MODE) {
        strcpy(mode_str, "cooling");
    } else {
        strcpy(mode_str, "heating");
    }
    LOG_F(INFO, "Client %d working mode changed to %s", sub_id, mode_str);
    return 0;
}

int Client::change_wind_speed(int speed) {
    if (cur_wind_speed == speed) {
        return 0;
    }
    if (speed != HIGH_SPEED && speed != MEDIUM_SPEED && speed != LOW_SPEED) {
        return -1;
    }
    message req = {sub_id, message_type::CHANGE_WIND_SPEED, (double) speed};
    client_socket->send_to_server(req);
    cur_wind_speed = speed;
    LOG_F(INFO, "Client %d wind speed changed to %d", sub_id, speed);
    return 0;
}

int Client::change_target_temp(double temp) {
    if (temp == target_temp) {
        return 0;
    }
    //防止顾客紫砂
    if (temp < 0 || temp > 40) {
        return -1;
    }
    message req = {sub_id, message_type::CHANGE_TEMPERATURE, temp};
    client_socket->send_to_server(req);
    target_temp = temp;
    LOG_F(INFO, "Client %d target temp changed to %f", sub_id, double (temp));
    return 0;
}

int Client::handle_server_response() {
    while (!message_queue.empty()) {
        message msg = message_queue.front();
        message_queue.pop();
        switch (msg.type) {
            case SEND_STATUS:
                cur_status = (int) msg.paramter;
                LOG_F(INFO, "Client %d status changed to %d", sub_id, cur_status);
                break;
            case message_type::REQUEST_TEMPERATURE:
                send_cur_temp();
                break;
            default:
                break;
        }
    }
    return 0;
}

int Client::send_cur_temp() {
    message req = {sub_id, message_type::SEND_TEMPERATURE, cur_temp};
    client_socket->send_to_server(req);
    LOG_F(INFO, "Client %d send temp %f", sub_id, double (cur_temp));
    return 0;
}

int Client::power_on() {
    if (power_status) {
        return 0;
    }
    // 复位初始状态
    target_temp = DEFAULT_TARGET_TEMP;
    cur_wind_speed = DEFAULT_SPEED;
    working_mode = DEFAULT_WORK_MODE;
    cur_status = WAITING;
    message req = {sub_id, message_type::POWER_ON, ON};
    client_socket->send_to_server(req);
    power_status = ON;
    LOG_F(INFO, "Client %d power on", sub_id);
    return 0;
}

int Client::power_off() {
    if (!power_status) {
        return 0;
    }
    message req = {sub_id, message_type::POWER_OFF, OFF};
    client_socket->send_to_server(req);
    power_status = OFF;
    LOG_F(INFO, "Client %d power off", sub_id);
    return 0;
}

void Client::init_default_temp() {
    rapidcsv::Document doc(TEST_CONFIG_FILE);
    size_t room_num = doc.GetRowCount();
    for (int i = 0; i < room_num; ++i) {
        if (doc.GetCell<int>(0, i) == sub_id) {
            default_temp = doc.GetCell<int>(1, i);
            return;
        }
    }
}

bool Client::get_power_status() const {
    return power_status;
}

double Client::get_cur_temp() const {
    return cur_temp;
}

double Client::get_target_temp() const {
    return target_temp;
}

int Client::get_cur_wind_speed() const {
    return cur_wind_speed;
}

int Client::get_working_mode() const {
    return working_mode;
}

int Client::get_cur_status() const {
    return cur_status;
}

// check whether client arrive at target temp
// in cooling mode , if cur temp is lower than target temp -> finished
// vice vesa for heating mode
int Client::check_finished() {
    if (power_status == OFF){
        return 0;
    }
    if (working_mode== COOLING_MODE){
        if (cur_temp <= target_temp){
            power_status = OFF;
            send_finished();
            LOG_F(INFO, "Client %d finished", sub_id);
            return 1;
        } else {
            return 0;
        }
    } else {
        if (cur_temp >= target_temp){
            power_status = OFF;
            send_finished();
            LOG_F(INFO, "Client %d finished", sub_id);
            return 1;
        } else {
            return 0;
        }
    }
}

// in power down state, just ignore all msg in queue
int Client::ignore() {
    client_socket->get_msg_queue_and_clear(message_queue);
    while (!message_queue.empty()){
        message_queue.pop();
    }
    return 0;
}

int Client::send_finished() {
    message req = {sub_id, message_type::FINISHED, 0};
    client_socket->send_to_server(req);
    LOG_F(INFO, "Client %d send finished", sub_id);
    return 0;
}

void Client::client_working() {
    while (true) {
        if (power_status == OFF) {
            ignore();
			std::this_thread::sleep_for(std::chrono::seconds(5));
            continue;
        }
		std::this_thread::sleep_for(std::chrono::seconds(1));
        get_status();
		std::this_thread::sleep_for(std::chrono::seconds(1));
        listen_server();
		std::this_thread::sleep_for(std::chrono::seconds(1));
        handle_server_response();
        check_finished();
    }
}

void keep_alive() {
    while (true) {
        
    }
}

int Client::start_client_working() {
    get_environment_temp();
//    keep_alive_thread = std::thread(keep_alive);
    working_thread = std::thread(&Client::client_working, this);
    LOG_F(INFO, "Client %d thread start working", sub_id);
    return 0;
}
