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
    string name;
public:
    messageq_receiver(const std::string &queue_name);

    messageq_state_type messageq_create(const std::string &name);

    messageq_state_type messageq_receive_sync(char *buffer);

    messageq_state_type messageq_receive_async(char *buffer);
};

class messageq_sender
{
private:
    mqd_t mq_descriptor;
    int mq_send_result;

public:
    messageq_sender();
    messageq_state_type messageq_connect(const std::string& name);
    messageq_state_type messageq_send(const string &message);
};

#endif