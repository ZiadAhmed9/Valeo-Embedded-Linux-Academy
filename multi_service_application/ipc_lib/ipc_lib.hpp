#ifndef IPC_LIB_HPP
#define IPC_LIB_HPP
#include <iostream>
#include <mqueue.h>
#include <cstring>
#include <cstdlib>
#include <cerrno>

using namespace std;
#define MAX_MESSAGE_SIZE 1024
#define MAX_MESSAGE_QUEUE 10

typedef enum
{
    MQ_OK,
    MQ_CREATE_ERROR,
    MQ_CONNECTION_ERROR,
    MQ_SENDING_ERROR,
    MQ_RECEIVE_ERROR,
} messageq_state_type;
class messageq_receiver
{
private:
    mqd_t mq_descriptor;

public:
    messageq_receiver();

    messageq_state_type messageq_create();

    messageq_state_type messageq_receive_sync(char *str);

    messageq_state_type messageq_receive_async();
};

class messageq_sender
{
private:
    mqd_t mq_descriptor;
    int mq_send_result;

public:
    messageq_sender();
    messageq_state_type messageq_connect();
    messageq_state_type messageq_send(const string &message);
};

#endif