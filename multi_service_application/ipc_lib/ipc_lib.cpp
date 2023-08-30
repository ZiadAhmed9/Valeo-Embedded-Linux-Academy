#include "ipc_lib.hpp"

using namespace std;

messageq_receiver ::messageq_receiver()
{
    mq_unlink("/myqueue");
}
messageq_state_type messageq_receiver::messageq_create()
{
    struct mq_attr mq_attributes;
    mq_attributes.mq_maxmsg = MAX_MESSAGE_QUEUE;
    mq_attributes.mq_msgsize = MAX_MESSAGE_SIZE;
    mq_descriptor = mq_open("/myqueue", O_CREAT | O_RDWR, 0666, &mq_attributes);
    if (mq_descriptor == -1)
    {
        cout << "mq_not created"<<endl;
        return MQ_CREATE_ERROR;
    }
    return MQ_OK;
}

messageq_state_type messageq_receiver::messageq_receive_sync(char *buffer)
{
    unsigned int priority;
    ssize_t last_byte = mq_receive(mq_descriptor, buffer, MAX_MESSAGE_SIZE, &priority);
    if (last_byte == -1)
    {
        cout << "receiver error";
        return MQ_RECEIVE_ERROR;
    }
    cout << "hi there";
    buffer[last_byte] = '\0';
    cout << buffer << endl;
    return MQ_OK;
}

messageq_sender ::messageq_sender()
{
}

messageq_state_type messageq_sender::messageq_connect()
{
    mq_descriptor = mq_open("/myqueue", O_RDWR);
    if (mq_descriptor == -1)
    {
        cout << "not connected";
        return MQ_CONNECTION_ERROR;
    }
    cout << "connected";
    return MQ_OK;
}

messageq_state_type messageq_sender::messageq_send(const string &message)
{
    if (mq_descriptor == -1)
    {
        cout << "mq is not found in sending";
        return MQ_SENDING_ERROR;
    }
    mq_send_result = mq_send(mq_descriptor, message.c_str(), message.size(), 0);
    cout << "mq sent";
    if (mq_send_result == -1)
    {
        return MQ_SENDING_ERROR;
    }
    return MQ_OK;
}
