Guide to build this project:
1) clone this repo into your machine
2) inside the project execute the command `cmake -S . -B build -DCMAKE_INSTALL_PREFIX=./buid/`
3) The above command shall create a file named 'build' containing the makefile and other tools generated
4) then `cd build`
5) then write 'make'
6) Binaries will be added and the building is done
7) Now you can run the files Like follows


Trying the project:
1) `./file_handler'
2) open a new terminal and execute './requester $command $directory or file you Waiting


Debugging :
1) After executing the project you can check the logs in the run_logs.txt found inside build directory
2) Both requester and file_handler write logs there so be careful of the numbering

Supported commands:
1) ls
2) ls directory
3) cat any file 


Gtest is used to test some functions used in my code you can run the tests again in the tests directory