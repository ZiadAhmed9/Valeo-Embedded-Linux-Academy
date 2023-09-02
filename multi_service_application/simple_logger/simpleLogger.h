#ifndef simpleLogger_h__
#define simpleLogger_h__

/*Libraries and other dependencies*/
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
#include <boost/log/trivial.hpp>
#include <boost/log/sources/global_logger_storage.hpp>

/*Macros an other utilities*/

#define BOOST_LOG_USE_GLOBAL_LOGGER
#define BOOST_LOG_DYN_LINK // necessary when linking the boost_log library dynamically
#define LOG_FILE_PATH "/home/ziad/test1/Valeo-Embedded-Linux-Academy/multi_service_application/logs"
#define MAX_FILE_SIZE 1024
#define EMPTY 1
#define OK  0
// name of the log file
#define LOGFILE "run_logs.txt"

// just log messages with severity >= SEVERITY_THRESHOLD are written
#define SEVERITY_THRESHOLD logging::trivial::warning

// register a global logger
BOOST_LOG_GLOBAL_LOGGER(logger, boost::log::sources::severity_logger_mt<boost::log::trivial::severity_level>)

// just a helper macro used by the macros below - don't use it in your code
#define LOG(severity) BOOST_LOG_SEV(logger::get(),boost::log::trivial::severity)

// ===== log macros =====
#define LOG_TRACE   LOG(trace)
#define LOG_DEBUG   LOG(debug)
#define LOG_INFO    LOG(info)
#define LOG_WARNING LOG(warning)
#define LOG_ERROR   LOG(error)
#define LOG_FATAL   LOG(fatal)

#endif
