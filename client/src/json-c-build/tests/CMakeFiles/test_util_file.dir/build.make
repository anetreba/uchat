# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

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

# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /Users/anetreba/.brew/Cellar/cmake/3.17.3/bin/cmake

# The command to remove a file.
RM = /Users/anetreba/.brew/Cellar/cmake/3.17.3/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/anetreba/Desktop/uchat/client/src/json-c

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/anetreba/Desktop/uchat/client/src/json-c-build

# Include any dependencies generated for this target.
include tests/CMakeFiles/test_util_file.dir/depend.make

# Include the progress variables for this target.
include tests/CMakeFiles/test_util_file.dir/progress.make

# Include the compile flags for this target's objects.
include tests/CMakeFiles/test_util_file.dir/flags.make

tests/CMakeFiles/test_util_file.dir/test_util_file.c.o: tests/CMakeFiles/test_util_file.dir/flags.make
tests/CMakeFiles/test_util_file.dir/test_util_file.c.o: /Users/anetreba/Desktop/uchat/client/src/json-c/tests/test_util_file.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/anetreba/Desktop/uchat/client/src/json-c-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object tests/CMakeFiles/test_util_file.dir/test_util_file.c.o"
	cd /Users/anetreba/Desktop/uchat/client/src/json-c-build/tests && /Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/test_util_file.dir/test_util_file.c.o   -c /Users/anetreba/Desktop/uchat/client/src/json-c/tests/test_util_file.c

tests/CMakeFiles/test_util_file.dir/test_util_file.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/test_util_file.dir/test_util_file.c.i"
	cd /Users/anetreba/Desktop/uchat/client/src/json-c-build/tests && /Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/anetreba/Desktop/uchat/client/src/json-c/tests/test_util_file.c > CMakeFiles/test_util_file.dir/test_util_file.c.i

tests/CMakeFiles/test_util_file.dir/test_util_file.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/test_util_file.dir/test_util_file.c.s"
	cd /Users/anetreba/Desktop/uchat/client/src/json-c-build/tests && /Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/anetreba/Desktop/uchat/client/src/json-c/tests/test_util_file.c -o CMakeFiles/test_util_file.dir/test_util_file.c.s

# Object files for target test_util_file
test_util_file_OBJECTS = \
"CMakeFiles/test_util_file.dir/test_util_file.c.o"

# External object files for target test_util_file
test_util_file_EXTERNAL_OBJECTS =

tests/test_util_file: tests/CMakeFiles/test_util_file.dir/test_util_file.c.o
tests/test_util_file: tests/CMakeFiles/test_util_file.dir/build.make
tests/test_util_file: libjson-c.5.0.0.dylib
tests/test_util_file: tests/CMakeFiles/test_util_file.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/anetreba/Desktop/uchat/client/src/json-c-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable test_util_file"
	cd /Users/anetreba/Desktop/uchat/client/src/json-c-build/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_util_file.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/CMakeFiles/test_util_file.dir/build: tests/test_util_file

.PHONY : tests/CMakeFiles/test_util_file.dir/build

tests/CMakeFiles/test_util_file.dir/clean:
	cd /Users/anetreba/Desktop/uchat/client/src/json-c-build/tests && $(CMAKE_COMMAND) -P CMakeFiles/test_util_file.dir/cmake_clean.cmake
.PHONY : tests/CMakeFiles/test_util_file.dir/clean

tests/CMakeFiles/test_util_file.dir/depend:
	cd /Users/anetreba/Desktop/uchat/client/src/json-c-build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/anetreba/Desktop/uchat/client/src/json-c /Users/anetreba/Desktop/uchat/client/src/json-c/tests /Users/anetreba/Desktop/uchat/client/src/json-c-build /Users/anetreba/Desktop/uchat/client/src/json-c-build/tests /Users/anetreba/Desktop/uchat/client/src/json-c-build/tests/CMakeFiles/test_util_file.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tests/CMakeFiles/test_util_file.dir/depend

