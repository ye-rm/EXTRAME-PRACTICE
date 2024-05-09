#include "socket.h"

int Socket::init_ip() {
    rapidcsv::Document doc("/home/wenyuye/C_Projects/EXTRAME-PRACTICE/iptable.csv");
    server_ip = SERVER_IP;
    for (int i = 0; i < doc.GetRowCount(); i++) {
        sub_ip_map[doc.GetCell<int>(1, i)] = doc.GetCell<std::string>(2, i);
    }
    return 0;
}

IP_ADDRESS Socket::get_ip(SUB_ID sub_id) {
    return sub_ip_map[sub_id];
}

Socket::Socket(int s_id) {
#if defined(_WIN32)
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
#endif
    init_ip();
    sockfd = socket(AF_INET, SOCK_STREAM,0 );
    if (sockfd < 0) {
        perror("socket error");
        exit(1);
    }
    if (s_id == 0) {
        // server socket
        struct sockaddr_in addr;
        addr.sin_family = AF_INET;
        addr.sin_port = htons(PORT);
        addr.sin_addr.s_addr = inet_addr(server_ip.c_str());
        if (bind(sockfd, (struct sockaddr *) &addr, sizeof(addr)) < 0) {
            perror("server socket error, unable to bind");
            return;
        }
    } else {
        struct sockaddr_in addr;
        addr.sin_family = AF_INET;
        addr.sin_port = htons(PORT);
        addr.sin_addr.s_addr = inet_addr(sub_ip_map[s_id].c_str());
        if (bind(sockfd, (struct sockaddr *) &addr, sizeof(addr)) < 0) {
            perror("client socket error, unable to bind");
            return;
        }
    }
}

Socket::~Socket() {
#if defined(_WIN32)
    closesocket(sockfd);
    WSACleanup();
#else
    close(sockfd);
#endif 
}