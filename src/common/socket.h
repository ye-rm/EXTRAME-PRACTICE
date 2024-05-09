#include<vector>
#include<map>
#include<string>
#include"rapidcsv.h"
#include <thread>
#include <cstring>

#ifdef _WIN32
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
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

const IP_ADDRESS SERVER_IP = "127.0.0.2";

enum message_type {
    CHANGE_TEMPERATURE,
    CHANEG_WIND_SPEED,
    REQUEST_TEMPERATURE,
    SEND_TEMPERATURE,
    REQUEST_STATUS,
    SEND_STATUS,
    POWER_ON,
    POWER_OFF,
    ERR,
    OK,
};

struct message {
    int sub_id;
    message_type type;
    int paramter;
};

class Socket {
private:
    std::string server_ip;
    std::map<SUB_ID, IP_ADDRESS> sub_ip_map;
    int sockfd;
    std::string socket_ip;

    int init_ip();  //init server_ip and room_ip_map
    std::thread listen_thread;

    void listen_thread_func();

public:
    //接受到的消息缓冲区
    std::vector<message> received;

    explicit Socket(int s_id);

    ~Socket();

    int listen_server();

    int send_to_server(message msg);

    int listen_client();

    int stop_listen();

    int send_to_client(SUB_ID sub_id, message msg);

    IP_ADDRESS get_ip(SUB_ID sub_id);   //get ip by sub_id
};