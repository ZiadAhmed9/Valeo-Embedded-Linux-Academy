#include "simpleLogger.h"

/*
Boost libraries from: https://github.com/gklingler/simpleLogger

Daemon logger application based on boost simpleLogger, message queue receiver, socket client.

Description :
            - designed to run in the background as a systemd service.
            - This application is used to log applications written in the config.txt found in config_lib/config.txt.
            - Logs are received through message queues and are written inside a log file.
            - Logs are sent to a socket server known as receiver application.
            - Supports logging for multiple applications

To use it:
          - Add the names of the application you want to log inside the config.txt
          - Restart your system afterwards

How it works:
            - This up runs in the background opening queues for applications that need message queues
            - If no applications are written inside the config.txt this program will sleep and will try to check the config.txt again
            - If no socket server is opened for logging the application will go on and write logs in the log file
            - It will constantly check for the socket server if it exists, if found it will start sending logs to it

Possible errors:
                -writing inside the config at the instance of checking can cause errors
                - Both Message queues and sockets are delicate and prone to mis-functioning
                - In case of erros when connecting to queue or sockets, check if the application is correctly compiled for your machine
                - Check for your server and port settings
                - Check your network connection

NOTE!!!!  to safely write inside the config while this app this running never save before making sure the user app name is correctly written
          If you typed the name wrong you should kindly reload the daemon or reboot your device
*/

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

// function to be used for the logs Check the boost documentation for more info
BOOST_LOG_GLOBAL_LOGGER_INIT(logger, src::severity_logger_mt)
{
    src::severity_logger_mt<boost::log::trivial::severity_level> logger;    // Severity loggger added
    logger.add_attribute("LineID", attrs::counter<unsigned int>(1));        // Lines are sequentially numbered
    logger.add_attribute("TimeStamp", attrs::local_clock());                // Each log line gets a timestamp
    typedef sinks::synchronous_sink<sinks::text_ostream_backend> text_sink; // Back end configuring
    boost::shared_ptr<text_sink> sink = boost::make_shared<text_sink>();    // sink created
    logging::formatter log_format = expr::stream                            // formaaat for the logs
                                    << std::setw(7) << std::setfill('0') << line_id << std::setfill(' ') << " | "
                                    << expr::format_date_time(timestamp, "%Y-%m-%d, %H:%M:%S.%f") << " "
                                    << "[" << logging::trivial::severity << "]"
                                    << " - " << expr::smessage;
    sink->set_formatter(log_format); // for the class sink pass the formatter created

    auto log_file = logging::add_file_log( // log file cofiguring variable created
        logkw::file_name = LOGFILE,
        logkw::rotation_size = MAX_FILE_SIZE); // Max file size here

    log_file->locked_backend()->set_file_collector( // log file class configuring
        sinks::file::make_collector(
            logkw::target = LOG_FILE_PATH));

    log_file->set_formatter(log_format); // log file formatting

    logging::core::get()->add_global_attribute("RotationCounter", attrs::counter<unsigned int>(0, 1));                   // Start from 0 and increment by 1
    logging::core::get()->add_global_attribute("RotationSize", attrs::constant<unsigned int>(1024));                     // Set the rotation size
    logging::core::get()->add_global_attribute("FileRotation", attrs::constant<unsigned int>(1));                        // Enable file rotation
    logging::core::get()->add_global_attribute("FileRotationPattern", attrs::constant<std::string>("%run%_%logs%.log")); // Set the file name pattern
    sink->set_filter(severity >= SEVERITY_THRESHOLD);
    logging::core::get()->add_sink(sink);
    logging::keywords::auto_flush = true;
    return logger;
}

// Main  function for the daemon logger

int main()
{
    /*Part 1 Variables used*/
    char mq_buffer[1024] = {0};          // Buffer for the message queue
    bool config_file_status = EMPTY;     // Bool that holds current state of the config.txt
    int number_of_queues = 0;            // Integer holding the number of programs in the config.txt
    int mq_state;                        // Integer holding the current state of the message queue
    int socket_state;                    // Integer holding the current state of the client socket
    string temp = {0};                   // tmp to conver from const char* to string
    vector<string> queue_names;          // vector to hold the name of the queues to be created
    vector<messageq_receiver> receivers; // vector holding the objects of the class "messageq_receiver" Message Queue Reciever

    /*Part 2 we parse the config.txt*/

    while (config_file_status) // Loop made to constantly check the config.txt for its contents
    {
        queue_names = read_config_file(config_file_path); // in this line I used my function to parse the config and hold it in
        if (queue_names.empty())                          // Check if the config file is empty,, report then try again after 5 seconds
        {
            cout << "No lines found in the config file." << endl;
            cout << "Checking again after 5 seconds." << endl;
            LOG_FATAL << "DAEMON LOGGER APP: Config file is empty!";
            boost::log::core::get()->flush();
            sleep(5);
        }
        else
        {
            config_file_status = OK;
            LOG_TRACE << "DAEMON LOGGER APP: config.txt is successfully parsed.";
            boost::log::core::get()->flush();
        }
    }
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
    case SOCKET_CLIENT_CONNECTED: // If the socket is connected successfully
        LOG_TRACE << "DAEMON LOGGER APP: Socket client connected to server.";
        break;
    case SOCKET_CLIENT_CONNECTION_ERROR: // If the socket has connection error
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
                int x = client.send(mq_buffer, sizeof(mq_buffer)); // Send the log through the socket to the server
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
