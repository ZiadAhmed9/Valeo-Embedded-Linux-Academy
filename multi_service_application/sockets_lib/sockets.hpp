
#ifndef SOCKET_LIBRARY_H
#define SOCKET_LIBRARY_H

#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <cerrno>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>


class TCP_server {
private:
    int server_socket;
    int client_socket;
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;

public:
    TCP_server(int port);
    ~TCP_server();

    bool accept_client();
    ssize_t send(const char* data, size_t length);
    ssize_t receive(char* buffer, size_t buffer_size);
};

class TCP_client {
private:
    int client_socket;
    struct sockaddr_in server_addr;

public:
    TCP_client(const std::string& server_IP, int server_port);
    //~TCP_client();

    bool connect_2server();
    ssize_t send(const char* data, size_t length);
    ssize_t receive(char* buffer, size_t buffer_size);
};

#endif 
