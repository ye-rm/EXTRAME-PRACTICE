#include "socket.h"

Socket::Socket(int s_id){
    #if defined(_WIN32)
        WSADATA wsaData;
        WSAStartup(MAKEWORD(2, 2), &wsaData);
    #endif
    init_ip();
}