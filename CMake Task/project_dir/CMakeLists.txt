cmake_minimum_required(VERSION 3.22.1)

project(
    CMakeProject
    VERSION 1.0
    LANGUAGES CXX
)


add_library(MyLib STATIC library/WriteInFIle.cpp include/WriteInFile.hpp)

add_executable(MyProgram src/main.cpp src/Print.cpp include/Print.hpp)

target_link_libraries(MyProgram PRIVATE MyLib)

install(TARGETS MyProgram)