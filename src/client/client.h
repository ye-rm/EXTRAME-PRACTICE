//
// Created by 98770 on 2024/5/10.
//

#ifndef EXTRAME_PRACTICE_CLIENT_H
#define EXTRAME_PRACTICE_CLIENT_H

#include "../../lib/loguru/loguru.hpp"
#include "../common/socket.h"
#include <queue>

#define STATUS_WORKING 1
#define STATUS_FREE 0
#define MODE_COOLING 1
#define MODE_HEATING 2
#define SPEED_HIGH 3
#define SPEED_MEDIUM 2
#define SPEED_LOW 1

class Client {
private:
    int sub_id;
    bool power_status;
    int cur_temp;
    int target_temp;
    int cur_wind_speed;
    int working_mode;
    int cur_status;
    Socket *client_socket;
    std::queue<message> message_queue;
    int send_cur_temp();
public:
    explicit Client(int sub_id);

    ~Client();

    int listen_server();//监听服务端的消息
    int get_status();//获取当前状态, 正在被服务或者等待服务
    int get_sub_id();//获取分机号
    int get_environment_temp();//室内温度模拟算法
    int change_working_mode(int mode);//发送工作模式改变请求，制冷或者制热
    int change_wind_speed(int speed);//发送风速改变请求
    int change_target_temp(int temp);//发送目标温度改变请求
    int handle_server_response();//处理服务端的响应
    int power_on();//开机
    int power_off();//关机
};

#endif //EXTRAME_PRACTICE_CLIENT_H
