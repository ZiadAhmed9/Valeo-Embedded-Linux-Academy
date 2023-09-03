cmake_minimum_required(VERSION 3.0)
project(multi_service_application)

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)

find_package(Boost 1.60 COMPONENTS log log_setup system REQUIRED)

INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
link_directories(${Boost_INCLUDE_DIRS})

message(status " Boost Include: ${Boost_INCLUDE_DIR}")
message(status " Boost Libraries: ${Boost_LIBRARY_DIRS}")
message(status "** Boost Libraries: ${Boost_LIBRARIES}")

add_subdirectory(ipc_lib)
add_subdirectory(sockets_lib)

add_executable (math_app math_app/math_app.cpp) #math_app executable
add_executable(daemon_logger    #name of the executable
                simple_logger/config_parsing.cpp simple_logger/config_parsing.hpp #files used in parsing config
                simple_logger/simpleLogger.cpp simple_logger/simpleLogger.h)    #daemon logger header and source
add_executable(receiver_app logger_receiver/server.cpp) #server executable


target_link_libraries(math_app ipc_lib ${Boost_LIBRARIES} pthread)  #Linking math apps with libraries needed
target_link_libraries(daemon_logger socket_lib ipc_lib ${Boost_LIBRARIES} pthread)  #linking daemon logger with libraries needed
target_link_libraries(receiver_app socket_lib pthread)  #linking receiver with libraries needed
