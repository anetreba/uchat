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
CMAKE_SOURCE_DIR = /Users/anetreba/Desktop/uchat/server/src/json-c

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/anetreba/Desktop/uchat/server/src/json-c-build

# Include any dependencies generated for this target.
include CMakeFiles/json-c.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/json-c.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/json-c.dir/flags.make

CMakeFiles/json-c.dir/arraylist.c.o: CMakeFiles/json-c.dir/flags.make
CMakeFiles/json-c.dir/arraylist.c.o: /Users/anetreba/Desktop/uchat/server/src/json-c/arraylist.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/anetreba/Desktop/uchat/server/src/json-c-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/json-c.dir/arraylist.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/json-c.dir/arraylist.c.o   -c /Users/anetreba/Desktop/uchat/server/src/json-c/arraylist.c

CMakeFiles/json-c.dir/arraylist.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/json-c.dir/arraylist.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/anetreba/Desktop/uchat/server/src/json-c/arraylist.c > CMakeFiles/json-c.dir/arraylist.c.i

CMakeFiles/json-c.dir/arraylist.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/json-c.dir/arraylist.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/anetreba/Desktop/uchat/server/src/json-c/arraylist.c -o CMakeFiles/json-c.dir/arraylist.c.s

CMakeFiles/json-c.dir/debug.c.o: CMakeFiles/json-c.dir/flags.make
CMakeFiles/json-c.dir/debug.c.o: /Users/anetreba/Desktop/uchat/server/src/json-c/debug.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/anetreba/Desktop/uchat/server/src/json-c-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/json-c.dir/debug.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/json-c.dir/debug.c.o   -c /Users/anetreba/Desktop/uchat/server/src/json-c/debug.c

CMakeFiles/json-c.dir/debug.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/json-c.dir/debug.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/anetreba/Desktop/uchat/server/src/json-c/debug.c > CMakeFiles/json-c.dir/debug.c.i

CMakeFiles/json-c.dir/debug.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/json-c.dir/debug.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/anetreba/Desktop/uchat/server/src/json-c/debug.c -o CMakeFiles/json-c.dir/debug.c.s

CMakeFiles/json-c.dir/json_c_version.c.o: CMakeFiles/json-c.dir/flags.make
CMakeFiles/json-c.dir/json_c_version.c.o: /Users/anetreba/Desktop/uchat/server/src/json-c/json_c_version.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/anetreba/Desktop/uchat/server/src/json-c-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/json-c.dir/json_c_version.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/json-c.dir/json_c_version.c.o   -c /Users/anetreba/Desktop/uchat/server/src/json-c/json_c_version.c

CMakeFiles/json-c.dir/json_c_version.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/json-c.dir/json_c_version.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/anetreba/Desktop/uchat/server/src/json-c/json_c_version.c > CMakeFiles/json-c.dir/json_c_version.c.i

CMakeFiles/json-c.dir/json_c_version.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/json-c.dir/json_c_version.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/anetreba/Desktop/uchat/server/src/json-c/json_c_version.c -o CMakeFiles/json-c.dir/json_c_version.c.s

CMakeFiles/json-c.dir/json_object.c.o: CMakeFiles/json-c.dir/flags.make
CMakeFiles/json-c.dir/json_object.c.o: /Users/anetreba/Desktop/uchat/server/src/json-c/json_object.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/anetreba/Desktop/uchat/server/src/json-c-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/json-c.dir/json_object.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/json-c.dir/json_object.c.o   -c /Users/anetreba/Desktop/uchat/server/src/json-c/json_object.c

CMakeFiles/json-c.dir/json_object.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/json-c.dir/json_object.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/anetreba/Desktop/uchat/server/src/json-c/json_object.c > CMakeFiles/json-c.dir/json_object.c.i

CMakeFiles/json-c.dir/json_object.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/json-c.dir/json_object.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/anetreba/Desktop/uchat/server/src/json-c/json_object.c -o CMakeFiles/json-c.dir/json_object.c.s

CMakeFiles/json-c.dir/json_object_iterator.c.o: CMakeFiles/json-c.dir/flags.make
CMakeFiles/json-c.dir/json_object_iterator.c.o: /Users/anetreba/Desktop/uchat/server/src/json-c/json_object_iterator.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/anetreba/Desktop/uchat/server/src/json-c-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/json-c.dir/json_object_iterator.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/json-c.dir/json_object_iterator.c.o   -c /Users/anetreba/Desktop/uchat/server/src/json-c/json_object_iterator.c

CMakeFiles/json-c.dir/json_object_iterator.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/json-c.dir/json_object_iterator.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/anetreba/Desktop/uchat/server/src/json-c/json_object_iterator.c > CMakeFiles/json-c.dir/json_object_iterator.c.i

CMakeFiles/json-c.dir/json_object_iterator.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/json-c.dir/json_object_iterator.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/anetreba/Desktop/uchat/server/src/json-c/json_object_iterator.c -o CMakeFiles/json-c.dir/json_object_iterator.c.s

CMakeFiles/json-c.dir/json_pointer.c.o: CMakeFiles/json-c.dir/flags.make
CMakeFiles/json-c.dir/json_pointer.c.o: /Users/anetreba/Desktop/uchat/server/src/json-c/json_pointer.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/anetreba/Desktop/uchat/server/src/json-c-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object CMakeFiles/json-c.dir/json_pointer.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/json-c.dir/json_pointer.c.o   -c /Users/anetreba/Desktop/uchat/server/src/json-c/json_pointer.c

CMakeFiles/json-c.dir/json_pointer.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/json-c.dir/json_pointer.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/anetreba/Desktop/uchat/server/src/json-c/json_pointer.c > CMakeFiles/json-c.dir/json_pointer.c.i

CMakeFiles/json-c.dir/json_pointer.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/json-c.dir/json_pointer.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/anetreba/Desktop/uchat/server/src/json-c/json_pointer.c -o CMakeFiles/json-c.dir/json_pointer.c.s

CMakeFiles/json-c.dir/json_tokener.c.o: CMakeFiles/json-c.dir/flags.make
CMakeFiles/json-c.dir/json_tokener.c.o: /Users/anetreba/Desktop/uchat/server/src/json-c/json_tokener.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/anetreba/Desktop/uchat/server/src/json-c-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object CMakeFiles/json-c.dir/json_tokener.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/json-c.dir/json_tokener.c.o   -c /Users/anetreba/Desktop/uchat/server/src/json-c/json_tokener.c

CMakeFiles/json-c.dir/json_tokener.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/json-c.dir/json_tokener.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/anetreba/Desktop/uchat/server/src/json-c/json_tokener.c > CMakeFiles/json-c.dir/json_tokener.c.i

CMakeFiles/json-c.dir/json_tokener.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/json-c.dir/json_tokener.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/anetreba/Desktop/uchat/server/src/json-c/json_tokener.c -o CMakeFiles/json-c.dir/json_tokener.c.s

CMakeFiles/json-c.dir/json_util.c.o: CMakeFiles/json-c.dir/flags.make
CMakeFiles/json-c.dir/json_util.c.o: /Users/anetreba/Desktop/uchat/server/src/json-c/json_util.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/anetreba/Desktop/uchat/server/src/json-c-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building C object CMakeFiles/json-c.dir/json_util.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/json-c.dir/json_util.c.o   -c /Users/anetreba/Desktop/uchat/server/src/json-c/json_util.c

CMakeFiles/json-c.dir/json_util.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/json-c.dir/json_util.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/anetreba/Desktop/uchat/server/src/json-c/json_util.c > CMakeFiles/json-c.dir/json_util.c.i

CMakeFiles/json-c.dir/json_util.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/json-c.dir/json_util.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/anetreba/Desktop/uchat/server/src/json-c/json_util.c -o CMakeFiles/json-c.dir/json_util.c.s

CMakeFiles/json-c.dir/json_visit.c.o: CMakeFiles/json-c.dir/flags.make
CMakeFiles/json-c.dir/json_visit.c.o: /Users/anetreba/Desktop/uchat/server/src/json-c/json_visit.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/anetreba/Desktop/uchat/server/src/json-c-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building C object CMakeFiles/json-c.dir/json_visit.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/json-c.dir/json_visit.c.o   -c /Users/anetreba/Desktop/uchat/server/src/json-c/json_visit.c

CMakeFiles/json-c.dir/json_visit.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/json-c.dir/json_visit.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/anetreba/Desktop/uchat/server/src/json-c/json_visit.c > CMakeFiles/json-c.dir/json_visit.c.i

CMakeFiles/json-c.dir/json_visit.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/json-c.dir/json_visit.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/anetreba/Desktop/uchat/server/src/json-c/json_visit.c -o CMakeFiles/json-c.dir/json_visit.c.s

CMakeFiles/json-c.dir/linkhash.c.o: CMakeFiles/json-c.dir/flags.make
CMakeFiles/json-c.dir/linkhash.c.o: /Users/anetreba/Desktop/uchat/server/src/json-c/linkhash.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/anetreba/Desktop/uchat/server/src/json-c-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building C object CMakeFiles/json-c.dir/linkhash.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/json-c.dir/linkhash.c.o   -c /Users/anetreba/Desktop/uchat/server/src/json-c/linkhash.c

CMakeFiles/json-c.dir/linkhash.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/json-c.dir/linkhash.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/anetreba/Desktop/uchat/server/src/json-c/linkhash.c > CMakeFiles/json-c.dir/linkhash.c.i

CMakeFiles/json-c.dir/linkhash.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/json-c.dir/linkhash.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/anetreba/Desktop/uchat/server/src/json-c/linkhash.c -o CMakeFiles/json-c.dir/linkhash.c.s

CMakeFiles/json-c.dir/printbuf.c.o: CMakeFiles/json-c.dir/flags.make
CMakeFiles/json-c.dir/printbuf.c.o: /Users/anetreba/Desktop/uchat/server/src/json-c/printbuf.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/anetreba/Desktop/uchat/server/src/json-c-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building C object CMakeFiles/json-c.dir/printbuf.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/json-c.dir/printbuf.c.o   -c /Users/anetreba/Desktop/uchat/server/src/json-c/printbuf.c

CMakeFiles/json-c.dir/printbuf.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/json-c.dir/printbuf.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/anetreba/Desktop/uchat/server/src/json-c/printbuf.c > CMakeFiles/json-c.dir/printbuf.c.i

CMakeFiles/json-c.dir/printbuf.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/json-c.dir/printbuf.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/anetreba/Desktop/uchat/server/src/json-c/printbuf.c -o CMakeFiles/json-c.dir/printbuf.c.s

CMakeFiles/json-c.dir/random_seed.c.o: CMakeFiles/json-c.dir/flags.make
CMakeFiles/json-c.dir/random_seed.c.o: /Users/anetreba/Desktop/uchat/server/src/json-c/random_seed.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/anetreba/Desktop/uchat/server/src/json-c-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building C object CMakeFiles/json-c.dir/random_seed.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/json-c.dir/random_seed.c.o   -c /Users/anetreba/Desktop/uchat/server/src/json-c/random_seed.c

CMakeFiles/json-c.dir/random_seed.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/json-c.dir/random_seed.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/anetreba/Desktop/uchat/server/src/json-c/random_seed.c > CMakeFiles/json-c.dir/random_seed.c.i

CMakeFiles/json-c.dir/random_seed.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/json-c.dir/random_seed.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/anetreba/Desktop/uchat/server/src/json-c/random_seed.c -o CMakeFiles/json-c.dir/random_seed.c.s

CMakeFiles/json-c.dir/strerror_override.c.o: CMakeFiles/json-c.dir/flags.make
CMakeFiles/json-c.dir/strerror_override.c.o: /Users/anetreba/Desktop/uchat/server/src/json-c/strerror_override.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/anetreba/Desktop/uchat/server/src/json-c-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Building C object CMakeFiles/json-c.dir/strerror_override.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/json-c.dir/strerror_override.c.o   -c /Users/anetreba/Desktop/uchat/server/src/json-c/strerror_override.c

CMakeFiles/json-c.dir/strerror_override.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/json-c.dir/strerror_override.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/anetreba/Desktop/uchat/server/src/json-c/strerror_override.c > CMakeFiles/json-c.dir/strerror_override.c.i

CMakeFiles/json-c.dir/strerror_override.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/json-c.dir/strerror_override.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/anetreba/Desktop/uchat/server/src/json-c/strerror_override.c -o CMakeFiles/json-c.dir/strerror_override.c.s

# Object files for target json-c
json__c_OBJECTS = \
"CMakeFiles/json-c.dir/arraylist.c.o" \
"CMakeFiles/json-c.dir/debug.c.o" \
"CMakeFiles/json-c.dir/json_c_version.c.o" \
"CMakeFiles/json-c.dir/json_object.c.o" \
"CMakeFiles/json-c.dir/json_object_iterator.c.o" \
"CMakeFiles/json-c.dir/json_pointer.c.o" \
"CMakeFiles/json-c.dir/json_tokener.c.o" \
"CMakeFiles/json-c.dir/json_util.c.o" \
"CMakeFiles/json-c.dir/json_visit.c.o" \
"CMakeFiles/json-c.dir/linkhash.c.o" \
"CMakeFiles/json-c.dir/printbuf.c.o" \
"CMakeFiles/json-c.dir/random_seed.c.o" \
"CMakeFiles/json-c.dir/strerror_override.c.o"

# External object files for target json-c
json__c_EXTERNAL_OBJECTS =

libjson-c.5.0.0.dylib: CMakeFiles/json-c.dir/arraylist.c.o
libjson-c.5.0.0.dylib: CMakeFiles/json-c.dir/debug.c.o
libjson-c.5.0.0.dylib: CMakeFiles/json-c.dir/json_c_version.c.o
libjson-c.5.0.0.dylib: CMakeFiles/json-c.dir/json_object.c.o
libjson-c.5.0.0.dylib: CMakeFiles/json-c.dir/json_object_iterator.c.o
libjson-c.5.0.0.dylib: CMakeFiles/json-c.dir/json_pointer.c.o
libjson-c.5.0.0.dylib: CMakeFiles/json-c.dir/json_tokener.c.o
libjson-c.5.0.0.dylib: CMakeFiles/json-c.dir/json_util.c.o
libjson-c.5.0.0.dylib: CMakeFiles/json-c.dir/json_visit.c.o
libjson-c.5.0.0.dylib: CMakeFiles/json-c.dir/linkhash.c.o
libjson-c.5.0.0.dylib: CMakeFiles/json-c.dir/printbuf.c.o
libjson-c.5.0.0.dylib: CMakeFiles/json-c.dir/random_seed.c.o
libjson-c.5.0.0.dylib: CMakeFiles/json-c.dir/strerror_override.c.o
libjson-c.5.0.0.dylib: CMakeFiles/json-c.dir/build.make
libjson-c.5.0.0.dylib: CMakeFiles/json-c.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/anetreba/Desktop/uchat/server/src/json-c-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_14) "Linking C shared library libjson-c.dylib"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/json-c.dir/link.txt --verbose=$(VERBOSE)
	$(CMAKE_COMMAND) -E cmake_symlink_library libjson-c.5.0.0.dylib libjson-c.5.dylib libjson-c.dylib

libjson-c.5.dylib: libjson-c.5.0.0.dylib
	@$(CMAKE_COMMAND) -E touch_nocreate libjson-c.5.dylib

libjson-c.dylib: libjson-c.5.0.0.dylib
	@$(CMAKE_COMMAND) -E touch_nocreate libjson-c.dylib

# Rule to build all files generated by this target.
CMakeFiles/json-c.dir/build: libjson-c.dylib

.PHONY : CMakeFiles/json-c.dir/build

CMakeFiles/json-c.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/json-c.dir/cmake_clean.cmake
.PHONY : CMakeFiles/json-c.dir/clean

CMakeFiles/json-c.dir/depend:
	cd /Users/anetreba/Desktop/uchat/server/src/json-c-build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/anetreba/Desktop/uchat/server/src/json-c /Users/anetreba/Desktop/uchat/server/src/json-c /Users/anetreba/Desktop/uchat/server/src/json-c-build /Users/anetreba/Desktop/uchat/server/src/json-c-build /Users/anetreba/Desktop/uchat/server/src/json-c-build/CMakeFiles/json-c.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/json-c.dir/depend

