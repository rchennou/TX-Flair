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
CMAKE_SOURCE_DIR = /home/sofiane/flair/flair-src/demos/LineFollower/uav

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/sofiane/flair/flair-src/demos/LineFollower/uav/build

# Include any dependencies generated for this target.
include CMakeFiles/LineFollower_nrt.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/LineFollower_nrt.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/LineFollower_nrt.dir/flags.make

CMakeFiles/LineFollower_nrt.dir/src/main.cpp.o: CMakeFiles/LineFollower_nrt.dir/flags.make
CMakeFiles/LineFollower_nrt.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sofiane/flair/flair-src/demos/LineFollower/uav/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/LineFollower_nrt.dir/src/main.cpp.o"
	/opt/robomap3/1.7.3/core2-64/sysroots/x86_64-pokysdk-linux/usr/bin/x86_64-poky-linux/x86_64-poky-linux-g++  --sysroot=/opt/robomap3/1.7.3/core2-64/sysroots/core2-64-poky-linux  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/LineFollower_nrt.dir/src/main.cpp.o -c /home/sofiane/flair/flair-src/demos/LineFollower/uav/src/main.cpp

CMakeFiles/LineFollower_nrt.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/LineFollower_nrt.dir/src/main.cpp.i"
	/opt/robomap3/1.7.3/core2-64/sysroots/x86_64-pokysdk-linux/usr/bin/x86_64-poky-linux/x86_64-poky-linux-g++  --sysroot=/opt/robomap3/1.7.3/core2-64/sysroots/core2-64-poky-linux $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sofiane/flair/flair-src/demos/LineFollower/uav/src/main.cpp > CMakeFiles/LineFollower_nrt.dir/src/main.cpp.i

CMakeFiles/LineFollower_nrt.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/LineFollower_nrt.dir/src/main.cpp.s"
	/opt/robomap3/1.7.3/core2-64/sysroots/x86_64-pokysdk-linux/usr/bin/x86_64-poky-linux/x86_64-poky-linux-g++  --sysroot=/opt/robomap3/1.7.3/core2-64/sysroots/core2-64-poky-linux $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sofiane/flair/flair-src/demos/LineFollower/uav/src/main.cpp -o CMakeFiles/LineFollower_nrt.dir/src/main.cpp.s

CMakeFiles/LineFollower_nrt.dir/src/main.cpp.o.requires:

.PHONY : CMakeFiles/LineFollower_nrt.dir/src/main.cpp.o.requires

CMakeFiles/LineFollower_nrt.dir/src/main.cpp.o.provides: CMakeFiles/LineFollower_nrt.dir/src/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/LineFollower_nrt.dir/build.make CMakeFiles/LineFollower_nrt.dir/src/main.cpp.o.provides.build
.PHONY : CMakeFiles/LineFollower_nrt.dir/src/main.cpp.o.provides

CMakeFiles/LineFollower_nrt.dir/src/main.cpp.o.provides.build: CMakeFiles/LineFollower_nrt.dir/src/main.cpp.o


CMakeFiles/LineFollower_nrt.dir/src/LineFollower.cpp.o: CMakeFiles/LineFollower_nrt.dir/flags.make
CMakeFiles/LineFollower_nrt.dir/src/LineFollower.cpp.o: ../src/LineFollower.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sofiane/flair/flair-src/demos/LineFollower/uav/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/LineFollower_nrt.dir/src/LineFollower.cpp.o"
	/opt/robomap3/1.7.3/core2-64/sysroots/x86_64-pokysdk-linux/usr/bin/x86_64-poky-linux/x86_64-poky-linux-g++  --sysroot=/opt/robomap3/1.7.3/core2-64/sysroots/core2-64-poky-linux  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/LineFollower_nrt.dir/src/LineFollower.cpp.o -c /home/sofiane/flair/flair-src/demos/LineFollower/uav/src/LineFollower.cpp

CMakeFiles/LineFollower_nrt.dir/src/LineFollower.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/LineFollower_nrt.dir/src/LineFollower.cpp.i"
	/opt/robomap3/1.7.3/core2-64/sysroots/x86_64-pokysdk-linux/usr/bin/x86_64-poky-linux/x86_64-poky-linux-g++  --sysroot=/opt/robomap3/1.7.3/core2-64/sysroots/core2-64-poky-linux $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sofiane/flair/flair-src/demos/LineFollower/uav/src/LineFollower.cpp > CMakeFiles/LineFollower_nrt.dir/src/LineFollower.cpp.i

CMakeFiles/LineFollower_nrt.dir/src/LineFollower.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/LineFollower_nrt.dir/src/LineFollower.cpp.s"
	/opt/robomap3/1.7.3/core2-64/sysroots/x86_64-pokysdk-linux/usr/bin/x86_64-poky-linux/x86_64-poky-linux-g++  --sysroot=/opt/robomap3/1.7.3/core2-64/sysroots/core2-64-poky-linux $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sofiane/flair/flair-src/demos/LineFollower/uav/src/LineFollower.cpp -o CMakeFiles/LineFollower_nrt.dir/src/LineFollower.cpp.s

CMakeFiles/LineFollower_nrt.dir/src/LineFollower.cpp.o.requires:

.PHONY : CMakeFiles/LineFollower_nrt.dir/src/LineFollower.cpp.o.requires

CMakeFiles/LineFollower_nrt.dir/src/LineFollower.cpp.o.provides: CMakeFiles/LineFollower_nrt.dir/src/LineFollower.cpp.o.requires
	$(MAKE) -f CMakeFiles/LineFollower_nrt.dir/build.make CMakeFiles/LineFollower_nrt.dir/src/LineFollower.cpp.o.provides.build
.PHONY : CMakeFiles/LineFollower_nrt.dir/src/LineFollower.cpp.o.provides

CMakeFiles/LineFollower_nrt.dir/src/LineFollower.cpp.o.provides.build: CMakeFiles/LineFollower_nrt.dir/src/LineFollower.cpp.o


# Object files for target LineFollower_nrt
LineFollower_nrt_OBJECTS = \
"CMakeFiles/LineFollower_nrt.dir/src/main.cpp.o" \
"CMakeFiles/LineFollower_nrt.dir/src/LineFollower.cpp.o"

# External object files for target LineFollower_nrt
LineFollower_nrt_EXTERNAL_OBJECTS =

bin/LineFollower_nrt: CMakeFiles/LineFollower_nrt.dir/src/main.cpp.o
bin/LineFollower_nrt: CMakeFiles/LineFollower_nrt.dir/src/LineFollower.cpp.o
bin/LineFollower_nrt: CMakeFiles/LineFollower_nrt.dir/build.make
bin/LineFollower_nrt: /home/sofiane/flair/flair-bin/lib/x86_64/unix/libFlairMeta.a
bin/LineFollower_nrt: /home/sofiane/flair/flair-bin/lib/x86_64/unix/libFlairFilter.a
bin/LineFollower_nrt: /home/sofiane/flair/flair-bin/lib/x86_64/unix/libFlairSensorActuator.a
bin/LineFollower_nrt: /home/sofiane/flair/flair-bin/lib/x86_64/unix/libFlairCore_nrt.a
bin/LineFollower_nrt: /opt/robomap3/1.7.3/core2-64/sysroots/core2-64-poky-linux/usr/lib/libxml2.so
bin/LineFollower_nrt: CMakeFiles/LineFollower_nrt.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/sofiane/flair/flair-src/demos/LineFollower/uav/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable bin/LineFollower_nrt"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/LineFollower_nrt.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/LineFollower_nrt.dir/build: bin/LineFollower_nrt

.PHONY : CMakeFiles/LineFollower_nrt.dir/build

CMakeFiles/LineFollower_nrt.dir/requires: CMakeFiles/LineFollower_nrt.dir/src/main.cpp.o.requires
CMakeFiles/LineFollower_nrt.dir/requires: CMakeFiles/LineFollower_nrt.dir/src/LineFollower.cpp.o.requires

.PHONY : CMakeFiles/LineFollower_nrt.dir/requires

CMakeFiles/LineFollower_nrt.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/LineFollower_nrt.dir/cmake_clean.cmake
.PHONY : CMakeFiles/LineFollower_nrt.dir/clean

CMakeFiles/LineFollower_nrt.dir/depend:
	cd /home/sofiane/flair/flair-src/demos/LineFollower/uav/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/sofiane/flair/flair-src/demos/LineFollower/uav /home/sofiane/flair/flair-src/demos/LineFollower/uav /home/sofiane/flair/flair-src/demos/LineFollower/uav/build /home/sofiane/flair/flair-src/demos/LineFollower/uav/build /home/sofiane/flair/flair-src/demos/LineFollower/uav/build/CMakeFiles/LineFollower_nrt.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/LineFollower_nrt.dir/depend

