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
CMAKE_SOURCE_DIR = /home/rafik/flair/flair-src/demos/SquareFleet/uav

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/rafik/flair/flair-src/demos/SquareFleet/uav/build

# Include any dependencies generated for this target.
include CMakeFiles/SquareFleet_nrt.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/SquareFleet_nrt.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/SquareFleet_nrt.dir/flags.make

CMakeFiles/SquareFleet_nrt.dir/src/main.cpp.o: CMakeFiles/SquareFleet_nrt.dir/flags.make
CMakeFiles/SquareFleet_nrt.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/rafik/flair/flair-src/demos/SquareFleet/uav/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/SquareFleet_nrt.dir/src/main.cpp.o"
	/opt/robomap3/1.7.3/core2-64/sysroots/x86_64-pokysdk-linux/usr/bin/x86_64-poky-linux/x86_64-poky-linux-g++  --sysroot=/opt/robomap3/1.7.3/core2-64/sysroots/core2-64-poky-linux  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/SquareFleet_nrt.dir/src/main.cpp.o -c /home/rafik/flair/flair-src/demos/SquareFleet/uav/src/main.cpp

CMakeFiles/SquareFleet_nrt.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SquareFleet_nrt.dir/src/main.cpp.i"
	/opt/robomap3/1.7.3/core2-64/sysroots/x86_64-pokysdk-linux/usr/bin/x86_64-poky-linux/x86_64-poky-linux-g++  --sysroot=/opt/robomap3/1.7.3/core2-64/sysroots/core2-64-poky-linux $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/rafik/flair/flair-src/demos/SquareFleet/uav/src/main.cpp > CMakeFiles/SquareFleet_nrt.dir/src/main.cpp.i

CMakeFiles/SquareFleet_nrt.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SquareFleet_nrt.dir/src/main.cpp.s"
	/opt/robomap3/1.7.3/core2-64/sysroots/x86_64-pokysdk-linux/usr/bin/x86_64-poky-linux/x86_64-poky-linux-g++  --sysroot=/opt/robomap3/1.7.3/core2-64/sysroots/core2-64-poky-linux $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/rafik/flair/flair-src/demos/SquareFleet/uav/src/main.cpp -o CMakeFiles/SquareFleet_nrt.dir/src/main.cpp.s

CMakeFiles/SquareFleet_nrt.dir/src/main.cpp.o.requires:

.PHONY : CMakeFiles/SquareFleet_nrt.dir/src/main.cpp.o.requires

CMakeFiles/SquareFleet_nrt.dir/src/main.cpp.o.provides: CMakeFiles/SquareFleet_nrt.dir/src/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/SquareFleet_nrt.dir/build.make CMakeFiles/SquareFleet_nrt.dir/src/main.cpp.o.provides.build
.PHONY : CMakeFiles/SquareFleet_nrt.dir/src/main.cpp.o.provides

CMakeFiles/SquareFleet_nrt.dir/src/main.cpp.o.provides.build: CMakeFiles/SquareFleet_nrt.dir/src/main.cpp.o


CMakeFiles/SquareFleet_nrt.dir/src/SquareFleet.cpp.o: CMakeFiles/SquareFleet_nrt.dir/flags.make
CMakeFiles/SquareFleet_nrt.dir/src/SquareFleet.cpp.o: ../src/SquareFleet.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/rafik/flair/flair-src/demos/SquareFleet/uav/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/SquareFleet_nrt.dir/src/SquareFleet.cpp.o"
	/opt/robomap3/1.7.3/core2-64/sysroots/x86_64-pokysdk-linux/usr/bin/x86_64-poky-linux/x86_64-poky-linux-g++  --sysroot=/opt/robomap3/1.7.3/core2-64/sysroots/core2-64-poky-linux  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/SquareFleet_nrt.dir/src/SquareFleet.cpp.o -c /home/rafik/flair/flair-src/demos/SquareFleet/uav/src/SquareFleet.cpp

CMakeFiles/SquareFleet_nrt.dir/src/SquareFleet.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SquareFleet_nrt.dir/src/SquareFleet.cpp.i"
	/opt/robomap3/1.7.3/core2-64/sysroots/x86_64-pokysdk-linux/usr/bin/x86_64-poky-linux/x86_64-poky-linux-g++  --sysroot=/opt/robomap3/1.7.3/core2-64/sysroots/core2-64-poky-linux $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/rafik/flair/flair-src/demos/SquareFleet/uav/src/SquareFleet.cpp > CMakeFiles/SquareFleet_nrt.dir/src/SquareFleet.cpp.i

CMakeFiles/SquareFleet_nrt.dir/src/SquareFleet.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SquareFleet_nrt.dir/src/SquareFleet.cpp.s"
	/opt/robomap3/1.7.3/core2-64/sysroots/x86_64-pokysdk-linux/usr/bin/x86_64-poky-linux/x86_64-poky-linux-g++  --sysroot=/opt/robomap3/1.7.3/core2-64/sysroots/core2-64-poky-linux $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/rafik/flair/flair-src/demos/SquareFleet/uav/src/SquareFleet.cpp -o CMakeFiles/SquareFleet_nrt.dir/src/SquareFleet.cpp.s

CMakeFiles/SquareFleet_nrt.dir/src/SquareFleet.cpp.o.requires:

.PHONY : CMakeFiles/SquareFleet_nrt.dir/src/SquareFleet.cpp.o.requires

CMakeFiles/SquareFleet_nrt.dir/src/SquareFleet.cpp.o.provides: CMakeFiles/SquareFleet_nrt.dir/src/SquareFleet.cpp.o.requires
	$(MAKE) -f CMakeFiles/SquareFleet_nrt.dir/build.make CMakeFiles/SquareFleet_nrt.dir/src/SquareFleet.cpp.o.provides.build
.PHONY : CMakeFiles/SquareFleet_nrt.dir/src/SquareFleet.cpp.o.provides

CMakeFiles/SquareFleet_nrt.dir/src/SquareFleet.cpp.o.provides.build: CMakeFiles/SquareFleet_nrt.dir/src/SquareFleet.cpp.o


# Object files for target SquareFleet_nrt
SquareFleet_nrt_OBJECTS = \
"CMakeFiles/SquareFleet_nrt.dir/src/main.cpp.o" \
"CMakeFiles/SquareFleet_nrt.dir/src/SquareFleet.cpp.o"

# External object files for target SquareFleet_nrt
SquareFleet_nrt_EXTERNAL_OBJECTS =

bin/SquareFleet_nrt: CMakeFiles/SquareFleet_nrt.dir/src/main.cpp.o
bin/SquareFleet_nrt: CMakeFiles/SquareFleet_nrt.dir/src/SquareFleet.cpp.o
bin/SquareFleet_nrt: CMakeFiles/SquareFleet_nrt.dir/build.make
bin/SquareFleet_nrt: /home/rafik/flair/flair-bin/lib/x86_64/unix/libFlairMeta.a
bin/SquareFleet_nrt: /home/rafik/flair/flair-bin/lib/x86_64/unix/libFlairFilter.a
bin/SquareFleet_nrt: /home/rafik/flair/flair-bin/lib/x86_64/unix/libFlairSensorActuator.a
bin/SquareFleet_nrt: /home/rafik/flair/flair-bin/lib/x86_64/unix/libFlairCore_nrt.a
bin/SquareFleet_nrt: /opt/robomap3/1.7.3/core2-64/sysroots/core2-64-poky-linux/usr/lib/libxml2.so
bin/SquareFleet_nrt: CMakeFiles/SquareFleet_nrt.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/rafik/flair/flair-src/demos/SquareFleet/uav/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable bin/SquareFleet_nrt"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/SquareFleet_nrt.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/SquareFleet_nrt.dir/build: bin/SquareFleet_nrt

.PHONY : CMakeFiles/SquareFleet_nrt.dir/build

CMakeFiles/SquareFleet_nrt.dir/requires: CMakeFiles/SquareFleet_nrt.dir/src/main.cpp.o.requires
CMakeFiles/SquareFleet_nrt.dir/requires: CMakeFiles/SquareFleet_nrt.dir/src/SquareFleet.cpp.o.requires

.PHONY : CMakeFiles/SquareFleet_nrt.dir/requires

CMakeFiles/SquareFleet_nrt.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/SquareFleet_nrt.dir/cmake_clean.cmake
.PHONY : CMakeFiles/SquareFleet_nrt.dir/clean

CMakeFiles/SquareFleet_nrt.dir/depend:
	cd /home/rafik/flair/flair-src/demos/SquareFleet/uav/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/rafik/flair/flair-src/demos/SquareFleet/uav /home/rafik/flair/flair-src/demos/SquareFleet/uav /home/rafik/flair/flair-src/demos/SquareFleet/uav/build /home/rafik/flair/flair-src/demos/SquareFleet/uav/build /home/rafik/flair/flair-src/demos/SquareFleet/uav/build/CMakeFiles/SquareFleet_nrt.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/SquareFleet_nrt.dir/depend

