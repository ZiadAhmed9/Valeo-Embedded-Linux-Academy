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
CMAKE_SOURCE_DIR = "/home/ziad/test/Valeo-Embedded-Linux-Academy/File Handler"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/ziad/test/Valeo-Embedded-Linux-Academy/File Handler/build"

# Include any dependencies generated for this target.
include CMakeFiles/simpleLogger.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/simpleLogger.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/simpleLogger.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/simpleLogger.dir/flags.make

CMakeFiles/simpleLogger.dir/simpleLogger/simpleLogger.cpp.o: CMakeFiles/simpleLogger.dir/flags.make
CMakeFiles/simpleLogger.dir/simpleLogger/simpleLogger.cpp.o: ../simpleLogger/simpleLogger.cpp
CMakeFiles/simpleLogger.dir/simpleLogger/simpleLogger.cpp.o: CMakeFiles/simpleLogger.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/ziad/test/Valeo-Embedded-Linux-Academy/File Handler/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/simpleLogger.dir/simpleLogger/simpleLogger.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/simpleLogger.dir/simpleLogger/simpleLogger.cpp.o -MF CMakeFiles/simpleLogger.dir/simpleLogger/simpleLogger.cpp.o.d -o CMakeFiles/simpleLogger.dir/simpleLogger/simpleLogger.cpp.o -c "/home/ziad/test/Valeo-Embedded-Linux-Academy/File Handler/simpleLogger/simpleLogger.cpp"

CMakeFiles/simpleLogger.dir/simpleLogger/simpleLogger.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/simpleLogger.dir/simpleLogger/simpleLogger.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/ziad/test/Valeo-Embedded-Linux-Academy/File Handler/simpleLogger/simpleLogger.cpp" > CMakeFiles/simpleLogger.dir/simpleLogger/simpleLogger.cpp.i

CMakeFiles/simpleLogger.dir/simpleLogger/simpleLogger.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/simpleLogger.dir/simpleLogger/simpleLogger.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/ziad/test/Valeo-Embedded-Linux-Academy/File Handler/simpleLogger/simpleLogger.cpp" -o CMakeFiles/simpleLogger.dir/simpleLogger/simpleLogger.cpp.s

# Object files for target simpleLogger
simpleLogger_OBJECTS = \
"CMakeFiles/simpleLogger.dir/simpleLogger/simpleLogger.cpp.o"

# External object files for target simpleLogger
simpleLogger_EXTERNAL_OBJECTS =

libsimpleLogger.a: CMakeFiles/simpleLogger.dir/simpleLogger/simpleLogger.cpp.o
libsimpleLogger.a: CMakeFiles/simpleLogger.dir/build.make
libsimpleLogger.a: CMakeFiles/simpleLogger.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/ziad/test/Valeo-Embedded-Linux-Academy/File Handler/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libsimpleLogger.a"
	$(CMAKE_COMMAND) -P CMakeFiles/simpleLogger.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/simpleLogger.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/simpleLogger.dir/build: libsimpleLogger.a
.PHONY : CMakeFiles/simpleLogger.dir/build

CMakeFiles/simpleLogger.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/simpleLogger.dir/cmake_clean.cmake
.PHONY : CMakeFiles/simpleLogger.dir/clean

CMakeFiles/simpleLogger.dir/depend:
	cd "/home/ziad/test/Valeo-Embedded-Linux-Academy/File Handler/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/ziad/test/Valeo-Embedded-Linux-Academy/File Handler" "/home/ziad/test/Valeo-Embedded-Linux-Academy/File Handler" "/home/ziad/test/Valeo-Embedded-Linux-Academy/File Handler/build" "/home/ziad/test/Valeo-Embedded-Linux-Academy/File Handler/build" "/home/ziad/test/Valeo-Embedded-Linux-Academy/File Handler/build/CMakeFiles/simpleLogger.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/simpleLogger.dir/depend
