#include "ipc_lib.hpp"

using namespace std;

messageq_receiver ::messageq_receiver(const string &name)
{
    this -> name=name;
    //setting attributes
    struct mq_attr mq_attributes;
    mq_attributes.mq_maxmsg = MAX_MESSAGE_QUEUE;
    mq_attributes.mq_msgsize = MAX_MESSAGE_SIZE;
    mq_descriptor = mq_open(name.c_str(), O_CREAT | O_RDWR, 0666, &mq_attributes);
    if (mq_descriptor == -1)
    {
        cout << "message queue descriptor error for " << name.c_str() << endl;
    }
    cout << "created queue with name " << name.c_str() << endl;
}
// messageq_state_type messageq_receiver::messageq_create(const std::string &name)
// {
//     struct mq_attr mq_attributes;
//     mq_attributes.mq_maxmsg = MAX_MESSAGE_QUEUE;
//     mq_attributes.mq_msgsize = MAX_MESSAGE_SIZE;
//     mq_descriptor = mq_open(name.c_str(), O_CREAT | O_RDWR, 0666, &mq_attributes);

//     return MQ_OK;
// }

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

messageq_state_type messageq_receiver::messageq_receive_async(char *buffer)
{
    unsigned int priority;
    //setting time out
    struct timespec timeout;
    timeout.tv_sec = time(NULL) + 10;
    timeout.tv_nsec = 0;
    ssize_t last_byte = mq_timedreceive(mq_descriptor, buffer, MAX_MESSAGE_SIZE, &priority,&timeout);
    if (last_byte == -1)
    {
        cout << name;
        cerr<<"Recieve error:";
        cout << "receiver error";
        return MQ_RECEIVE_ERROR;
    }
    buffer[last_byte] = '\0';
    cout << buffer << endl;
    return MQ_OK;
}

messageq_sender ::messageq_sender()
{
}

messageq_state_type messageq_sender::messageq_connect(const std::string &name)
{
    mq_descriptor = mq_open(name.c_str(), O_RDWR);
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
