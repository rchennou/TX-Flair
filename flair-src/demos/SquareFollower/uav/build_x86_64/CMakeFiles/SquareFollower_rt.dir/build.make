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
CMAKE_SOURCE_DIR = /home/rafik/flair/flair-src/demos/SquareFollower/uav

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/rafik/flair/flair-src/demos/SquareFollower/uav/build

# Include any dependencies generated for this target.
include CMakeFiles/SquareFollower_rt.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/SquareFollower_rt.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/SquareFollower_rt.dir/flags.make

CMakeFiles/SquareFollower_rt.dir/src/main.cpp.o: CMakeFiles/SquareFollower_rt.dir/flags.make
CMakeFiles/SquareFollower_rt.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/rafik/flair/flair-src/demos/SquareFollower/uav/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/SquareFollower_rt.dir/src/main.cpp.o"
	/opt/robomap3/1.7.3/core2-64/sysroots/x86_64-pokysdk-linux/usr/bin/x86_64-poky-linux/x86_64-poky-linux-g++  --sysroot=/opt/robomap3/1.7.3/core2-64/sysroots/core2-64-poky-linux  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/SquareFollower_rt.dir/src/main.cpp.o -c /home/rafik/flair/flair-src/demos/SquareFollower/uav/src/main.cpp

CMakeFiles/SquareFollower_rt.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SquareFollower_rt.dir/src/main.cpp.i"
	/opt/robomap3/1.7.3/core2-64/sysroots/x86_64-pokysdk-linux/usr/bin/x86_64-poky-linux/x86_64-poky-linux-g++  --sysroot=/opt/robomap3/1.7.3/core2-64/sysroots/core2-64-poky-linux $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/rafik/flair/flair-src/demos/SquareFollower/uav/src/main.cpp > CMakeFiles/SquareFollower_rt.dir/src/main.cpp.i

CMakeFiles/SquareFollower_rt.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SquareFollower_rt.dir/src/main.cpp.s"
	/opt/robomap3/1.7.3/core2-64/sysroots/x86_64-pokysdk-linux/usr/bin/x86_64-poky-linux/x86_64-poky-linux-g++  --sysroot=/opt/robomap3/1.7.3/core2-64/sysroots/core2-64-poky-linux $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/rafik/flair/flair-src/demos/SquareFollower/uav/src/main.cpp -o CMakeFiles/SquareFollower_rt.dir/src/main.cpp.s

CMakeFiles/SquareFollower_rt.dir/src/main.cpp.o.requires:

.PHONY : CMakeFiles/SquareFollower_rt.dir/src/main.cpp.o.requires

CMakeFiles/SquareFollower_rt.dir/src/main.cpp.o.provides: CMakeFiles/SquareFollower_rt.dir/src/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/SquareFollower_rt.dir/build.make CMakeFiles/SquareFollower_rt.dir/src/main.cpp.o.provides.build
.PHONY : CMakeFiles/SquareFollower_rt.dir/src/main.cpp.o.provides

CMakeFiles/SquareFollower_rt.dir/src/main.cpp.o.provides.build: CMakeFiles/SquareFollower_rt.dir/src/main.cpp.o


CMakeFiles/SquareFollower_rt.dir/src/SquareFollower.cpp.o: CMakeFiles/SquareFollower_rt.dir/flags.make
CMakeFiles/SquareFollower_rt.dir/src/SquareFollower.cpp.o: ../src/SquareFollower.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/rafik/flair/flair-src/demos/SquareFollower/uav/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/SquareFollower_rt.dir/src/SquareFollower.cpp.o"
	/opt/robomap3/1.7.3/core2-64/sysroots/x86_64-pokysdk-linux/usr/bin/x86_64-poky-linux/x86_64-poky-linux-g++  --sysroot=/opt/robomap3/1.7.3/core2-64/sysroots/core2-64-poky-linux  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/SquareFollower_rt.dir/src/SquareFollower.cpp.o -c /home/rafik/flair/flair-src/demos/SquareFollower/uav/src/SquareFollower.cpp

CMakeFiles/SquareFollower_rt.dir/src/SquareFollower.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SquareFollower_rt.dir/src/SquareFollower.cpp.i"
	/opt/robomap3/1.7.3/core2-64/sysroots/x86_64-pokysdk-linux/usr/bin/x86_64-poky-linux/x86_64-poky-linux-g++  --sysroot=/opt/robomap3/1.7.3/core2-64/sysroots/core2-64-poky-linux $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/rafik/flair/flair-src/demos/SquareFollower/uav/src/SquareFollower.cpp > CMakeFiles/SquareFollower_rt.dir/src/SquareFollower.cpp.i

CMakeFiles/SquareFollower_rt.dir/src/SquareFollower.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SquareFollower_rt.dir/src/SquareFollower.cpp.s"
	/opt/robomap3/1.7.3/core2-64/sysroots/x86_64-pokysdk-linux/usr/bin/x86_64-poky-linux/x86_64-poky-linux-g++  --sysroot=/opt/robomap3/1.7.3/core2-64/sysroots/core2-64-poky-linux $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/rafik/flair/flair-src/demos/SquareFollower/uav/src/SquareFollower.cpp -o CMakeFiles/SquareFollower_rt.dir/src/SquareFollower.cpp.s

CMakeFiles/SquareFollower_rt.dir/src/SquareFollower.cpp.o.requires:

.PHONY : CMakeFiles/SquareFollower_rt.dir/src/SquareFollower.cpp.o.requires

CMakeFiles/SquareFollower_rt.dir/src/SquareFollower.cpp.o.provides: CMakeFiles/SquareFollower_rt.dir/src/SquareFollower.cpp.o.requires
	$(MAKE) -f CMakeFiles/SquareFollower_rt.dir/build.make CMakeFiles/SquareFollower_rt.dir/src/SquareFollower.cpp.o.provides.build
.PHONY : CMakeFiles/SquareFollower_rt.dir/src/SquareFollower.cpp.o.provides

CMakeFiles/SquareFollower_rt.dir/src/SquareFollower.cpp.o.provides.build: CMakeFiles/SquareFollower_rt.dir/src/SquareFollower.cpp.o


# Object files for target SquareFollower_rt
SquareFollower_rt_OBJECTS = \
"CMakeFiles/SquareFollower_rt.dir/src/main.cpp.o" \
"CMakeFiles/SquareFollower_rt.dir/src/SquareFollower.cpp.o"

# External object files for target SquareFollower_rt
SquareFollower_rt_EXTERNAL_OBJECTS =

bin/SquareFollower_rt: CMakeFiles/SquareFollower_rt.dir/src/main.cpp.o
bin/SquareFollower_rt: CMakeFiles/SquareFollower_rt.dir/src/SquareFollower.cpp.o
bin/SquareFollower_rt: CMakeFiles/SquareFollower_rt.dir/build.make
bin/SquareFollower_rt: /home/rafik/flair/flair-bin/lib/x86_64/unix/libFlairMeta.a
bin/SquareFollower_rt: /home/rafik/flair/flair-bin/lib/x86_64/unix/libFlairFilter.a
bin/SquareFollower_rt: /home/rafik/flair/flair-bin/lib/x86_64/unix/libFlairSensorActuator.a
bin/SquareFollower_rt: /home/rafik/flair/flair-bin/lib/x86_64/unix/libFlairCore_rt.a
bin/SquareFollower_rt: /opt/robomap3/1.7.3/core2-64/sysroots/core2-64-poky-linux/usr/lib/libxml2.so
bin/SquareFollower_rt: /opt/robomap3/1.7.3/core2-64/sysroots/core2-64-poky-linux/usr/lib/librtdm.so
bin/SquareFollower_rt: /opt/robomap3/1.7.3/core2-64/sysroots/core2-64-poky-linux/usr/lib/libnative.so
bin/SquareFollower_rt: /opt/robomap3/1.7.3/core2-64/sysroots/core2-64-poky-linux/usr/lib/libxenomai.so
bin/SquareFollower_rt: CMakeFiles/SquareFollower_rt.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/rafik/flair/flair-src/demos/SquareFollower/uav/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable bin/SquareFollower_rt"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/SquareFollower_rt.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/SquareFollower_rt.dir/build: bin/SquareFollower_rt

.PHONY : CMakeFiles/SquareFollower_rt.dir/build

CMakeFiles/SquareFollower_rt.dir/requires: CMakeFiles/SquareFollower_rt.dir/src/main.cpp.o.requires
CMakeFiles/SquareFollower_rt.dir/requires: CMakeFiles/SquareFollower_rt.dir/src/SquareFollower.cpp.o.requires

.PHONY : CMakeFiles/SquareFollower_rt.dir/requires

CMakeFiles/SquareFollower_rt.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/SquareFollower_rt.dir/cmake_clean.cmake
.PHONY : CMakeFiles/SquareFollower_rt.dir/clean

CMakeFiles/SquareFollower_rt.dir/depend:
	cd /home/rafik/flair/flair-src/demos/SquareFollower/uav/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/rafik/flair/flair-src/demos/SquareFollower/uav /home/rafik/flair/flair-src/demos/SquareFollower/uav /home/rafik/flair/flair-src/demos/SquareFollower/uav/build /home/rafik/flair/flair-src/demos/SquareFollower/uav/build /home/rafik/flair/flair-src/demos/SquareFollower/uav/build/CMakeFiles/SquareFollower_rt.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/SquareFollower_rt.dir/depend

