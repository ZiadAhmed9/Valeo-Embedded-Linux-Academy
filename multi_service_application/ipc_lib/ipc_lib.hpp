#ifndef IPC_LIB_HPP
#define IPC_LIB_HPP
#include <iostream>
#include <mqueue.h>
#include <cstring>
#include <cstdlib>
#include <cerrno>
using namespace std;
#define MAX_MESSAGE_SIZE 1024 // Macro holding max message size
#define MAX_MESSAGE_QUEUE 10  // Macro holding max queueing messages

typedef enum
{
    MQ_OK,
    MQ_CREATE_ERROR,
    MQ_CONNECTION_ERROR,
    MQ_SENDING_ERROR,
    MQ_RECEIVE_ERROR,
} messageq_state_type; // typedef of messageq status

/*
    Class for message queue receivers
*/
class messageq_receiver
{
private:
    mqd_t mq_descriptor; // message queue descriptor
    string name;         // string containing name of the queue

public:
    /*
    Constructor of the class messageq_receiver
    description: Creates message queue with read write create permissions
    arguments: takes string of the name of the queue
    */
    messageq_receiver(const string &queue_name);
    /*
    function name: messageq_receive_sync()
    description:  used by the receiver class to receive data through queue
    blocking:  busy waits on receiving
    returns: Status type from the status typdef
    */
    messageq_state_type messageq_receive_sync(char *buffer);
    /*
    function name: messageq_receive_async()
    description:  used by the receiver class to receive data through queue
    blocking:  waits for some seconds then exits in case no receiving
    returns: Status type from the status typdef
    */
    messageq_state_type messageq_receive_async(char *buffer);
    /*
    function name: current_queue_name()
    description:  used by the receiver class to receive data through queue
    blocking: Non
    returns:  String containing current queue name
    */
    string current_queue_name();
};

/*
    Class for Message queue sending objects
*/
class messageq_sender
{
private:
    mqd_t mq_descriptor;        //Message queue descriptor
    int mq_send_result;         //Message queue status after sending

public:
    /*
    function name: messageq_connect()
    description:  Used by sending class to connect to queue
    blocking:  non
    returns: Status type from the status typdef
    */
    messageq_state_type messageq_connect(const string &name);
    /*
    function name: messageq_send()
    description:  Used by sending class to send through queue
    blocking:  blocks until whole message is sent
    returns: Status type from the status typdef
    */
    messageq_state_type messageq_send(const string &message);
};

#endif