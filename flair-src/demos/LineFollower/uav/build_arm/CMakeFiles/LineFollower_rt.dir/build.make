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
CMAKE_SOURCE_DIR = /home/rafik/flair/flair-src/demos/LineFollower/uav

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/rafik/flair/flair-src/demos/LineFollower/uav/build_arm

# Include any dependencies generated for this target.
include CMakeFiles/LineFollower_rt.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/LineFollower_rt.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/LineFollower_rt.dir/flags.make

CMakeFiles/LineFollower_rt.dir/src/main.cpp.o: CMakeFiles/LineFollower_rt.dir/flags.make
CMakeFiles/LineFollower_rt.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/rafik/flair/flair-src/demos/LineFollower/uav/build_arm/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/LineFollower_rt.dir/src/main.cpp.o"
	/opt/robomap3/1.7.3/armv7a-neon/sysroots/x86_64-pokysdk-linux/usr/bin/arm-poky-linux-gnueabi/arm-poky-linux-gnueabi-g++  --sysroot=/opt/robomap3/1.7.3/armv7a-neon/sysroots/armv7a-vfp-neon-poky-linux-gnueabi  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/LineFollower_rt.dir/src/main.cpp.o -c /home/rafik/flair/flair-src/demos/LineFollower/uav/src/main.cpp

CMakeFiles/LineFollower_rt.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/LineFollower_rt.dir/src/main.cpp.i"
	/opt/robomap3/1.7.3/armv7a-neon/sysroots/x86_64-pokysdk-linux/usr/bin/arm-poky-linux-gnueabi/arm-poky-linux-gnueabi-g++  --sysroot=/opt/robomap3/1.7.3/armv7a-neon/sysroots/armv7a-vfp-neon-poky-linux-gnueabi $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/rafik/flair/flair-src/demos/LineFollower/uav/src/main.cpp > CMakeFiles/LineFollower_rt.dir/src/main.cpp.i

CMakeFiles/LineFollower_rt.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/LineFollower_rt.dir/src/main.cpp.s"
	/opt/robomap3/1.7.3/armv7a-neon/sysroots/x86_64-pokysdk-linux/usr/bin/arm-poky-linux-gnueabi/arm-poky-linux-gnueabi-g++  --sysroot=/opt/robomap3/1.7.3/armv7a-neon/sysroots/armv7a-vfp-neon-poky-linux-gnueabi $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/rafik/flair/flair-src/demos/LineFollower/uav/src/main.cpp -o CMakeFiles/LineFollower_rt.dir/src/main.cpp.s

CMakeFiles/LineFollower_rt.dir/src/main.cpp.o.requires:

.PHONY : CMakeFiles/LineFollower_rt.dir/src/main.cpp.o.requires

CMakeFiles/LineFollower_rt.dir/src/main.cpp.o.provides: CMakeFiles/LineFollower_rt.dir/src/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/LineFollower_rt.dir/build.make CMakeFiles/LineFollower_rt.dir/src/main.cpp.o.provides.build
.PHONY : CMakeFiles/LineFollower_rt.dir/src/main.cpp.o.provides

CMakeFiles/LineFollower_rt.dir/src/main.cpp.o.provides.build: CMakeFiles/LineFollower_rt.dir/src/main.cpp.o


CMakeFiles/LineFollower_rt.dir/src/LineFollower.cpp.o: CMakeFiles/LineFollower_rt.dir/flags.make
CMakeFiles/LineFollower_rt.dir/src/LineFollower.cpp.o: ../src/LineFollower.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/rafik/flair/flair-src/demos/LineFollower/uav/build_arm/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/LineFollower_rt.dir/src/LineFollower.cpp.o"
	/opt/robomap3/1.7.3/armv7a-neon/sysroots/x86_64-pokysdk-linux/usr/bin/arm-poky-linux-gnueabi/arm-poky-linux-gnueabi-g++  --sysroot=/opt/robomap3/1.7.3/armv7a-neon/sysroots/armv7a-vfp-neon-poky-linux-gnueabi  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/LineFollower_rt.dir/src/LineFollower.cpp.o -c /home/rafik/flair/flair-src/demos/LineFollower/uav/src/LineFollower.cpp

CMakeFiles/LineFollower_rt.dir/src/LineFollower.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/LineFollower_rt.dir/src/LineFollower.cpp.i"
	/opt/robomap3/1.7.3/armv7a-neon/sysroots/x86_64-pokysdk-linux/usr/bin/arm-poky-linux-gnueabi/arm-poky-linux-gnueabi-g++  --sysroot=/opt/robomap3/1.7.3/armv7a-neon/sysroots/armv7a-vfp-neon-poky-linux-gnueabi $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/rafik/flair/flair-src/demos/LineFollower/uav/src/LineFollower.cpp > CMakeFiles/LineFollower_rt.dir/src/LineFollower.cpp.i

CMakeFiles/LineFollower_rt.dir/src/LineFollower.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/LineFollower_rt.dir/src/LineFollower.cpp.s"
	/opt/robomap3/1.7.3/armv7a-neon/sysroots/x86_64-pokysdk-linux/usr/bin/arm-poky-linux-gnueabi/arm-poky-linux-gnueabi-g++  --sysroot=/opt/robomap3/1.7.3/armv7a-neon/sysroots/armv7a-vfp-neon-poky-linux-gnueabi $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/rafik/flair/flair-src/demos/LineFollower/uav/src/LineFollower.cpp -o CMakeFiles/LineFollower_rt.dir/src/LineFollower.cpp.s

CMakeFiles/LineFollower_rt.dir/src/LineFollower.cpp.o.requires:

.PHONY : CMakeFiles/LineFollower_rt.dir/src/LineFollower.cpp.o.requires

CMakeFiles/LineFollower_rt.dir/src/LineFollower.cpp.o.provides: CMakeFiles/LineFollower_rt.dir/src/LineFollower.cpp.o.requires
	$(MAKE) -f CMakeFiles/LineFollower_rt.dir/build.make CMakeFiles/LineFollower_rt.dir/src/LineFollower.cpp.o.provides.build
.PHONY : CMakeFiles/LineFollower_rt.dir/src/LineFollower.cpp.o.provides

CMakeFiles/LineFollower_rt.dir/src/LineFollower.cpp.o.provides.build: CMakeFiles/LineFollower_rt.dir/src/LineFollower.cpp.o


# Object files for target LineFollower_rt
LineFollower_rt_OBJECTS = \
"CMakeFiles/LineFollower_rt.dir/src/main.cpp.o" \
"CMakeFiles/LineFollower_rt.dir/src/LineFollower.cpp.o"

# External object files for target LineFollower_rt
LineFollower_rt_EXTERNAL_OBJECTS =

bin/LineFollower_rt: CMakeFiles/LineFollower_rt.dir/src/main.cpp.o
bin/LineFollower_rt: CMakeFiles/LineFollower_rt.dir/src/LineFollower.cpp.o
bin/LineFollower_rt: CMakeFiles/LineFollower_rt.dir/build.make
bin/LineFollower_rt: /home/rafik/flair/flair-bin/lib/arm/libFlairMeta.a
bin/LineFollower_rt: /home/rafik/flair/flair-bin/lib/arm/libFlairFilter.a
bin/LineFollower_rt: /home/rafik/flair/flair-bin/lib/arm/libFlairSensorActuator.a
bin/LineFollower_rt: /home/rafik/flair/flair-bin/lib/arm/libFlairCore_rt.a
bin/LineFollower_rt: /opt/robomap3/1.7.3/armv7a-neon/sysroots/armv7a-vfp-neon-poky-linux-gnueabi/usr/lib/libxml2.so
bin/LineFollower_rt: /opt/robomap3/1.7.3/armv7a-neon/sysroots/armv7a-vfp-neon-poky-linux-gnueabi/usr/lib/librtdm.so
bin/LineFollower_rt: /opt/robomap3/1.7.3/armv7a-neon/sysroots/armv7a-vfp-neon-poky-linux-gnueabi/usr/lib/libnative.so
bin/LineFollower_rt: /opt/robomap3/1.7.3/armv7a-neon/sysroots/armv7a-vfp-neon-poky-linux-gnueabi/usr/lib/libxenomai.so
bin/LineFollower_rt: CMakeFiles/LineFollower_rt.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/rafik/flair/flair-src/demos/LineFollower/uav/build_arm/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable bin/LineFollower_rt"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/LineFollower_rt.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/LineFollower_rt.dir/build: bin/LineFollower_rt

.PHONY : CMakeFiles/LineFollower_rt.dir/build

CMakeFiles/LineFollower_rt.dir/requires: CMakeFiles/LineFollower_rt.dir/src/main.cpp.o.requires
CMakeFiles/LineFollower_rt.dir/requires: CMakeFiles/LineFollower_rt.dir/src/LineFollower.cpp.o.requires

.PHONY : CMakeFiles/LineFollower_rt.dir/requires

CMakeFiles/LineFollower_rt.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/LineFollower_rt.dir/cmake_clean.cmake
.PHONY : CMakeFiles/LineFollower_rt.dir/clean

CMakeFiles/LineFollower_rt.dir/depend:
	cd /home/rafik/flair/flair-src/demos/LineFollower/uav/build_arm && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/rafik/flair/flair-src/demos/LineFollower/uav /home/rafik/flair/flair-src/demos/LineFollower/uav /home/rafik/flair/flair-src/demos/LineFollower/uav/build_arm /home/rafik/flair/flair-src/demos/LineFollower/uav/build_arm /home/rafik/flair/flair-src/demos/LineFollower/uav/build_arm/CMakeFiles/LineFollower_rt.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/LineFollower_rt.dir/depend

