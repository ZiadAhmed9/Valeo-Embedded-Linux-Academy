#include "../sockets_lib/sockets.hpp"
using namespace std;

/*server app
objective : receive logs from the machine running the daemon logger through sockets
*/

int main()
{
    int state;  //integer holding current client state
    char socket_buffer[SOCKET_BUFFER_SIZE]; //buffer for socket client
    TCP_server server(SOCKET_PORT); // object of the class TCP server and pass it the port
    cout << "server is listening on port:" << SOCKET_PORT << endl;
    for(;;)
    {
        if (server.accept_client()) // Check if a client is accepted to the server
        {
            cout << "client accepted by server" << endl;
            for(;;)
            {
                ssize_t last_byte = server.receive(socket_buffer, sizeof(socket_buffer)); // read the socket and store the date in socket_buffer
                socket_buffer[last_byte] = '/0';                                          // double checking the last element in the buffer is the null
                cout << "Log received: " << socket_buffer << endl;
            }
        }
    }
    return 0;
}
