#include "simpleLogger.h"
#include <boost/log/core/core.hpp>
#include <boost/log/expressions/formatters/date_time.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/sync_frontend.hpp>
#include <boost/log/sinks/text_ostream_backend.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/log/trivial.hpp>
#include <boost/core/null_deleter.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/make_shared.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/log/common.hpp>
#include <boost/log/sinks.hpp>
#include <boost/log/sources/logger.hpp>
#include <boost/log/utility/setup.hpp>
#include <random>
#include <fstream>
#include <ostream>
#include <iostream>
#include <unistd.h>
#include <signal.h>
#include "../ipc_lib/ipc_lib.hpp"
#include "../sockets_lib/sockets.hpp"
#include "config_parsing.hpp"
#define BOOST_LOG_USE_GLOBAL_LOGGER

// namespace variables to be used
namespace logging = boost::log;
namespace src = boost::log::sources;
namespace expr = boost::log::expressions;
namespace sinks = boost::log::sinks;
namespace attrs = boost::log::attributes;
namespace logkw = logging::keywords;

// attributes for logs
BOOST_LOG_ATTRIBUTE_KEYWORD(line_id, "LineID", unsigned int)
BOOST_LOG_ATTRIBUTE_KEYWORD(timestamp, "TimeStamp", boost::posix_time::ptime)
BOOST_LOG_ATTRIBUTE_KEYWORD(severity, "Severity", logging::trivial::severity_level)

// function to be used for the logs
BOOST_LOG_GLOBAL_LOGGER_INIT(logger, src::severity_logger_mt)
{
    src::severity_logger_mt<boost::log::trivial::severity_level> logger;

    // add attributes
    logger.add_attribute("LineID", attrs::counter<unsigned int>(1)); // lines are sequentially numbered
    logger.add_attribute("TimeStamp", attrs::local_clock());         // each log line gets a timestamp

    // adjusting sink
    typedef sinks::synchronous_sink<sinks::text_ostream_backend> text_sink;
    boost::shared_ptr<text_sink> sink = boost::make_shared<text_sink>();

    logging::formatter formatter = expr::stream
                                   << setw(7) << setfill('0') << line_id << setfill(' ') << " | "
                                   << expr::format_date_time(timestamp, "%Y-%m-%d, %H:%M:%S.%f") << " "
                                   << "[" << logging::trivial::severity << "]"
                                   << " - " << expr::smessage;
    sink->set_formatter(formatter);

    logging::add_file_log("/home/ziad/test1/Valeo-Embedded-Linux-Academy/multi_service_application/build/run_logs.txt", logkw::open_mode = ios::app)
        ->set_formatter(formatter);

    // only messages with severity >= SEVERITY_THRESHOLD are written
    sink->set_filter(severity >= SEVERITY_THRESHOLD);

    // "register" our sink
    logging::core::get()->add_sink(sink);
    logging::keywords::auto_flush = true;
    return logger;
}

// Main  function for the daemon logger

int main()
{
    /*Part 1 Variables used*/
    char mq_buffer[1024] = {0};          // Buffer for the message queue
    int number_of_queues = 0;            // Integer holding the number of programs in the config.txt
    int mq_state;                        // Integer holding the current state of the message queue
    int socket_state;                    // Integer holding the current state of the client socket
    string temp = {0};                   // tmp to conver from const char* to string
    vector<string> queue_names;          // vector to hold the name of the queues to be created
    vector<messageq_receiver> receivers; // vector holding the objects of the class "messageq_receiver" Message Queue Reciever

    /*Part 2 we parse the config.txt*/

    queue_names = read_config_file(config_file_path); // in this line I used my function to parse the config and hold it in
    if (queue_names.empty())                          // Check if the config file is empty,, report then exit
    {
        cout << "No lines found in the config file." << endl;
        LOG_FATAL << "DAEMON LOGGER APP: Config file is empty!";
        return 1;
    }
    LOG_TRACE << "DAEMON LOGGER APP: config.txt is successfully parsed.";
    boost::log::core::get()->flush();

    /*Part 3 We create the vector carrying objects of the messag queue receiver class*/

    for (const string &name : queue_names) // Loop through the vector containing names of the queues to be created
    {
        messageq_receiver messageq_receiver_obj(name); // Create object of the the class messageq_receiver and name it with corresponding app name
        receivers.push_back(messageq_receiver_obj);    // Pushback the object created into the vector
        number_of_queues++;                            // each time you loop increment the variable holding number of queues
    }
    LOG_TRACE << "DAEMON LOGGER APP: Vector containing classes created.";
    boost::log::core::get()->flush();

    /*Part 4 start creating the client to start socket programming*/

    TCP_client client(SOCKET_IP, SOCKET_PORT); // Here we instantiated an object of the class TCP_client
    socket_state = client.connect_2server();   // Try to connect to server

    switch (socket_state) // Switch on status and perform accordingly
    {
    case SOCKET_CLIENT_CONNECTED:
        LOG_TRACE << "DAEMON LOGGER APP: Socket client connected to server.";
        break;
    case SOCKET_CLIENT_CONNECTION_ERROR:
        LOG_ERROR << "DAEMON LOGGER APP: Socket client failed to connected to server.";
    }
    boost::log::core::get()->flush();

    /*Part 5 Infinite Loop*/

    for (;;)
    {
        for (int i = 0; i < number_of_queues; i++) // Loop through vector that contains objects created
        {
            // memset(mq_buffer,0,sizeof(mq_buffer));
            mq_state = receivers[i].messageq_receive_async(mq_buffer); // For this current receiver queue check the contents of the queue

            if (mq_state == MQ_OK) // If the message queue receive finds data sent through the queue then go on
            {
                temp = mq_buffer;  // store the char* inside a temporary string for logging
                LOG_TRACE << temp; // Write the log in the log file
                boost::log::core::get()->flush();
            }
            else // else Log an error message that the queue is empty or no data is received
            {
                LOG_ERROR << "DAEMON LOGGER APP: No data received from message queue named " << receivers[i].current_queue_name();
                boost::log::core::get()->flush();
            }
            if (socket_state == SOCKET_CLIENT_CONNECTED && mq_state == MQ_OK) // Check the current status of the
            {
                int x=client.send(mq_buffer, sizeof(mq_buffer)); // Send the log through the socket to the server
                LOG_TRACE << "DAEMON LOGGER APP: Socket client connected to server and logs are sent to it.";
                boost::log::core::get()->flush();
            }
        }
        if (socket_state == SOCKET_CLIENT_CONNECTION_ERROR) // Check if the socket is not connected and try to connect to it again
        {
            LOG_ERROR << "DAEMON LOGGER APP: Socket client is not connected to server retrying again ...";
            boost::log::core::get()->flush();
            socket_state = client.connect_2server();
        }
        sleep(1);
    }
    return 0;
}
