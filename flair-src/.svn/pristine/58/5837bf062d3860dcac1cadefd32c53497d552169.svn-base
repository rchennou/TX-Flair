#! /bin/bash

. $FLAIR_ROOT/flair-dev/scripts/ubuntu_cgroup_hack.sh

if [ -f /proc/xenomai/version ];then
	EXEC=./simulator_optitrack_rt
else
	EXEC=./simulator_optitrack_nrt
fi

$EXEC -n x8_0 -t x8 -p 9000 -x setup_x8.xml -o 10 -m $IGEP_ROOT/uav_dev/media -s $IGEP_ROOT/uav_dev/media/optitrack_b122.xml
