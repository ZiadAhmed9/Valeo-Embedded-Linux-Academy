
#ifndef Requester_h__
#define Requester_h__
#include <cstring>
#define STATE_OK    1
#define STATE_ERROR 0
/* functions description and implementation is to be found in the Requester.cpp file below the main*/
int is_file(std::string argument);
int pipe_error(int *pipe_d);
int single_argument(int n_arguments, char *argument[]);
int two_arguments(int n_arguments, char *argument[]);
#endif