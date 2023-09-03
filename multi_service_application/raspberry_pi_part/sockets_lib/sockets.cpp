#include "sockets.hpp"
using namespace std;
/*
Constructor of the class TCP_server
description: Creates the server, bind it, then start listening
*/
TCP_server::TCP_server(int port)
{
    // get the file descriptor of the socket after created
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) // check for creation errors
    {
        cerr << "Socket creation failed" << endl;
        exit(EXIT_FAILURE);
    }
    // below is the attributes of the server socket
    server_addr.sin_family = AF_INET;         // use IPV4
    server_addr.sin_port = htons(port);       // port of the socket
    server_addr.sin_addr.s_addr = INADDR_ANY; // accept any requests

    // Bind to server socket, and check for binding error
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
    {
        cerr << "Binding failed" << endl;
        exit(EXIT_FAILURE);
    }
    // wait for clients and check for error when listening
    if (listen(server_socket, 5) == -1)
    {
        cerr << "Listening failed" << endl;
        exit(EXIT_FAILURE);
    }
}
/*
Destructor of the class TCP_server
description: Closes the socket after finishing
*/
TCP_server::~TCP_server()
{

    close(server_socket);
}
/*
function name: accept_client()
description:  used by the server to checks if client is accepted by the server
blocking:   non
returns: bool -> 1 if accepted,  0 if no clients accepted
*/
bool TCP_server::accept_client()
{
    socklen_t client_addr_len = sizeof(client_addr); // variable holding socket address length
    // get the file descriptor of socket
    client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_addr_len);
    if (client_socket == -1)
    {
        cerr << "Client acceptance failed" << endl;
        return 0;
    }
    return 1;
}
/*
function name: send()
description:  used by the server to send
blocking:  Blocks other apps until it finishes sending
returns: number sent in case of success or -1 in case of failure
*/
ssize_t TCP_server::send(const char *data, size_t length)
{
    return ::send(client_socket, data, length, 0);
}
/*
function name: receive()
description:  used by the server to receive
blocking:  Blocks other apps until it finishes sending
returns: number sent in case of success or -1 in case of failure
*/
ssize_t TCP_server::receive(char *buffer, size_t buffer_size)
{
    return ::recv(client_socket, buffer, buffer_size, 0);
}

/*
Constructor of the class TCP_client
description: Get the socket descriptor, sets attributes
*/

TCP_client::TCP_client(const string &server_IP, int server_port)
{
    // getting the descriptor then cheking for erros
    // AF_INET-> IPV4
    // SOCK_STREAM -> used by TCP and UDP
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1)
    {
        cerr << "Socket creation failed" << endl;
        exit(EXIT_FAILURE);
    }
    // Attributes
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(server_port);
    server_addr.sin_addr.s_addr = inet_addr(server_IP.c_str());
}
/*
function name: connect_2server()
description:  used by the client to connect to server
blocking:  blocks only while inside the function until it is done, in case the conenction failed it won't block
returns: type retruned -> socket_client_status_type
*/
socket_client_status_type TCP_client::connect_2server()
{
    // Connect the client to the server and check if return is -1
    //-1 means either failure in network or server is non existing
    if (connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
    {
        return SOCKET_CLIENT_CONNECTION_ERROR;
    }
    return SOCKET_CLIENT_CONNECTED;
}
/*
function name: send()
description:  used by the server to send
blocking:  Blocks other apps until it finishes sending
returns: number sent in case of success or -1 in case of failure
*/
ssize_t TCP_client::send(const char *data, size_t length)
{
    return ::send(client_socket, data, length, 0); // returns the size of the buffer
}
ssize_t send(const char *data, size_t length);
/*
function name: receive()
description:  used by the server to receive
blocking:  Blocks other apps until it finishes sending
returns: number sent in case of success or -1 in case of failure
*/
ssize_t TCP_client::receive(char *buffer, size_t bufferSize)
{
    return ::recv(client_socket, buffer, bufferSize, 0); // returns the size of the buffer
}
