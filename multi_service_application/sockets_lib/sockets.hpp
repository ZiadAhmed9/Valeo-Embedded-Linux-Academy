
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

// Macros
#define SOCKET_PORT 5000           //Holding port number
#define SOCKET_IP "192.168.1.3"       //Holding IP address as string
#define SOCKET_BUFFER_SIZE 1024     //Buffer size of socket

/*Types created*/
typedef enum
{
    SOCKET_CLIENT_CONNECTED,
    SOCKET_CLIENT_CONNECTION_ERROR
} socket_client_status_type; // will use this to check current status of the client in the logger

/*Classes*/
// class for sockets TCP clients
class TCP_server
{
private:
    int server_socket;              // integer holding file descriptor in the server
    int client_socket;              // integer holding file descriptor in the client
    struct sockaddr_in server_addr; // struct contains attributes of the server
    struct sockaddr_in client_addr; // struct contains attributes of the client

public:
    /*
    Constructor of the class TCP_server
    description: Creates the server, bind it, then start listening
    */
    TCP_server(int port);
    /*
    Destructor of the class TCP_server
    description: Closes the socket after finishing
    */
    ~TCP_server();
    /*
    function name: accept_client()
    description:  used by the server to checks if client is accepted by the server
    blocking:   non
    returns: bool -> 1 if accepted,  0 if no clients accepted
    */
    bool accept_client();
    /*
    function name: send()
    description:  used by the server to send
    blocking:  Blocks other apps until it finishes sending
    returns: number sent in case of success or -1 in case of failure
    */
    ssize_t send(const char *data, size_t length);
    /*
    function name: receive()
    description:  used by the server to receive
    blocking:  Blocks other apps until it finishes sending
    returns: number sent in case of success or -1 in case of failure
    */
    ssize_t receive(char *buffer, size_t buffer_size);
};
// class for sockets TCP clients
class TCP_client
{
private:
    int client_socket;              // integer holding socket descriptor
    struct sockaddr_in server_addr; // struct contains attributes of server

public:
    TCP_client(const std::string &server_IP, int server_port);
    /*
    function name: connect_2server()
    description:  used by the client to connect to server
    blocking:  blocks only while inside the function until it is done, in case the conenction failed it won't block
    returns: type retruned -> socket_client_status_type
    */
    socket_client_status_type connect_2server();
    /*
    function name: send()
    description:  used by the server to send
    blocking:  Blocks other apps until it finishes sending
    returns: number sent in case of success or -1 in case of failure
    */
    ssize_t send(const char *data, size_t length);
    /*
    function name: receive()
    description:  used by the server to receive
    blocking:  Blocks other apps until it finishes sending
    returns: number sent in case of success or -1 in case of failure
    */
    ssize_t receive(char *buffer, size_t buffer_size);
};

#endif
