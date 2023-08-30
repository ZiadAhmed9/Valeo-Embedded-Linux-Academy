#include "../sockets_lib/sockets.hpp"
#define PORT 5000
#define BUFFER_SIZE 1024
using namespace std;

int main()
{
    char buffer[BUFFER_SIZE];
    TCP_server server(PORT);
    cout << "server is listening on port:" << PORT << endl;
    while (1)
    {
        if (server.accept_client())
        {
            cout << "client accepted by server" << endl;
            ssize_t last_byte = server.receive(buffer, sizeof(buffer));
            buffer[last_byte] = '/0';
            cout << "Log received: " << buffer << endl;
        }
        sleep(1);
    }
    return 0;
}
