# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.7

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


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
CMAKE_COMMAND = /opt/robomap3/1.7.3/core2-64/sysroots/x86_64-pokysdk-linux/usr/bin/cmake

# The command to remove a file.
RM = /opt/robomap3/1.7.3/core2-64/sysroots/x86_64-pokysdk-linux/usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/rafik/flair/flair-src/demos/HelloWorld

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/rafik/flair/flair-src/demos/HelloWorld/build

# Utility rule file for delivery.

# Include the progress variables for this target.
include CMakeFiles/delivery.dir/progress.make

CMakeFiles/delivery:
	make
	scp bin/HelloWorld root@192.168.6.1:/home/root/

delivery: CMakeFiles/delivery
delivery: CMakeFiles/delivery.dir/build.make

.PHONY : delivery

# Rule to build all files generated by this target.
CMakeFiles/delivery.dir/build: delivery

.PHONY : CMakeFiles/delivery.dir/build

CMakeFiles/delivery.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/delivery.dir/cmake_clean.cmake
.PHONY : CMakeFiles/delivery.dir/clean

CMakeFiles/delivery.dir/depend:
	cd /home/rafik/flair/flair-src/demos/HelloWorld/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/rafik/flair/flair-src/demos/HelloWorld /home/rafik/flair/flair-src/demos/HelloWorld /home/rafik/flair/flair-src/demos/HelloWorld/build /home/rafik/flair/flair-src/demos/HelloWorld/build /home/rafik/flair/flair-src/demos/HelloWorld/build/CMakeFiles/delivery.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/delivery.dir/depend
