# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.0

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/votol/Programming/skach_fish/fish4/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/votol/Programming/skach_fish/fish4/build

# Include any dependencies generated for this target.
include CMakeFiles/t.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/t.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/t.dir/flags.make

CMakeFiles/t.dir/main.cpp.o: CMakeFiles/t.dir/flags.make
CMakeFiles/t.dir/main.cpp.o: /home/votol/Programming/skach_fish/fish4/src/main.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/votol/Programming/skach_fish/fish4/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/t.dir/main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/t.dir/main.cpp.o -c /home/votol/Programming/skach_fish/fish4/src/main.cpp

CMakeFiles/t.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/t.dir/main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/votol/Programming/skach_fish/fish4/src/main.cpp > CMakeFiles/t.dir/main.cpp.i

CMakeFiles/t.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/t.dir/main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/votol/Programming/skach_fish/fish4/src/main.cpp -o CMakeFiles/t.dir/main.cpp.s

CMakeFiles/t.dir/main.cpp.o.requires:
.PHONY : CMakeFiles/t.dir/main.cpp.o.requires

CMakeFiles/t.dir/main.cpp.o.provides: CMakeFiles/t.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/t.dir/build.make CMakeFiles/t.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/t.dir/main.cpp.o.provides

CMakeFiles/t.dir/main.cpp.o.provides.build: CMakeFiles/t.dir/main.cpp.o

# Object files for target t
t_OBJECTS = \
"CMakeFiles/t.dir/main.cpp.o"

# External object files for target t
t_EXTERNAL_OBJECTS =

/home/votol/Programming/skach_fish/fish4/bin/debug/t: CMakeFiles/t.dir/main.cpp.o
/home/votol/Programming/skach_fish/fish4/bin/debug/t: CMakeFiles/t.dir/build.make
/home/votol/Programming/skach_fish/fish4/bin/debug/t: /usr/local/cuda/lib64/libcudart.so
/home/votol/Programming/skach_fish/fish4/bin/debug/t: CMakeFiles/t.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable /home/votol/Programming/skach_fish/fish4/bin/debug/t"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/t.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/t.dir/build: /home/votol/Programming/skach_fish/fish4/bin/debug/t
.PHONY : CMakeFiles/t.dir/build

CMakeFiles/t.dir/requires: CMakeFiles/t.dir/main.cpp.o.requires
.PHONY : CMakeFiles/t.dir/requires

CMakeFiles/t.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/t.dir/cmake_clean.cmake
.PHONY : CMakeFiles/t.dir/clean

CMakeFiles/t.dir/depend:
	cd /home/votol/Programming/skach_fish/fish4/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/votol/Programming/skach_fish/fish4/src /home/votol/Programming/skach_fish/fish4/src /home/votol/Programming/skach_fish/fish4/build /home/votol/Programming/skach_fish/fish4/build /home/votol/Programming/skach_fish/fish4/build/CMakeFiles/t.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/t.dir/depend

