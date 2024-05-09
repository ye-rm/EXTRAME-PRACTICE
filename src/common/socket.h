#include<vector>
#include<map>
#include<string>

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
        IP_ADDRESS server_ip;
        std::map<SUB_ID, IP_ADDRESS> room_ip_map;
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