//
// Created by yewenyu on 2024/5/10. client of air conditioner in roomS
//

#ifndef EXTRAME_PRACTICE_CLIENT_H
#define EXTRAME_PRACTICE_CLIENT_H

#include "../../loguru.hpp"
#include "../../lib/rapidcsv/rapidcsv.h"
#include "../common/socket.h"
#include <queue>
#include <atomic>
#include <cmath>
#include <thread>
#include <chrono>
#include "../common/common.h"

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
    int send_finished();//发送服务完成消息
    std::thread emulation_thread;
    std::thread working_thread;
    std::thread keep_alive_thread;
    void client_working();
    double estimate_fee;
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
    int start_client_working();//开始服务
    int check_finished();//检查是否已经完成服务,如果任务完成发送服务完成消息，并关机
    int ignore();//清空消息队列
    //用于gui获取需要的信息
    int get_sub_id() const;//获取分机号
    bool get_power_status() const;//获取开关机状态
    double get_cur_temp() const;//获取当前温度
    double get_target_temp() const;//获取目标温度
    int get_cur_wind_speed() const;//获取当前风速
    int get_working_mode() const;//获取工作模式
    int get_cur_status() const;//获取当前状态
	double get_estimate_fee() const;//获取预估费用
	void clear_estimate_fee();//清空预估费用
};

#endif //EXTRAME_PRACTICE_CLIENT_H
