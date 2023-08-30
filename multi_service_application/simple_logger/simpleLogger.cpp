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
#define BOOST_LOG_USE_GLOBAL_LOGGER

namespace logging = boost::log;
namespace src = boost::log::sources;
namespace expr = boost::log::expressions;
namespace sinks = boost::log::sinks;
namespace attrs = boost::log::attributes;
namespace logkw = logging::keywords;

BOOST_LOG_ATTRIBUTE_KEYWORD(line_id, "LineID", unsigned int)
BOOST_LOG_ATTRIBUTE_KEYWORD(timestamp, "TimeStamp", boost::posix_time::ptime)
BOOST_LOG_ATTRIBUTE_KEYWORD(severity, "Severity", logging::trivial::severity_level)

BOOST_LOG_GLOBAL_LOGGER_INIT(logger, src::severity_logger_mt)
{
    src::severity_logger_mt<boost::log::trivial::severity_level> logger;

    // add attributes
    logger.add_attribute("LineID", attrs::counter<unsigned int>(1)); // lines are sequentially numbered
    logger.add_attribute("TimeStamp", attrs::local_clock());         // each log line gets a timestamp

    typedef sinks::synchronous_sink<sinks::text_ostream_backend> text_sink;
    boost::shared_ptr<text_sink> sink = boost::make_shared<text_sink>();

    logging::formatter formatter = expr::stream
                                   << std::setw(7) << std::setfill('0') << line_id << std::setfill(' ') << " | "
                                   << expr::format_date_time(timestamp, "%Y-%m-%d, %H:%M:%S.%f") << " "
                                   << "[" << logging::trivial::severity << "]"
                                   << " - " << expr::smessage;
    sink->set_formatter(formatter);

    logging::add_file_log("/home/ziad/test1/Valeo-Embedded-Linux-Academy/multi_service_application/build/run_logs.txt", logkw::open_mode = std::ios::app)
        ->set_formatter(formatter);

    // only messages with severity >= SEVERITY_THRESHOLD are written
    sink->set_filter(severity >= SEVERITY_THRESHOLD);

    // "register" our sink
    logging::core::get()->add_sink(sink);
    logging::keywords::auto_flush = true;
    return logger;
}

std::vector<std::string> read_config_file(const std::string &filename)
{
    std::vector<std::string> lines;
    std::ifstream configFile(filename);
    if (!configFile.is_open())
    {
        std::cerr << "Error opening config file: " << filename << std::endl;
        return lines;
    }

    std::string line;
    while (std::getline(configFile, line))
    {
        line = "/" + line;
        lines.push_back(line);
    }

    configFile.close();
    return lines;
}

int main()
{
    int number_of_queues = 0;
    const string CONFIG_FILE = "/home/ziad/test1/Valeo-Embedded-Linux-Academy/multi_service_application/config_lib/config.txt";
    vector<string> queue_names = read_config_file(CONFIG_FILE);
    if (queue_names.empty())
    {
        std::cout << "No lines found in the config file." << std::endl;
    }
    else
    {
        std::cout << "Read " << queue_names.size() << "lines from the config file:" << std::endl;
        for (const std::string &line : queue_names)
        {
            std::cout << line << std::endl;
        }
    }
    vector<messageq_receiver> receivers;
    for (const std::string &name : queue_names)
    {
        messageq_receiver messageq_receiver_obj(name);
        receivers.push_back(messageq_receiver_obj);
        number_of_queues++;
    }
    messageq_receiver queue("/myqueue");
    TCP_client client("127.0.0.1",5000);
    if(!client.connect_2server())
    {
        cout<<"Client failed to connect to socket"<<endl;
        LOG_FATAL<<"Client failed to connect to socket"<<endl;
        boost::log::core::get()->flush();
        return 1;
    }
    LOG_TRACE<<"Socket client connected to server.";
    cout<<"Socket client connected to server."<<endl;
    char mq_buffer[1024] = {0};
    string test = {0};
    boost::log::core::get()->flush();
    // for (const std::string &queue_name : queue_names)
    // {
    //     messageq_state_type state = logger_daemon.messageq_create(queue_name);
    //     if (state == MQ_CREATE_ERROR)
    //     {
    //         cout << "failed to create message queue for " << queue_name << endl;
    //         LOG_FATAL << "failed to create message queue";
    //         return 1;
    //     }
    //     cout << "Created queue for " << queue_name << endl;
    //     LOG_TRACE << "failed to create message queue " << queue_name;
    // }
    // messageq_state_type state = logger_daemon.messageq_create("/myqueue");
    // if (state == MQ_CREATE_ERROR)
    // {
    //     cout << "failed to create message queue" << endl;
    //     LOG_FATAL << "failed to create message queue" << endl;
    //     // return 1;
    // }
    // cout << "created message queue" << endl;
    // messageq_state_type state;
    int state;
    while (1)
    {
        for (int i = 0; i < number_of_queues; i++)
        {
            state = receivers[i].messageq_receive_async(mq_buffer);
            cout<<mq_buffer;
            test = mq_buffer;
            cout << test << endl;
            LOG_ERROR << test;
            boost::log::core::get()->flush();
            client.send(mq_buffer,sizeof(mq_buffer));
        }
        // state = queue.messageq_receive_sync(mq_buffer);
    }
    return 0;
}
