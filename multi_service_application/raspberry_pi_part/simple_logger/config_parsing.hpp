#ifndef config_parsing_h__
#define config_parsing_h__
#include <vector>
#include <iostream>
//string holding path to config.txt
const std::string config_file_path = "/home/Ziad/Valeo-Embedded-Linux-Academy/multi_service_application/config_lib/config.txt";
/*
-Config.txt parsing function-
Description: Parse the config.txt file
blocking: non
returns: vector of strings containing the names of files inside the config.txt
*/
std::vector<std::string> read_config_file(const std::string &filename);


#endif