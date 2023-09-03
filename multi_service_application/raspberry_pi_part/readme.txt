multi_service_application
by Ziad Ahmed
-------------------------------------------------------------------------------------------------------
CAUTION!: Inside the code are some paths that need to be adjusted before trying on your machine 
          can be found in: simple_logger/simplelogger.hpp
          simple_logger/config_parsing.hpp
-------------------------------------------------------------------------------------------------------
The creation of :
3 main programs:
1) Daemon_logger: 
    -Running as a systemd service in the background
    -uses posix boost logger
    -acts like a receiver end in the message queue
    -object for each message queue is made according to application written inside the config file (Check the config_lib)
    -acts as the sender in the socket 
    -intended to run in the raspberry pi after cross compilation (CHECK THE CROSS COMPILATION DIRECTORY PROVIDED)
2) Receiver_app
    -works as a daemon that run in an infinite loop
    -acts as the client of the socket
    -intended to run on a x86 machine so different compiler than the daemon logger
3) math_app
    -Offer the user different mathematical operations in an abstracted way 
    -acts as the sender of the message queue

3 main libraries:
1) ipc_lib:
    -used to provide APIs that allows access to communication through message queues
    -contains 2 classes for sender and receiver and error handling techniques to tackle different corner cases
    -compiled as a shared library
    -sync and async functions are provided for receiving but in my app will be using the async
2)  sockets_lib:
    -used to provide APIs that allows access to communication through sockets_lib
    -intended to print logs from the apps
    -built statically
3)  Boost log library:
    -used to provide logging capabilities for the application

How it works:
-Provided is the build directory that contains the binaries and the executables
-if you want to build it yourself make sure to install in a build directory to make things easier
-Each program can run on its own you can and you can run them in the any order
-To get the best functionality I suggest you run the logger daemon as systemd service  then the receiver then try the app
-Log files can by found in the logs directory inside the project












