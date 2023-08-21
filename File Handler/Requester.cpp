#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <semaphore.h>
#include <string.h>
#include "shmem.hpp"
#include <sys/shm.h>
#include <cstring>
#include "simpleLogger/simpleLogger.h"
using namespace std;

/*Supported commands*/
string listing_cmd="ls";
string file_cont_cmd="cat";

/*A function I made, that will check if the name of the second argument contains the character . which means it is a file not a directory*/
int is_file(string argument)
{
  int i;
  for(i=0;argument[i];i++)
  {
    if(argument[i]=='.')
    {
      return 1;
    }
  }
  return 0;
}

/*The line bellow I take arguments when executing this app*/
int main(int argc, char *argv[])
{
  int pipe_d = open(pipeName, O_WRONLY); //Get pipe desciptor in this variable
  if (pipe_d==-1)
  {
    LOG_FATAL << "REQUESTER: requester failed to open pipe";
    // boost::log::core::get()->flush();
  }
  LOG_TRACE << "REQUESTER: Pipe desciptor acquired";
  // boost::log::core::get()->flush();
  if (argc == 2 && argv[1] == listing_cmd)        //if the user entered 1 argument when executing this app
  {
    LOG_WARNING<<"REQUESTER: Only one argument is entered";
    // boost::log::core::get()->flush();
    string command = argv[1];   //the command is surely the second part
    write(pipe_d, command.c_str(), command.size()); //inside the command pipe put the command for the file handler
    LOG_TRACE << "REQUESTER: command is sent through the pipe successfully";
    boost::log::core::get()->flush();
  }
  else if (argc == 3 && (argv[1]==listing_cmd || argv[1]==file_cont_cmd)) //else if you received more than 2 arguments
  {
    string command1 = argv[1];  //first one will be the command
    string command2 = argv[2];  //second one will be the path of the execution
    string command = command1 + " " + command2; //concatenate to get the full command
    if(is_file(command2)&&command1=="ls") //check if the user entered ls and a file which shall not work
    {
    LOG_TRACE << "Invalide input, ls can't be used with file";
    // boost::log::core::get()->flush();
    return 1;
    
    }
    else if(!is_file(command2)&&command1=="cat") //check if the user entered cat and directory which shall not work
    {
    LOG_TRACE << "Invalide input, cat can't be used with directory";
    // boost::log::core::get()->flush();
    return 1;
    }
    write(pipe_d, command.c_str(), command.size()); //write the command in the pipe
    LOG_TRACE << "REQUESTER: command is sent through the pipe successfully";
    // boost::log::core::get()->flush();
    return 1;
  }
  else
  {
    LOG_FATAL << "REQUESTER: Arguments entered are not supported -> "<<argv[1];
    // boost::log::core::get()->flush();
    return 1;
  }
  //now this app will go to sleep state until the shared memory is available
  sem_t *semptr = sem_open(SemaphoreName,0);    // this function return pointer to semaphore     
  if(semptr== SEM_FAILED)
  {
    LOG_FATAL << "REQUESTER: Requester failed to access the semaphore";
    // boost::log::core::get()->flush();
    return 1;
  }
  if (!sem_wait(semptr)) //sleep until semaphore is incremented
  {
    LOG_TRACE << "REQUESTER: Waiting For Semaphore";
    // boost::log::core::get()->flush();
    int shm_Id = shmget(SHARED_MEMORY_KEY, 1024, IPC_CREAT|0666); //open the name and size and permissions given and return the id of the shared memory
    char *pshared_memory = static_cast<char *>(shmat(shm_Id, nullptr, 0)); //attach to the shared memory, this function returns a pointer to the memory specified
    if (shm_Id == -1) //if the returned value is -1 an error occured so log the event and
    {
      LOG_FATAL << "REQUESTER: requester failed to access shared memory";
      // boost::log::core::get()->flush();
      return 1;
    }
    LOG_TRACE << "REQUESTER: Semaphore for shared memory is acquired and is decremented";
    // boost::log::core::get()->flush();
    cout << pshared_memory << endl;// print out the contents of the shared memory
    shmdt(pshared_memory); //deattach from the shared memory
    LOG_TRACE << "REQUESTER: Successfully de-attached from shared memory  \n ==================done================== ";
    // boost::log::core::get()->flush();
  }
  return 0;
}