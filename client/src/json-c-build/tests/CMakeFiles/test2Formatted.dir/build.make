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
include tests/CMakeFiles/test2Formatted.dir/depend.make

# Include the progress variables for this target.
include tests/CMakeFiles/test2Formatted.dir/progress.make

# Include the compile flags for this target's objects.
include tests/CMakeFiles/test2Formatted.dir/flags.make

tests/CMakeFiles/test2Formatted.dir/test2.c.o: tests/CMakeFiles/test2Formatted.dir/flags.make
tests/CMakeFiles/test2Formatted.dir/test2.c.o: /Users/anetreba/Desktop/uchat/client/src/json-c/tests/test2.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/anetreba/Desktop/uchat/client/src/json-c-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object tests/CMakeFiles/test2Formatted.dir/test2.c.o"
	cd /Users/anetreba/Desktop/uchat/client/src/json-c-build/tests && /Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/test2Formatted.dir/test2.c.o   -c /Users/anetreba/Desktop/uchat/client/src/json-c/tests/test2.c

tests/CMakeFiles/test2Formatted.dir/test2.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/test2Formatted.dir/test2.c.i"
	cd /Users/anetreba/Desktop/uchat/client/src/json-c-build/tests && /Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/anetreba/Desktop/uchat/client/src/json-c/tests/test2.c > CMakeFiles/test2Formatted.dir/test2.c.i

tests/CMakeFiles/test2Formatted.dir/test2.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/test2Formatted.dir/test2.c.s"
	cd /Users/anetreba/Desktop/uchat/client/src/json-c-build/tests && /Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/anetreba/Desktop/uchat/client/src/json-c/tests/test2.c -o CMakeFiles/test2Formatted.dir/test2.c.s

tests/CMakeFiles/test2Formatted.dir/parse_flags.c.o: tests/CMakeFiles/test2Formatted.dir/flags.make
tests/CMakeFiles/test2Formatted.dir/parse_flags.c.o: /Users/anetreba/Desktop/uchat/client/src/json-c/tests/parse_flags.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/anetreba/Desktop/uchat/client/src/json-c-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object tests/CMakeFiles/test2Formatted.dir/parse_flags.c.o"
	cd /Users/anetreba/Desktop/uchat/client/src/json-c-build/tests && /Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/test2Formatted.dir/parse_flags.c.o   -c /Users/anetreba/Desktop/uchat/client/src/json-c/tests/parse_flags.c

tests/CMakeFiles/test2Formatted.dir/parse_flags.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/test2Formatted.dir/parse_flags.c.i"
	cd /Users/anetreba/Desktop/uchat/client/src/json-c-build/tests && /Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/anetreba/Desktop/uchat/client/src/json-c/tests/parse_flags.c > CMakeFiles/test2Formatted.dir/parse_flags.c.i

tests/CMakeFiles/test2Formatted.dir/parse_flags.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/test2Formatted.dir/parse_flags.c.s"
	cd /Users/anetreba/Desktop/uchat/client/src/json-c-build/tests && /Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/anetreba/Desktop/uchat/client/src/json-c/tests/parse_flags.c -o CMakeFiles/test2Formatted.dir/parse_flags.c.s

# Object files for target test2Formatted
test2Formatted_OBJECTS = \
"CMakeFiles/test2Formatted.dir/test2.c.o" \
"CMakeFiles/test2Formatted.dir/parse_flags.c.o"

# External object files for target test2Formatted
test2Formatted_EXTERNAL_OBJECTS =

tests/test2Formatted: tests/CMakeFiles/test2Formatted.dir/test2.c.o
tests/test2Formatted: tests/CMakeFiles/test2Formatted.dir/parse_flags.c.o
tests/test2Formatted: tests/CMakeFiles/test2Formatted.dir/build.make
tests/test2Formatted: libjson-c.5.0.0.dylib
tests/test2Formatted: tests/CMakeFiles/test2Formatted.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/anetreba/Desktop/uchat/client/src/json-c-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable test2Formatted"
	cd /Users/anetreba/Desktop/uchat/client/src/json-c-build/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test2Formatted.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/CMakeFiles/test2Formatted.dir/build: tests/test2Formatted

.PHONY : tests/CMakeFiles/test2Formatted.dir/build

tests/CMakeFiles/test2Formatted.dir/clean:
	cd /Users/anetreba/Desktop/uchat/client/src/json-c-build/tests && $(CMAKE_COMMAND) -P CMakeFiles/test2Formatted.dir/cmake_clean.cmake
.PHONY : tests/CMakeFiles/test2Formatted.dir/clean

tests/CMakeFiles/test2Formatted.dir/depend:
	cd /Users/anetreba/Desktop/uchat/client/src/json-c-build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/anetreba/Desktop/uchat/client/src/json-c /Users/anetreba/Desktop/uchat/client/src/json-c/tests /Users/anetreba/Desktop/uchat/client/src/json-c-build /Users/anetreba/Desktop/uchat/client/src/json-c-build/tests /Users/anetreba/Desktop/uchat/client/src/json-c-build/tests/CMakeFiles/test2Formatted.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tests/CMakeFiles/test2Formatted.dir/depend

