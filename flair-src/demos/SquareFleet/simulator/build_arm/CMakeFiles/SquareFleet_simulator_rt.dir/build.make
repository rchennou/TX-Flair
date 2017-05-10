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
CMAKE_SOURCE_DIR = /home/rafik/flair/flair-src/demos/SquareFleet/simulator

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/rafik/flair/flair-src/demos/SquareFleet/simulator/build_arm

# Include any dependencies generated for this target.
include CMakeFiles/SquareFleet_simulator_rt.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/SquareFleet_simulator_rt.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/SquareFleet_simulator_rt.dir/flags.make

CMakeFiles/SquareFleet_simulator_rt.dir/src/main.cpp.o: CMakeFiles/SquareFleet_simulator_rt.dir/flags.make
CMakeFiles/SquareFleet_simulator_rt.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/rafik/flair/flair-src/demos/SquareFleet/simulator/build_arm/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/SquareFleet_simulator_rt.dir/src/main.cpp.o"
	/opt/robomap3/1.7.3/armv7a-neon/sysroots/x86_64-pokysdk-linux/usr/bin/arm-poky-linux-gnueabi/arm-poky-linux-gnueabi-g++  --sysroot=/opt/robomap3/1.7.3/armv7a-neon/sysroots/armv7a-vfp-neon-poky-linux-gnueabi  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/SquareFleet_simulator_rt.dir/src/main.cpp.o -c /home/rafik/flair/flair-src/demos/SquareFleet/simulator/src/main.cpp

CMakeFiles/SquareFleet_simulator_rt.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SquareFleet_simulator_rt.dir/src/main.cpp.i"
	/opt/robomap3/1.7.3/armv7a-neon/sysroots/x86_64-pokysdk-linux/usr/bin/arm-poky-linux-gnueabi/arm-poky-linux-gnueabi-g++  --sysroot=/opt/robomap3/1.7.3/armv7a-neon/sysroots/armv7a-vfp-neon-poky-linux-gnueabi $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/rafik/flair/flair-src/demos/SquareFleet/simulator/src/main.cpp > CMakeFiles/SquareFleet_simulator_rt.dir/src/main.cpp.i

CMakeFiles/SquareFleet_simulator_rt.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SquareFleet_simulator_rt.dir/src/main.cpp.s"
	/opt/robomap3/1.7.3/armv7a-neon/sysroots/x86_64-pokysdk-linux/usr/bin/arm-poky-linux-gnueabi/arm-poky-linux-gnueabi-g++  --sysroot=/opt/robomap3/1.7.3/armv7a-neon/sysroots/armv7a-vfp-neon-poky-linux-gnueabi $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/rafik/flair/flair-src/demos/SquareFleet/simulator/src/main.cpp -o CMakeFiles/SquareFleet_simulator_rt.dir/src/main.cpp.s

CMakeFiles/SquareFleet_simulator_rt.dir/src/main.cpp.o.requires:

.PHONY : CMakeFiles/SquareFleet_simulator_rt.dir/src/main.cpp.o.requires

CMakeFiles/SquareFleet_simulator_rt.dir/src/main.cpp.o.provides: CMakeFiles/SquareFleet_simulator_rt.dir/src/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/SquareFleet_simulator_rt.dir/build.make CMakeFiles/SquareFleet_simulator_rt.dir/src/main.cpp.o.provides.build
.PHONY : CMakeFiles/SquareFleet_simulator_rt.dir/src/main.cpp.o.provides

CMakeFiles/SquareFleet_simulator_rt.dir/src/main.cpp.o.provides.build: CMakeFiles/SquareFleet_simulator_rt.dir/src/main.cpp.o


# Object files for target SquareFleet_simulator_rt
SquareFleet_simulator_rt_OBJECTS = \
"CMakeFiles/SquareFleet_simulator_rt.dir/src/main.cpp.o"

# External object files for target SquareFleet_simulator_rt
SquareFleet_simulator_rt_EXTERNAL_OBJECTS =

bin/SquareFleet_simulator_rt: CMakeFiles/SquareFleet_simulator_rt.dir/src/main.cpp.o
bin/SquareFleet_simulator_rt: CMakeFiles/SquareFleet_simulator_rt.dir/build.make
bin/SquareFleet_simulator_rt: /home/rafik/flair/flair-bin/lib/arm/libFlairSimulator_nogl.a
bin/SquareFleet_simulator_rt: /home/rafik/flair/flair-bin/lib/arm/libFlairSensorActuator.a
bin/SquareFleet_simulator_rt: /home/rafik/flair/flair-bin/lib/arm/libFlairCore_rt.a
bin/SquareFleet_simulator_rt: /opt/robomap3/1.7.3/armv7a-neon/sysroots/armv7a-vfp-neon-poky-linux-gnueabi/usr/lib/libxml2.so
bin/SquareFleet_simulator_rt: /opt/robomap3/1.7.3/armv7a-neon/sysroots/armv7a-vfp-neon-poky-linux-gnueabi/usr/lib/librtdm.so
bin/SquareFleet_simulator_rt: /opt/robomap3/1.7.3/armv7a-neon/sysroots/armv7a-vfp-neon-poky-linux-gnueabi/usr/lib/libnative.so
bin/SquareFleet_simulator_rt: /opt/robomap3/1.7.3/armv7a-neon/sysroots/armv7a-vfp-neon-poky-linux-gnueabi/usr/lib/libxenomai.so
bin/SquareFleet_simulator_rt: CMakeFiles/SquareFleet_simulator_rt.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/rafik/flair/flair-src/demos/SquareFleet/simulator/build_arm/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable bin/SquareFleet_simulator_rt"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/SquareFleet_simulator_rt.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/SquareFleet_simulator_rt.dir/build: bin/SquareFleet_simulator_rt

.PHONY : CMakeFiles/SquareFleet_simulator_rt.dir/build

CMakeFiles/SquareFleet_simulator_rt.dir/requires: CMakeFiles/SquareFleet_simulator_rt.dir/src/main.cpp.o.requires

.PHONY : CMakeFiles/SquareFleet_simulator_rt.dir/requires

CMakeFiles/SquareFleet_simulator_rt.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/SquareFleet_simulator_rt.dir/cmake_clean.cmake
.PHONY : CMakeFiles/SquareFleet_simulator_rt.dir/clean

CMakeFiles/SquareFleet_simulator_rt.dir/depend:
	cd /home/rafik/flair/flair-src/demos/SquareFleet/simulator/build_arm && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/rafik/flair/flair-src/demos/SquareFleet/simulator /home/rafik/flair/flair-src/demos/SquareFleet/simulator /home/rafik/flair/flair-src/demos/SquareFleet/simulator/build_arm /home/rafik/flair/flair-src/demos/SquareFleet/simulator/build_arm /home/rafik/flair/flair-src/demos/SquareFleet/simulator/build_arm/CMakeFiles/SquareFleet_simulator_rt.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/SquareFleet_simulator_rt.dir/depend

