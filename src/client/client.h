//
// Created by 98770 on 2024/5/10.
//

#ifndef EXTRAME_PRACTICE_CLIENT_H
#define EXTRAME_PRACTICE_CLIENT_H

#include "../../lib/loguru/loguru.hpp"
#include "../../lib/rapidcsv/rapidcsv.h"
#include "../common/socket.h"
#include <queue>
#include <atomic>
#include <cmath>
#include <thread>
#include <chrono>

#define STATUS_WORKING 1
#define STATUS_FREE 0
#define MODE_COOLING 1
#define MODE_HEATING 2
#define SPEED_HIGH 3
#define SPEED_MEDIUM 2
#define SPEED_LOW 1
#define DEFAULT_TARGET_TEMP 27
#define ON true
#define OFF false

class Client {
private:
    int sub_id;
    bool power_status;
    std::atomic<double> cur_temp;
    double target_temp;
    int cur_wind_speed;
    double default_temp;
    int working_mode;
    int cur_status;
    Socket *client_socket;
    std::queue<message> message_queue;

    void init_default_temp();

    int send_cur_temp();

    void temp_emulation();

    std::thread emulation_thread;
public:
    explicit Client(int sub_id);

    ~Client();

    int listen_server();//监听服务端的消息
    int get_status();//从服务器获取当前状态, 正在被服务或者等待服务
    void get_environment_temp();//室内温度模拟算法
    int change_working_mode(int mode);//发送工作模式改变请求，制冷或者制热
    int change_wind_speed(int speed);//发送风速改变请求
    int change_target_temp(double temp);//发送目标温度改变请求
    int handle_server_response();//处理服务端的响应
    int power_on();//开机
    int power_off();//关机
    //用于gui获取需要的信息
    int get_sub_id() const;//获取分机号
    bool get_power_status() const;//获取开关机状态
    double get_cur_temp() const;//获取当前温度
    double get_target_temp() const;//获取目标温度
    int get_cur_wind_speed() const;//获取当前风速
    int get_working_mode() const;//获取工作模式
    int get_cur_status() const;//获取当前状态
};

#endif //EXTRAME_PRACTICE_CLIENT_H
