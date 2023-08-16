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
