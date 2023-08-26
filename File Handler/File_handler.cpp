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
int main()
{

  char command_buffer[32];               // a buffer to hold the command in when taking it from the pipe
  FILE *fp = nullptr;                       // a pointer to FILE type to be used in piping between the app and the terminal
  mkfifo(pipeName, 0666);                // create a pipe with name defined in shmem.hpp and with permision 0666
  int pipe_d = open(pipeName, O_RDONLY); // get the file descriptor of the pipe
  if (pipe_d == -1)                      // checking if the pipe works correctly
  {
    LOG_FATAL << "FILE HANDLER: failed to access the command pipe";
    boost::log::core::get()->flush();
  }
  sem_t *semptr = sem_open(SemaphoreName, O_CREAT, AccessPerms, 0); // creating a semaphore initialized by 0
  if (semptr == SEM_FAILED)
  {
    LOG_FATAL << "FILE HANDLER: failed to access the semaphore";
    boost::log::core::get()->flush();
  }
  LOG_TRACE << "FILE HANDLER: Semaphore created and initially is 0";
  boost::log::core::get()->flush();
  while (true) // infinite loop
  {

    int bytes_read = read(pipe_d, command_buffer, sizeof(command_buffer)); // read the pipe contents and store it in command_buffer and the size of the buffer is also passed
    if (bytes_read == 0)                                                   // If no data inside the pipe
    {
      LOG_WARNING << "FILE HANDLER:No command received from requester checking again after 5 seconds";
      boost::log::core::get()->flush();
      sleep(5);
      continue;
    }
    command_buffer[bytes_read] = '\0';                                                             // last element in the string must be \0
    LOG_TRACE << "FILE HANDLER: found " << bytes_read << " bytes containing : " << command_buffer; // for tracing log the number of bytes and contents
    boost::log::core::get()->flush();

    /*now Open a pipe between terminal and cpp file, The function takes the command executes it and returns pointer to file containing output*/
    fp = popen(command_buffer, "r"); 
    if (!fp) // if file is not created didn't open
    {
      LOG_FATAL << "FILE HANDLER: failed to access pipe with CMD to execute the command";
      boost::log::core::get()->flush();
      sleep(5);
      continue;
    }
    int shm_Id = shmget(SHARED_MEMORY_KEY, 1024, IPC_CREAT | 0666); // get a shared memory ID
    if (shm_Id == -1)                                               // if returned -1
    {
      LOG_FATAL << "FILE HANDLER: Shared memory ID couldn't be acquired by file handler";
      boost::log::core::get()->flush();
      sleep(5);
      continue;
    }
    /*now we use shmat to attach this process with the shared memory
    this function must be casted as it returns pointer to void
    it returns address to the shared memory
    */
    char *pshared_memory = static_cast<char *>(shmat(shm_Id, nullptr, 0));
    char output_buffer[512]; // buffer to hold the data to be passed to the shared memory
    size_t total_size = 0;
    for (int i = 0; i < 512; i++)
    {
      strcpy(pshared_memory + i, ""); // Initially empty the shared memory
    }
    LOG_TRACE << "FILE HANDLER: Memory is erased before writing on it";
    boost::log::core::get()->flush();
    /* next line is quiet tricky, we discussed that fp is pointer to file
    which contains the output of the command we received and now we want to store
    this output in the shared memory feof() function will be true if we reach the end of the file
    also if the file reads null value it will terminate
    so if we reached the end of the fill we exit or if we reach the end of the output
    fgets: is used to read the contents
    */
    LOG_TRACE << "FILE HANDLER: Writing on shared memory";
    boost::log::core::get()->flush();
    while (!feof(fp) && fgets(output_buffer, sizeof(output_buffer), fp) != NULL)
    {
      size_t len = strlen(output_buffer);                      // create a variable holding the length of the buffer
      memcpy(pshared_memory + total_size, output_buffer, len); // copy the memory line from the file to the shared memory
      total_size += len;                                       // increment to go to the next line
    }
    sem_post(semptr);      // once done working with the shared memory we increment the semaphore
    shmdt(pshared_memory); // we now un-attach from the shared memory safely and start all over again
    LOG_TRACE << "FILE HANDLER: Semaphore is incremented";
    boost::log::core::get()->flush();
    pclose(fp);
  }
  return 0;
}