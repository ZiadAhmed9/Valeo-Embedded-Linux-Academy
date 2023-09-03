# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ziad/Rpi_compiling/Valeo-Embedded-Linux-Academy/multi_service_application

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ziad/Rpi_compiling/Valeo-Embedded-Linux-Academy/multi_service_application/build

# Include any dependencies generated for this target.
include sockets_lib/CMakeFiles/socket_lib.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include sockets_lib/CMakeFiles/socket_lib.dir/compiler_depend.make

# Include the progress variables for this target.
include sockets_lib/CMakeFiles/socket_lib.dir/progress.make

# Include the compile flags for this target's objects.
include sockets_lib/CMakeFiles/socket_lib.dir/flags.make

sockets_lib/CMakeFiles/socket_lib.dir/sockets.cpp.o: sockets_lib/CMakeFiles/socket_lib.dir/flags.make
sockets_lib/CMakeFiles/socket_lib.dir/sockets.cpp.o: ../sockets_lib/sockets.cpp
sockets_lib/CMakeFiles/socket_lib.dir/sockets.cpp.o: sockets_lib/CMakeFiles/socket_lib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ziad/Rpi_compiling/Valeo-Embedded-Linux-Academy/multi_service_application/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object sockets_lib/CMakeFiles/socket_lib.dir/sockets.cpp.o"
	cd /home/ziad/Rpi_compiling/Valeo-Embedded-Linux-Academy/multi_service_application/build/sockets_lib && /home/ziad/x-tools/aarch64-rpi4-linux-gnu/bin/aarch64-rpi4-linux-gnu-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT sockets_lib/CMakeFiles/socket_lib.dir/sockets.cpp.o -MF CMakeFiles/socket_lib.dir/sockets.cpp.o.d -o CMakeFiles/socket_lib.dir/sockets.cpp.o -c /home/ziad/Rpi_compiling/Valeo-Embedded-Linux-Academy/multi_service_application/sockets_lib/sockets.cpp

sockets_lib/CMakeFiles/socket_lib.dir/sockets.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/socket_lib.dir/sockets.cpp.i"
	cd /home/ziad/Rpi_compiling/Valeo-Embedded-Linux-Academy/multi_service_application/build/sockets_lib && /home/ziad/x-tools/aarch64-rpi4-linux-gnu/bin/aarch64-rpi4-linux-gnu-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ziad/Rpi_compiling/Valeo-Embedded-Linux-Academy/multi_service_application/sockets_lib/sockets.cpp > CMakeFiles/socket_lib.dir/sockets.cpp.i

sockets_lib/CMakeFiles/socket_lib.dir/sockets.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/socket_lib.dir/sockets.cpp.s"
	cd /home/ziad/Rpi_compiling/Valeo-Embedded-Linux-Academy/multi_service_application/build/sockets_lib && /home/ziad/x-tools/aarch64-rpi4-linux-gnu/bin/aarch64-rpi4-linux-gnu-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ziad/Rpi_compiling/Valeo-Embedded-Linux-Academy/multi_service_application/sockets_lib/sockets.cpp -o CMakeFiles/socket_lib.dir/sockets.cpp.s

# Object files for target socket_lib
socket_lib_OBJECTS = \
"CMakeFiles/socket_lib.dir/sockets.cpp.o"

# External object files for target socket_lib
socket_lib_EXTERNAL_OBJECTS =

sockets_lib/libsocket_lib.a: sockets_lib/CMakeFiles/socket_lib.dir/sockets.cpp.o
sockets_lib/libsocket_lib.a: sockets_lib/CMakeFiles/socket_lib.dir/build.make
sockets_lib/libsocket_lib.a: sockets_lib/CMakeFiles/socket_lib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ziad/Rpi_compiling/Valeo-Embedded-Linux-Academy/multi_service_application/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libsocket_lib.a"
	cd /home/ziad/Rpi_compiling/Valeo-Embedded-Linux-Academy/multi_service_application/build/sockets_lib && $(CMAKE_COMMAND) -P CMakeFiles/socket_lib.dir/cmake_clean_target.cmake
	cd /home/ziad/Rpi_compiling/Valeo-Embedded-Linux-Academy/multi_service_application/build/sockets_lib && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/socket_lib.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
sockets_lib/CMakeFiles/socket_lib.dir/build: sockets_lib/libsocket_lib.a
.PHONY : sockets_lib/CMakeFiles/socket_lib.dir/build

sockets_lib/CMakeFiles/socket_lib.dir/clean:
	cd /home/ziad/Rpi_compiling/Valeo-Embedded-Linux-Academy/multi_service_application/build/sockets_lib && $(CMAKE_COMMAND) -P CMakeFiles/socket_lib.dir/cmake_clean.cmake
.PHONY : sockets_lib/CMakeFiles/socket_lib.dir/clean

sockets_lib/CMakeFiles/socket_lib.dir/depend:
	cd /home/ziad/Rpi_compiling/Valeo-Embedded-Linux-Academy/multi_service_application/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ziad/Rpi_compiling/Valeo-Embedded-Linux-Academy/multi_service_application /home/ziad/Rpi_compiling/Valeo-Embedded-Linux-Academy/multi_service_application/sockets_lib /home/ziad/Rpi_compiling/Valeo-Embedded-Linux-Academy/multi_service_application/build /home/ziad/Rpi_compiling/Valeo-Embedded-Linux-Academy/multi_service_application/build/sockets_lib /home/ziad/Rpi_compiling/Valeo-Embedded-Linux-Academy/multi_service_application/build/sockets_lib/CMakeFiles/socket_lib.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : sockets_lib/CMakeFiles/socket_lib.dir/depend

