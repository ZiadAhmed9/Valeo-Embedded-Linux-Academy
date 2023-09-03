add_library(socket_lib STATIC sockets.cpp)
target_include_directories(socket_lib PUBLIC $(CMAKE_CURRENT_SOURCE_DIR))