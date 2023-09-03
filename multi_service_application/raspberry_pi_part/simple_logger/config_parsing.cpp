#include "config_parsing.hpp"
#include <fstream>
#include <ostream>
#include <iostream>
using namespace std;

/*
-Config.txt parsing function-
Description: Parse the config.txt file
blocking: non
returns: vector of strings containing the names of files inside the config.txt
*/
vector<string> read_config_file(const string &filename)
{
    vector<string> app_names;      // Create a vector of strings to hold app names inside the config files
    ifstream configFile(filename); // Object of the class configFile and pass it the file name
    if (!configFile.is_open())     // Check if the file exists
    {
        cerr << "Error opening config file: " << filename << endl;
        return app_names;
    }

    string line;                      // Creating a string to hold each line indvidually
    while (getline(configFile, line)) // Read each line until the end of the file
    {
        line = "/" + line;         // add '/' to the name to use it as message queue name
        app_names.push_back(line); // push back the name extracted from the config.txt into the vector
    }

    configFile.close(); // close the file after done
    return app_names;
}