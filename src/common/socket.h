#include<vector>
#include<map>
#include<string>

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
#define IP_ADDRESS std::string
typedef struct message message;

enum message_type {
    CHANGE_TEMPERATURE,
    CHANEG_WIND_SPEED,
    REQUEST_TEMPERATURE,
    SEND_TEMPERATURE,
    REQUEST_STATUS,
    SEND_STATUS,
    POWER_ON,
    POWER_OFF,
    ERROR,
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
    public:
        //接受到的消息缓冲区
        std::vector<message> received;
        Socket(int s_id);
        ~Socket();
        int listen_server();
        int send_to_server(SUB_ID sub_id,message msg);
        int listen_client();
        int stop_listen_client();
        int send_to_client(SUB_ID sub_id, message msg);
};