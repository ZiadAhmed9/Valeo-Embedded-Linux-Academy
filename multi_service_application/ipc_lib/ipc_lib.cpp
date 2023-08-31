#include "ipc_lib.hpp"
#include "../simple_logger/simpleLogger.h"

/*
    Library providing message queue APIs
    Class: 1 class for sender and another for receiver
*/

using namespace std;

/*
Constructor of the class messageq_receiver
description: Creates message queue with read write create permissions
arguments: takes string of the name of the queue
*/
messageq_receiver ::messageq_receiver(const string &name)
{
    this->name = name; // Store the name passed from the object to the private variable name
    // setting attributes
    struct mq_attr mq_attributes;                                                  // Struct containing attributes
    mq_attributes.mq_maxmsg = MAX_MESSAGE_QUEUE;                                   // setting max message queues
    mq_attributes.mq_msgsize = MAX_MESSAGE_SIZE;                                   // setting max message size
    mq_descriptor = mq_open(name.c_str(), O_CREAT | O_RDWR, 0666, &mq_attributes); // Acquiring the message queue descriptor
    if (mq_descriptor == -1)                                                       // check for erros in descriptor
    {
        cout << "Error while acquiring descriptor for queue named " << name.c_str() << endl;
    }
    cout << "Created message queue with name " << name.c_str() << endl;
}
/*
function name: messageq_receive_sync()
description:  used by the receiver class to receive data through queue
blocking:  busy waits on receiving
returns: Status type from the status typdef
 */
messageq_state_type messageq_receiver::messageq_receive_sync(char *buffer)
{
    unsigned int priority;                                                              // unsigned int holding priority
    ssize_t last_byte = mq_receive(mq_descriptor, buffer, MAX_MESSAGE_SIZE, &priority); // Receive data from queue and store in buffer
    if (last_byte == -1)                                                                // Check for receiving error
    {
        cout << "Message queue receiving error in queue named " << name.c_str();
        return MQ_RECEIVE_ERROR;
    }
    buffer[last_byte] = '\0'; // ensure last element is null
    return MQ_OK;
}
/*
function name: messageq_receive_async()
description:  used by the receiver class to receive data through queue
blocking:  waits for some seconds then exits in case no receiving
returns: Status type from the status typdef
*/
messageq_state_type messageq_receiver::messageq_receive_async(char *buffer)
{
    unsigned int priority;
    // setting time out
    struct timespec timeout;         // struct for timeout
    timeout.tv_sec = time(NULL) + 1; // wait 1 second timeout
    timeout.tv_nsec = 0;
    ssize_t last_byte = mq_timedreceive(mq_descriptor, buffer, MAX_MESSAGE_SIZE, &priority, &timeout); // using timed receive wait 1 second then proceed
    if (last_byte == -1)
    {
        return MQ_RECEIVE_ERROR;
    }
    buffer[last_byte] = '\0';
    // cout << buffer << endl;
    return MQ_OK;
}
/*
function name: current_queue_name()
description:  used by the receiver class to receive data through queue
blocking: Non
returns:  String containing current queue name
*/
std::string messageq_receiver::current_queue_name()
{
    return name;
}

/*
function name: messageq_connect()
description:  Used by sending class to connect to queue
blocking:  non
returns: Status type from the status typdef
*/
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
/*
function name: messageq_send()
description:  Used by sending class to send through queue
blocking:  blocks until whole message is sent
returns: Status type from the status typdef
*/
messageq_state_type messageq_sender::messageq_send(const string &message)
{
    if (mq_descriptor == -1) // checking if descriptor is valid
    {
        cerr<<"Message queue sending error";
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
