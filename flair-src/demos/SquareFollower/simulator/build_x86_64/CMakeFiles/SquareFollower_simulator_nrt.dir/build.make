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
CMAKE_SOURCE_DIR = /home/rafik/flair/flair-src/demos/SquareFollower/simulator

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/rafik/flair/flair-src/demos/SquareFollower/simulator/build

# Include any dependencies generated for this target.
include CMakeFiles/SquareFollower_simulator_nrt.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/SquareFollower_simulator_nrt.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/SquareFollower_simulator_nrt.dir/flags.make

CMakeFiles/SquareFollower_simulator_nrt.dir/src/main.cpp.o: CMakeFiles/SquareFollower_simulator_nrt.dir/flags.make
CMakeFiles/SquareFollower_simulator_nrt.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/rafik/flair/flair-src/demos/SquareFollower/simulator/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/SquareFollower_simulator_nrt.dir/src/main.cpp.o"
	/opt/robomap3/1.7.3/core2-64/sysroots/x86_64-pokysdk-linux/usr/bin/x86_64-poky-linux/x86_64-poky-linux-g++  --sysroot=/opt/robomap3/1.7.3/core2-64/sysroots/core2-64-poky-linux  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/SquareFollower_simulator_nrt.dir/src/main.cpp.o -c /home/rafik/flair/flair-src/demos/SquareFollower/simulator/src/main.cpp

CMakeFiles/SquareFollower_simulator_nrt.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SquareFollower_simulator_nrt.dir/src/main.cpp.i"
	/opt/robomap3/1.7.3/core2-64/sysroots/x86_64-pokysdk-linux/usr/bin/x86_64-poky-linux/x86_64-poky-linux-g++  --sysroot=/opt/robomap3/1.7.3/core2-64/sysroots/core2-64-poky-linux $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/rafik/flair/flair-src/demos/SquareFollower/simulator/src/main.cpp > CMakeFiles/SquareFollower_simulator_nrt.dir/src/main.cpp.i

CMakeFiles/SquareFollower_simulator_nrt.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SquareFollower_simulator_nrt.dir/src/main.cpp.s"
	/opt/robomap3/1.7.3/core2-64/sysroots/x86_64-pokysdk-linux/usr/bin/x86_64-poky-linux/x86_64-poky-linux-g++  --sysroot=/opt/robomap3/1.7.3/core2-64/sysroots/core2-64-poky-linux $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/rafik/flair/flair-src/demos/SquareFollower/simulator/src/main.cpp -o CMakeFiles/SquareFollower_simulator_nrt.dir/src/main.cpp.s

CMakeFiles/SquareFollower_simulator_nrt.dir/src/main.cpp.o.requires:

.PHONY : CMakeFiles/SquareFollower_simulator_nrt.dir/src/main.cpp.o.requires

CMakeFiles/SquareFollower_simulator_nrt.dir/src/main.cpp.o.provides: CMakeFiles/SquareFollower_simulator_nrt.dir/src/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/SquareFollower_simulator_nrt.dir/build.make CMakeFiles/SquareFollower_simulator_nrt.dir/src/main.cpp.o.provides.build
.PHONY : CMakeFiles/SquareFollower_simulator_nrt.dir/src/main.cpp.o.provides

CMakeFiles/SquareFollower_simulator_nrt.dir/src/main.cpp.o.provides.build: CMakeFiles/SquareFollower_simulator_nrt.dir/src/main.cpp.o


# Object files for target SquareFollower_simulator_nrt
SquareFollower_simulator_nrt_OBJECTS = \
"CMakeFiles/SquareFollower_simulator_nrt.dir/src/main.cpp.o"

# External object files for target SquareFollower_simulator_nrt
SquareFollower_simulator_nrt_EXTERNAL_OBJECTS =

bin/SquareFollower_simulator_nrt: CMakeFiles/SquareFollower_simulator_nrt.dir/src/main.cpp.o
bin/SquareFollower_simulator_nrt: CMakeFiles/SquareFollower_simulator_nrt.dir/build.make
bin/SquareFollower_simulator_nrt: /home/rafik/flair/flair-bin/lib/x86_64/unix/libFlairSimulator_gl.a
bin/SquareFollower_simulator_nrt: /home/rafik/flair/flair-bin/lib/x86_64/unix/libFlairSensorActuator.a
bin/SquareFollower_simulator_nrt: /home/rafik/flair/flair-bin/lib/x86_64/unix/libFlairCore_nrt.a
bin/SquareFollower_simulator_nrt: /opt/robomap3/1.7.3/core2-64/sysroots/core2-64-poky-linux/usr/lib/libxml2.so
bin/SquareFollower_simulator_nrt: CMakeFiles/SquareFollower_simulator_nrt.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/rafik/flair/flair-src/demos/SquareFollower/simulator/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable bin/SquareFollower_simulator_nrt"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/SquareFollower_simulator_nrt.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/SquareFollower_simulator_nrt.dir/build: bin/SquareFollower_simulator_nrt

.PHONY : CMakeFiles/SquareFollower_simulator_nrt.dir/build

CMakeFiles/SquareFollower_simulator_nrt.dir/requires: CMakeFiles/SquareFollower_simulator_nrt.dir/src/main.cpp.o.requires

.PHONY : CMakeFiles/SquareFollower_simulator_nrt.dir/requires

CMakeFiles/SquareFollower_simulator_nrt.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/SquareFollower_simulator_nrt.dir/cmake_clean.cmake
.PHONY : CMakeFiles/SquareFollower_simulator_nrt.dir/clean

CMakeFiles/SquareFollower_simulator_nrt.dir/depend:
	cd /home/rafik/flair/flair-src/demos/SquareFollower/simulator/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/rafik/flair/flair-src/demos/SquareFollower/simulator /home/rafik/flair/flair-src/demos/SquareFollower/simulator /home/rafik/flair/flair-src/demos/SquareFollower/simulator/build /home/rafik/flair/flair-src/demos/SquareFollower/simulator/build /home/rafik/flair/flair-src/demos/SquareFollower/simulator/build/CMakeFiles/SquareFollower_simulator_nrt.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/SquareFollower_simulator_nrt.dir/depend

