
#ifndef Requester_h__
#define Requester_h__
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
#include <cstring>
#define STATE_OK    1
#define STATE_ERROR 0
/* functions description and implementation is to be found in the Requester.cpp file below the main*/

/*Functions I made to make the code more modular*/
/*The following function I will use to determine if the entered is a file or a directory by checking the ',' */
int is_file(std::string argument);

/*The next function checks if we failed to obtain the pipe*/
int pipe_error(int *pipe_d);

/*This function is to be executed in case the user entered only 1 argument*/
int single_argument(int n_arguments, char *argument[]);

/*This function is to be executed in case the user entered 2 arguments*/
int two_arguments(int n_arguments, char *argument[]);
#endif