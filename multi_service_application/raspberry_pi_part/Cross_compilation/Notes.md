To cross compile the code:
1-We must have the .cmake file provided in this directory
2-Change the macro -DCMAKE_TOOLCHAIN_FILE to have the path to the .cmake

The command should be executed in the directory containing the cmakelists.txt for the cmake will be:
'~/src/build$ cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE=~//home/ziad/test1/Valeo-Embedded-Linux-Academy/multi_service_application/Cross_compilation/tool_chain.cmake -DCMAKE_INSTALL_PREFIX=./build/'
