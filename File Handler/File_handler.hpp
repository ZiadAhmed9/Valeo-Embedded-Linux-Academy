#ifndef File_handler_h__
#define File_handler_h__
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
#include <thread>
#include <semaphore.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include "shmem.hpp"
#include "simpleLogger/simpleLogger.h"
using namespace std;

#define BUFFER_SIZE 512
#define COMMAND_SIZE 32


#endif