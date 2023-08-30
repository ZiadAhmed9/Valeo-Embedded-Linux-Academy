// socket_library.cpp
#include "sockets.hpp"


TCP_server::TCP_server(int port) {


    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        std::cerr << "Socket creation failed" << std::endl;
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        std::cerr << "Binding failed" << std::endl;
        exit(EXIT_FAILURE);
    }

    if (listen(server_socket, 5) == -1) {
        std::cerr << "Listening failed" << std::endl;
        exit(EXIT_FAILURE);
    }
}

TCP_server::~TCP_server() {

    close(server_socket);
}

bool TCP_server::accept_client() {
    socklen_t client_addr_len = sizeof(client_addr);
    client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &client_addr_len);
    if (client_socket == -1) {
        std::cerr << "Client acceptance failed" << std::endl;
        return 0;
    }
    return 1;
}

ssize_t TCP_server::send(const char* data, size_t length) {
    return ::send(client_socket, data, length, 0);
}

ssize_t TCP_server::receive(char* buffer, size_t buffer_size) {
    return ::recv(client_socket, buffer, buffer_size, 0);
}

TCP_client::TCP_client(const std::string& server_IP, int server_port) {

    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        std::cerr << "Socket creation failed" << std::endl;
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(server_port);
    server_addr.sin_addr.s_addr = inet_addr(server_IP.c_str());
}

bool TCP_client::connect_2server() {
    if (connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        std::cerr << "Connection failed" << std::endl;
        return 0;
    }
    return 1;
}

ssize_t TCP_client::send(const char* data, size_t length) {
    return ::send(client_socket, data, length, 0);
}

ssize_t TCP_client::receive(char* buffer, size_t bufferSize) {
    return ::recv(client_socket, buffer, bufferSize, 0);
}
