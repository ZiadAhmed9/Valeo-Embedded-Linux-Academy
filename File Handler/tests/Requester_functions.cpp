#include <iostream>
using namespace std;
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
int single_argument(int n_arguments, string argument)
{
  int state = 1;
  if (n_arguments == 2 && argument== "ls") // if the user entered 1 argument when executing this app
  {
    state=1;
  }
  else
  {
    state = 0;
  }
  return state;
}