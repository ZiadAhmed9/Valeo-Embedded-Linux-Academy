By : **Ziad Ahmed Ibrahim**
Requirements: build a project using Makefile

---
## Source codes
- I tried creating another file with the main and to use a function from it for testing
### main file
```C++
#include <iostream>
#include "head.hpp"
using namespace std;

int main()
{
 cout <<"Hello this is ziad from main.c"<<endl;
 func();
return 0;
}

```

### head.cpp
```C++
#include <iostream>

void func()
{
  std::cout<<"hi i'm function from head.c"<<std::endl;	
}
```
### Makefile 
```bash
CC=g++	#compiler used
CFLAGS=-Wall -c	#flags for compilation

all: project		#make all depends on project building

install: project	#install build project also
	mkdir -p build/usr/bin	#
	mv *.o build/usr/bin/
	mv main build/usr/bin/

project: head.o main.o 		#dependencies for building the project
	$(CC) main.o head.o -o main	#I used no flags here by the way

main.o: main.cpp			#dependencies to compile main.cpp
	$(CC) $(CFLAGS) main.cpp

head.o: head.cpp			#dependencies to compile head.cpp
	$(CC) $(CFLAGS) head.cpp

clean :
	rm -rf *o main		#removes the main exe file
	rm -r build			#removes the build directory

```
## Testing
### Make all
![[Pasted image 20230816200024.png]]
- as we can see the binaries are produced 
- also the executable file "main" is made

<div style="page-break-after: always; visibility: hidden"> \pagebreak </div>

### Output from the project
![[Pasted image 20230816200622.png]]
- As shown both the prints from the head.cpp and the main.cpp are printed
- so the project was compiled and linked successfully 
## Make install
![[Pasted image 20230816200346.png]]
- Here it shows afte make install the executables and binaries are moved to their directory

<div style="page-break-after: always; visibility: hidden"> \pagebreak </div>

### Make clean
![[Pasted image 20230816200457.png]]
- As shown all executables and binaries are deleted  