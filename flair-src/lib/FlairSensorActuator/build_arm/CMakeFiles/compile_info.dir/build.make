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
CMAKE_SOURCE_DIR = /home/rafik/flair/flair-src/lib/FlairSensorActuator

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/rafik/flair/flair-src/lib/FlairSensorActuator/build_arm

# Utility rule file for compile_info.

# Include the progress variables for this target.
include CMakeFiles/compile_info.dir/progress.make

CMakeFiles/compile_info:
	/home/rafik/flair/flair-dev/scripts/compile_info.sh /opt/robomap3/1.7.3/armv7a-neon/sysroots/x86_64-pokysdk-linux/usr/bin/arm-poky-linux-gnueabi/arm-poky-linux-gnueabi-gcc /home/rafik/flair/flair-src/lib/FlairSensorActuator /home/rafik/flair/flair-src/lib/FlairSensorActuator/src/unexported/compile_info.h

compile_info: CMakeFiles/compile_info
compile_info: CMakeFiles/compile_info.dir/build.make

.PHONY : compile_info

# Rule to build all files generated by this target.
CMakeFiles/compile_info.dir/build: compile_info

.PHONY : CMakeFiles/compile_info.dir/build

CMakeFiles/compile_info.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/compile_info.dir/cmake_clean.cmake
.PHONY : CMakeFiles/compile_info.dir/clean

CMakeFiles/compile_info.dir/depend:
	cd /home/rafik/flair/flair-src/lib/FlairSensorActuator/build_arm && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/rafik/flair/flair-src/lib/FlairSensorActuator /home/rafik/flair/flair-src/lib/FlairSensorActuator /home/rafik/flair/flair-src/lib/FlairSensorActuator/build_arm /home/rafik/flair/flair-src/lib/FlairSensorActuator/build_arm /home/rafik/flair/flair-src/lib/FlairSensorActuator/build_arm/CMakeFiles/compile_info.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/compile_info.dir/depend

