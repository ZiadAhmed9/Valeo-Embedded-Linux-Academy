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
CMAKE_SOURCE_DIR = /home/ziad/test1/Valeo-Embedded-Linux-Academy/multi_service_application

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ziad/test1/Valeo-Embedded-Linux-Academy/multi_service_application/build

# Include any dependencies generated for this target.
include ipc_lib/CMakeFiles/ipc_lib.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include ipc_lib/CMakeFiles/ipc_lib.dir/compiler_depend.make

# Include the progress variables for this target.
include ipc_lib/CMakeFiles/ipc_lib.dir/progress.make

# Include the compile flags for this target's objects.
include ipc_lib/CMakeFiles/ipc_lib.dir/flags.make

ipc_lib/CMakeFiles/ipc_lib.dir/ipc_lib.cpp.o: ipc_lib/CMakeFiles/ipc_lib.dir/flags.make
ipc_lib/CMakeFiles/ipc_lib.dir/ipc_lib.cpp.o: ../ipc_lib/ipc_lib.cpp
ipc_lib/CMakeFiles/ipc_lib.dir/ipc_lib.cpp.o: ipc_lib/CMakeFiles/ipc_lib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ziad/test1/Valeo-Embedded-Linux-Academy/multi_service_application/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object ipc_lib/CMakeFiles/ipc_lib.dir/ipc_lib.cpp.o"
	cd /home/ziad/test1/Valeo-Embedded-Linux-Academy/multi_service_application/build/ipc_lib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT ipc_lib/CMakeFiles/ipc_lib.dir/ipc_lib.cpp.o -MF CMakeFiles/ipc_lib.dir/ipc_lib.cpp.o.d -o CMakeFiles/ipc_lib.dir/ipc_lib.cpp.o -c /home/ziad/test1/Valeo-Embedded-Linux-Academy/multi_service_application/ipc_lib/ipc_lib.cpp

ipc_lib/CMakeFiles/ipc_lib.dir/ipc_lib.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ipc_lib.dir/ipc_lib.cpp.i"
	cd /home/ziad/test1/Valeo-Embedded-Linux-Academy/multi_service_application/build/ipc_lib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ziad/test1/Valeo-Embedded-Linux-Academy/multi_service_application/ipc_lib/ipc_lib.cpp > CMakeFiles/ipc_lib.dir/ipc_lib.cpp.i

ipc_lib/CMakeFiles/ipc_lib.dir/ipc_lib.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ipc_lib.dir/ipc_lib.cpp.s"
	cd /home/ziad/test1/Valeo-Embedded-Linux-Academy/multi_service_application/build/ipc_lib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ziad/test1/Valeo-Embedded-Linux-Academy/multi_service_application/ipc_lib/ipc_lib.cpp -o CMakeFiles/ipc_lib.dir/ipc_lib.cpp.s

# Object files for target ipc_lib
ipc_lib_OBJECTS = \
"CMakeFiles/ipc_lib.dir/ipc_lib.cpp.o"

# External object files for target ipc_lib
ipc_lib_EXTERNAL_OBJECTS =

ipc_lib/libipc_lib.so: ipc_lib/CMakeFiles/ipc_lib.dir/ipc_lib.cpp.o
ipc_lib/libipc_lib.so: ipc_lib/CMakeFiles/ipc_lib.dir/build.make
ipc_lib/libipc_lib.so: ipc_lib/CMakeFiles/ipc_lib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ziad/test1/Valeo-Embedded-Linux-Academy/multi_service_application/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared library libipc_lib.so"
	cd /home/ziad/test1/Valeo-Embedded-Linux-Academy/multi_service_application/build/ipc_lib && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ipc_lib.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
ipc_lib/CMakeFiles/ipc_lib.dir/build: ipc_lib/libipc_lib.so
.PHONY : ipc_lib/CMakeFiles/ipc_lib.dir/build

ipc_lib/CMakeFiles/ipc_lib.dir/clean:
	cd /home/ziad/test1/Valeo-Embedded-Linux-Academy/multi_service_application/build/ipc_lib && $(CMAKE_COMMAND) -P CMakeFiles/ipc_lib.dir/cmake_clean.cmake
.PHONY : ipc_lib/CMakeFiles/ipc_lib.dir/clean

ipc_lib/CMakeFiles/ipc_lib.dir/depend:
	cd /home/ziad/test1/Valeo-Embedded-Linux-Academy/multi_service_application/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ziad/test1/Valeo-Embedded-Linux-Academy/multi_service_application /home/ziad/test1/Valeo-Embedded-Linux-Academy/multi_service_application/ipc_lib /home/ziad/test1/Valeo-Embedded-Linux-Academy/multi_service_application/build /home/ziad/test1/Valeo-Embedded-Linux-Academy/multi_service_application/build/ipc_lib /home/ziad/test1/Valeo-Embedded-Linux-Academy/multi_service_application/build/ipc_lib/CMakeFiles/ipc_lib.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : ipc_lib/CMakeFiles/ipc_lib.dir/depend

