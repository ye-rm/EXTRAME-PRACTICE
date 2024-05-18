#include "socket.h"
#include <iostream>

int Socket::init_ip() {
    rapidcsv::Document doc("/root/projects/EXTRAME-PRACTICE/room_msg.csv");
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
    init_ip();
    LOG_F(INFO, "Socket init for %d", s_id);
#if defined(_WIN32)
    //same as below, work on windows
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        perror("WSAStartup error");
        exit(1);
    }
    sockfd=INVALID_SOCKET;
    sockfd=socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == INVALID_SOCKET) {
        perror("socket create error");
        return;
    }
    if (s_id == 0) {
        // server socket
        socket_ip = server_ip;
        struct sockaddr_in addr{};
        addr.sin_family = AF_INET;
        addr.sin_port = htons(PORT);
        addr.sin_addr.s_addr = inet_addr(server_ip.c_str());
        if (bind(sockfd, (struct sockaddr *) &addr, sizeof(addr)) < 0) {
            perror("server socket error, unable to bind");
            return;
        }
    }else {
        socket_ip = sub_ip_map[s_id];
        struct sockaddr_in addr{};
        addr.sin_family = AF_INET;
        addr.sin_port = htons(PORT);
        addr.sin_addr.s_addr = inet_addr(socket_ip.c_str());
        if (bind(sockfd, (struct sockaddr *) &addr, sizeof(addr)) < 0) {
            perror("client socket error, unable to bind");
            return;
        }
    }
#else
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("socket create error");
        exit(1);
    }
    if (s_id == 0) {
        // server socket
        socket_ip = server_ip;
        struct sockaddr_in addr{};
        addr.sin_family = AF_INET;
        addr.sin_port = htons(PORT);
        addr.sin_addr.s_addr = inet_addr(server_ip.c_str());
        if (bind(sockfd, (struct sockaddr *) &addr, sizeof(addr)) < 0) {
            LOG_F(ERROR, "server socket error, unable to bind");
            return;
        }
    } else {
        socket_ip = sub_ip_map[s_id];
        struct sockaddr_in addr{};
        addr.sin_family = AF_INET;
        addr.sin_port = htons(PORT);
        addr.sin_addr.s_addr = inet_addr(socket_ip.c_str());
        if (bind(sockfd, (struct sockaddr *) &addr, sizeof(addr)) < 0) {
            LOG_F(ERROR, "client socket error, unable to bind");
            return;
        }
    }
#endif
//    LOG_F(INFO, "Socket %d init success for %d", sockfd, s_id);
}

Socket::~Socket() {
#if defined(_WIN32)
    closesocket(sockfd);
    WSACleanup();
#else
    close(sockfd);
#endif
    //delete all messages
    while (!received.empty()) {
        received.pop();
    }
    //delete all threads
    listen_flag = false;
    if (listen_thread.joinable()) {
        listen_thread.join();
    }
}

int Socket::listen_server() {
    listen_flag = true;
    listen_thread = std::thread(&Socket::listen_thread_func, this);
//    LOG_F(INFO, "Socket %d listen server", sockfd);
    return 0;
}

int Socket::listen_client() {
    listen_flag = true;
    listen_thread = std::thread(&Socket::listen_thread_func, this);
//    LOG_F(INFO, "Socket %d listen client", sockfd);
    return 0;
}

void Socket::listen_thread_func() {
    while (listen_flag) {
        struct sockaddr_in client_addr{};
        socklen_t len = sizeof(client_addr);
        message to_store{};
#ifdef _WIN32
        if(recvfrom(sockfd, (char *)msg, sizeof(message), 0, (struct sockaddr *) &client_addr, &len)==SOCKET_ERROR){
            LOG_F(WARNING, "recvfrom error");
            return;
        }
#else
        if (recvfrom(sockfd, &to_store, sizeof(message), 0, (struct sockaddr *) &client_addr, &len) < 0) {
            LOG_F(WARNING, "recvfrom error");
            return;
        }
#endif
        mutex.lock();
        received.push(to_store);
        mutex.unlock();
//        LOG_F(INFO, "Socket %d received from %s", sockfd, inet_ntoa(client_addr.sin_addr));
//        LOG_F(INFO, "received msg sub_id :%d, para:%f", to_store.sub_id, to_store.paramter);
    }
}

int Socket::send_to_server(message msg) {
    //send msg to server_ip
    struct sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr(server_ip.c_str());
    message tosend = msg;
#ifdef _WIN32
    if (sendto(sockfd, (char *)msge, sizeof(message), 0, (struct sockaddr *) &server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
        LOG_F(WARNING, "sendto server error");
        return -1;
    }
#else
    if (sendto(sockfd, &tosend, sizeof(message), 0, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) {
        LOG_F(WARNING, "sendto server error");
        return -1;
    }
#endif
//    LOG_F(INFO, "sub %d send to server", msg.sub_id);
    return 0;
}

int Socket::send_to_client(int sub_id, message msg) {
    //send msg to sub_id
    struct sockaddr_in client_addr{};
    client_addr.sin_family = AF_INET;
    client_addr.sin_port = htons(PORT);
    client_addr.sin_addr.s_addr = inet_addr(sub_ip_map[sub_id].c_str());
    message tosend = msg;
#ifdef _WIN32
    if (sendto(sockfd, (char *)msge, sizeof(message), 0, (struct sockaddr *) &client_addr, sizeof(client_addr)) == SOCKET_ERROR) {
        LOG_F(WARNING, "%d sendto error",sub_id);
        return -1;
    }
#else
    if (sendto(sockfd, &tosend, sizeof(message), 0, (struct sockaddr *) &client_addr, sizeof(client_addr)) < 0) {
        LOG_F(WARNING, "%d sendto error", sub_id);
        return -1;
    }
#endif
//    LOG_F(INFO, "server send to sub %d", sub_id);
    return 0;
}

int Socket::stop_listen() {
    listen_flag = false;
    return 0;
}

int Socket::get_msg_queue_and_clear(std::queue<message> &msg_queue) {
    mutex.lock();
    while (!received.empty()) {
        msg_queue.push(received.front());
        received.pop();
    }
    mutex.unlock();
    return 0;
}
