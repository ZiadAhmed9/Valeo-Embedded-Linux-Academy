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
#include "Requester.hpp"

/*Supported commands*/
string listing_cmd = "ls";
string file_cont_cmd = "cat";

/*Variables to be used in code*/
string command;       //This string will carry the full command
string command_part1;   //This string will carry first part of command if more than 1 argument
string command_part2;   //This string will carry second part of command if more than 1 argument
int state;


/*The line bellow I take arguments when executing this app*/
int main(int argc, char *argv[])
{
  int pipe_d = open(pipeName, O_WRONLY); // Get pipe desciptor in this variable
  if (pipe_error(&pipe_d))               // Check for erros while creating the pipe
  {
    return 1;
  }
  LOG_TRACE << "REQUESTER: Pipe desciptor acquired";
  boost::log::core::get()->flush();
  if (single_argument(argc, argv)) // if the user entered 1 argument when executing this app
  {
    write(pipe_d, command.c_str(), command.size()); // inside the command pipe put the command for the file handler
    LOG_TRACE << "REQUESTER: command is sent through the pipe successfully";
    boost::log::core::get()->flush();
  }
  else if (two_arguments(argc,argv)) // else if you received more than 2 arguments
  {
    write(pipe_d, command.c_str(), command.size()); // write the command in the pipe
    LOG_TRACE << "REQUESTER: command is sent through the pipe successfully";
    boost::log::core::get()->flush();
  }
  else
  {
    LOG_TRACE << "REQUESTER: Program exited due to fatal error";
    LOG_TRACE << "=================FORCED EXIT==================";
    return 1;
  }
  // now this app will go to sleep state until the shared memory is available
  sem_t *semptr = sem_open(SemaphoreName, 0); // this function return pointer to semaphore
  if (semptr == SEM_FAILED)
  {
    LOG_FATAL << "REQUESTER: Requester failed to access the semaphore";
    boost::log::core::get()->flush();
    return 1;
  }
  if (!sem_wait(semptr)) // sleep until semaphore is incremented
  {
    LOG_TRACE << "REQUESTER: Waiting For Semaphore";
    boost::log::core::get()->flush();
    int shm_Id = shmget(SHARED_MEMORY_KEY, 1024, IPC_CREAT | 0666);        // open the name and size and permissions given and return the id of the shared memory
    char *pshared_memory = static_cast<char *>(shmat(shm_Id, nullptr, 0)); // attach to the shared memory, this function returns a pointer to the memory specified
    if (shm_Id == -1)                                                      // if the returned value is -1 an error occured so log the event and
    {
      LOG_FATAL << "REQUESTER: requester failed to access shared memory";
      boost::log::core::get()->flush();
      return 1;
    }
    LOG_TRACE << "REQUESTER: Semaphore for shared memory is acquired and is decremented";
    boost::log::core::get()->flush();
    cout << pshared_memory << endl; // print out the contents of the shared memory
    shmdt(pshared_memory);          // deattach from the shared memory
    LOG_TRACE << "REQUESTER: Successfully de-attached from shared memory  \n ==================done================== ";
    boost::log::core::get()->flush();
  }
  return 0;
}


/*Functions I made to make the code more modular*/
/*The following function I will use to determine if the entered is a file or a directory by checking the ',' */
int is_file(string argument)
{
  int i;
  for (i = 0; argument[i]; i++)
  {
    if (argument[i] == '.')
    {
      return 1;
    }
  }
  return 0;
}
/*The next function checks if we failed to obtain the pipe*/
int pipe_error(int *pipe_d)
{

  if (*pipe_d == -1)
  {
    LOG_FATAL << "REQUESTER: requester failed to open pipe";
    boost::log::core::get()->flush();
    return 1;
  }
  return 0;
}
/*This function is to be executed in case the user entered only 1 argument*/
int single_argument(int n_arguments, char *argument[])
{
  state=STATE_OK;
  if (n_arguments == 2 && argument[1] == listing_cmd) // if the user entered 1 argument when executing this app
  {
    LOG_WARNING << "REQUESTER: Only one argument is entered";
    boost::log::core::get()->flush();
    command = argument[1]; // the command is surely the second part
  }
  else
  {
    state=STATE_ERROR;
  }
  return state;
}
/*This function is to be executed in case the user entered 2 arguments*/
int two_arguments(int n_arguments, char *argument[])
{
  state=STATE_OK;
  if (n_arguments == 3 && (argument[1] == listing_cmd || argument[1] == file_cont_cmd)) // else if you received more than 2 arguments
  {
    command_part1 = argument[1];                  // first one will be the command
    command_part2 = argument[2];                  // second one will be the path of the execution
    if (is_file(command_part2) && command_part1 == "ls")  // check if the user entered ls and a file which shall not work
    {
      LOG_FATAL << "REQUESTER:Invalid input, ls command can't be used with file";
      boost::log::core::get()->flush();
      state=STATE_ERROR;
    }
    else if(!is_file(command_part2)&&command_part1=="cat")    //if the second argument is not a file
    {
      LOG_FATAL << "REQUESTER:Invalid input, cat command can't be used with directory";
      boost::log::core::get()->flush();
      state=STATE_ERROR;
    }
  }
  else
  {
    LOG_FATAL << "REQUESTER: Arguments entered are not supported -> " << argument[1];
    boost::log::core::get()->flush();
    state=STATE_ERROR;
  }
  command = command_part1 + " " + command_part2;
  return state;
}