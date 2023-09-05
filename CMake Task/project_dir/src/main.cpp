#include <iostream>
#include <fstream>
#include "../include/WriteInFile.hpp"
#include "../include/Print.hpp"


int main(int argc,char* argv[])
{
    if(std::string(argv[1])=="-f")
    {
        std::ofstream file("helloworld.txt");
        file<<"hello World";
        file.close();
    }
    else if(std::string(argv[1])=="-c")
    {
     std::cout<<"hello world"<<std::endl;
    }
    else
    {
        std::cout<<"error"<<std::endl;
    }
    return 0;
}