#include "socket.h"
#include <iostream>

int main() {
    //ignore SIGPIPE
    message slist[3]={
            {0, message_type::REQUEST_TEMPERATURE, 0},
            {0, message_type::REQUEST_STATUS, 0},
            {0, message_type::CHANGE_TEMPERATURE, 26}
    };
    message clist[3]={
            {1, message_type::OK, 0},
            {1, message_type::REQUEST_TEMPERATURE, 0},
            {1, message_type::REQUEST_TEMPERATURE, 0}
    };
    // 类实例化s，参数为0表示服务端
    Socket s(0);
    // 类实例化s2和s3，参数为1表示客户端，分机号为1
    Socket s2(1);
    Socket s3(2);
    // 服务端和客户端监听发送到的信息
    s.listen_client();
    s2.listen_server();
    s3.listen_server();
    // 客户端发送信息给服务端
    s2.send_to_server(message{0, message_type::REQUEST_TEMPERATURE, 0});
    s2.send_to_server(message{0, message_type::REQUEST_STATUS, 0});
    s2.send_to_server(message{0, message_type::CHANGE_TEMPERATURE, 26});
    s3.send_to_server(message{0, message_type::REQUEST_TEMPERATURE, 0});
    s3.send_to_server(message{0, message_type::REQUEST_STATUS, 0});
    s3.send_to_server(message{0, message_type::CHANGE_TEMPERATURE, 26});
#ifdef _WIN32
    Sleep(2000);
#else
    sleep(2);
#endif
    // 服务端发送信息给客户端，第一个是分机号，第二个是一个消息结构体
    s.send_to_client(1,message{1, message_type::OK, 0});
    s.send_to_client(1,message{1, message_type::REQUEST_TEMPERATURE, 0});
    s.send_to_client(1,message{1, message_type::REQUEST_TEMPERATURE, 0});
#ifdef _WIN32
    Sleep(2000);
#else
    sleep(2);
#endif
    // 判断接收到的信息是否正确
    for (int i = 0; i < 3; ++i) {
        if (slist[i].type!=s.received.front().type) {
            std::cout << "error" << std::endl;
            return 1;
        }
        std::cout << "ok" << std::endl;
        s.received.pop();
    }
    for (int i = 3; i < 6; ++i) {
        if (slist[i-3].type!=s.received.front().type) {
            std::cout << "error" << std::endl;
            return 1;
        }
        std::cout << "ok" << std::endl;
        s.received.pop();
    }
    for (int i = 0; i < s2.received.size(); ++i) {
        if (clist[i].type!=s2.received.front().type) {
            std::cout << "error" << std::endl;
            return 1;
        }
        std::cout << "ok" << std::endl;
        s2.received.pop();
    }
    s.stop_listen();
    s2.stop_listen();
    s3.stop_listen();
    return 0;
};