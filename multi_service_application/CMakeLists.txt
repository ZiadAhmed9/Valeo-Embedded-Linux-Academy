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

add_library(ipc_lib ipc_lib/ipc_lib.cpp ipc_lib/ipc_lib.hpp)
add_executable (math_app math_app/math_app.cpp)
add_executable(daemon_logger simple_logger/simpleLogger.cpp simple_logger/simpleLogger.h)
add_executable(receiver_app logger_receiver/server.cpp)

target_link_libraries(math_app ipc_lib ${Boost_LIBRARIES} pthread)
target_link_libraries(daemon_logger socket_lib ipc_lib ${Boost_LIBRARIES} pthread)
target_link_libraries(receiver_app socket_lib pthread)
