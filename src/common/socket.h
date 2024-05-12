#include<vector>
#include<map>
#include<string>
#include"../../lib/rapidcsv/rapidcsv.h"
#include <thread>
#include <cstring>
#include <atomic>
#include <mutex>
#include <queue>
#include "../../lib/loguru/loguru.hpp"

#ifdef _WIN32

#include <WinSock2.h>
#include <Ws2tcpip.h>

#pragma  comment(lib, "Ws2_32.lib")
#else

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define SOCKET int
#define INVALID_SOCKET (SOCKET)(~0)
#define SOCKET_ERROR (-1)
#endif

#define PORT 6666
#define SUB_ID int
#define MAX_SUB_COUNT 10
#define IP_ADDRESS std::string
typedef struct message message;

const IP_ADDRESS SERVER_IP = "127.0.0.112";

enum message_type {
    CHANGE_TEMPERATURE,
    CHANGE_WIND_SPEED,
    REQUEST_TEMPERATURE,
    CHANGE_WORKING_MOOD,
    SEND_TEMPERATURE,
    REQUEST_STATUS,
    SEND_STATUS,
    POWER_ON,
    POWER_OFF,
    FINISHED,
    ERR,
    OK,
};

//按一字节对齐
#pragma pack(1)
struct message {
    int sub_id;
    message_type type;
    double paramter;
};
#pragma pack()

class Socket {
private:
    std::string server_ip;
    std::map<SUB_ID, IP_ADDRESS> sub_ip_map;
#ifdef _WIN32
    SOCKET sockfd;
#else
    int sockfd;
#endif
    std::string socket_ip;

    int init_ip();  //init server_ip and room_ip_map
    std::thread listen_thread;

    void listen_thread_func();

    std::atomic<bool> listen_flag = true;

    std::mutex mutex;
public:
    //接受到的消息缓冲区
    std::queue<message> received;

    explicit Socket(int s_id);

    ~Socket();

    int listen_server();

    int send_to_server(message msg);

    int listen_client();

    int stop_listen();

    int send_to_client(SUB_ID sub_id, message msg);

    int get_msg_queue_and_clear(std::queue<message> &msg_queue);

    IP_ADDRESS get_ip(SUB_ID sub_id);   //get ip by sub_id
};