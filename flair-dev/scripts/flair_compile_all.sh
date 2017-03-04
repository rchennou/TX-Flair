#!/bin/bash
ARCH_DIR=build_$(uname -m)
NB_THREADS=$(nproc)
from_scratch=no

function green_echo () {
	echo -e "\033[32m$1\033[0m"
}

function red_echo () {
	echo -e "\033[31m$1\033[0m"
}

function check_error () {
	if [ "$?" != "0" ]; then
		red_echo "Error, exiting"
		exit 1
	fi
}

function sanity_check () {
	if [ -z $FLAIR_ROOT ]; then
		red_echo "You must set the FLAIR_ROOT environement variable"
		exit 1
	fi
}

function configure () {
	if [ "$from_scratch" = "yes" ]; then
		green_echo "Configuring $1/$2"
		cd $1/$2

		rm -f build_arm/CMakeCache.txt
		$FLAIR_ROOT/flair-dev/scripts/cmake_codeblocks.sh > /dev/null
	
		check_error
	else
		green_echo "Not configuring $1/$2"
	fi
}

function cross_compile () {
	green_echo "Cross compiling and installing $2"
	cd $1/$2/build_arm
	if [ "$from_scratch" = "yes" ]; then make clean > /dev/null; fi
	make -j$NB_THREADS > /dev/null
	check_error
	make install
}

function compile () {
	green_echo "Compiling and installing $2"
	cd $1/$2/$ARCH_DIR
	if [ "$from_scratch" = "yes" ]; then make clean > /dev/null; fi
	make -j$NB_THREADS > /dev/null
	check_error	
	make install
}

function compile_libs() {
	for projects in FlairCore FlairSensorActuator FlairFilter FlairMeta FlairSimulator ; do
		configure $FLAIR_ROOT/flair-src/lib $projects
	   	compile $FLAIR_ROOT/flair-src/lib $projects
		cross_compile $FLAIR_ROOT/flair-src/lib $projects
	done

	if [ -d $FLAIR_ROOT/flair-hds ]; then
		for projects in FlairArdrone2 VisionFilter; do
			configure $FLAIR_ROOT/flair-hds/src/lib $projects
		   	compile $FLAIR_ROOT/flair-hds/src/lib $projects
			cross_compile $FLAIR_ROOT/flair-hds/src/lib $projects
		done
	fi
}

function compile_tools() {
	for projects in FlairGCS Controller/DualShock3 Controller/Mavlink Dbt2csv; do
		configure $FLAIR_ROOT/flair-src/tools $projects
	   	compile $FLAIR_ROOT/flair-src/tools $projects
		cross_compile $FLAIR_ROOT/flair-src/tools $projects
	done
}

function compile_uav_and_simulator_demo() {
	for projects in simulator uav; do
		configure $1/$2 $projects
	   	compile $1/$2 $projects
		cross_compile $1/$2 $projects
	done
}

function compile_demos() {
	for projects in Sinus; do
		configure $FLAIR_ROOT/flair-src/demos $projects
	   	compile $FLAIR_ROOT/flair-src/demos $projects
		cross_compile $FLAIR_ROOT/flair-src/demos $projects
	done

	for projects in CircleFollower SimpleFleet Gps; do
		compile_uav_and_simulator_demo $FLAIR_ROOT/flair-src/demos $projects
	done

	for projects in CustomReferenceAngles CustomTorques; do
		configure $FLAIR_ROOT/flair-src/demos/Skeletons $projects
	   	compile $FLAIR_ROOT/flair-src/demos/Skeletons $projects
		cross_compile $FLAIR_ROOT/flair-src/demos/Skeletons $projects
	done

	if [ -d $FLAIR_ROOT/flair-hds ]; then
		for projects in OpticalFlow; do
			compile_uav_and_simulator_demo $FLAIR_ROOT/flair-hds/src/demos $projects
		done
	fi

exit 0	
	

	for projects in uav; do
		configure $FLAIR_ROOT/uav_ex/demo_ligne_framework $projects
	   	compile $FLAIR_ROOT/uav_ex/demo_ligne_framework $projects
		cross_compile $FLAIR_ROOT/uav_ex/demo_ligne_framework $projects
	done

	
}

sanity_check

printf "Compile all from scratch [Y/n]?"
read answer

if [ "$answer" = "" ] || [ "$answer" = "y" ] || [ "$answer" = "Y" ]; then
	from_scratch=yes
fi

printf "Compile Flair libs [Y/n]?"
read answer

if [ "$answer" = "" ] || [ "$answer" = "y" ] || [ "$answer" = "Y" ]; then
	compile_libs
fi

printf "Compile Flair libs documentation [Y/n]?"
read answer

if [ "$answer" = "" ] || [ "$answer" = "y" ] || [ "$answer" = "Y" ]; then
	$OECORE_HOST_NATIVE_SYSROOT/usr/bin/doxygen $FLAIR_ROOT/flair-src/lib/Doxyfile.in
fi

printf "Compile Flair tools [Y/n]?"
read answer

if [ "$answer" = "" ] || [ "$answer" = "y" ] || [ "$answer" = "Y" ]; then
	compile_tools
fi

printf "Compile demos [Y/n]?"
read answer

if [ "$answer" = "" ] || [ "$answer" = "y" ] || [ "$answer" = "Y" ]; then
	compile_demos
fi

exit 0



exit 0
