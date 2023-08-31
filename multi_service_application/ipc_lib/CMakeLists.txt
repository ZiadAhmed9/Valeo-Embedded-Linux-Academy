add_library(ipc_lib SHARED ipc_lib.cpp)
target_include_directories(ipc_lib PUBLIC $(CMAKE_CURRENT_SOURCE_DIR))