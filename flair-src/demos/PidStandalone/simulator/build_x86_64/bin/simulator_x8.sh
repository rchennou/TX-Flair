#! /bin/bash

. $IGEP_ROOT/uav_dev/bin/noarch/ubuntu_cgroup_hack.sh

if [ -f /proc/xenomai/version ];then
	EXEC=./simulator_pid_rt
else
	EXEC=./simulator_pid_nrt
fi

$EXEC  -n x8_0 -t x8 -a 127.0.0.1 -p 9000 -x setup_x8.xml -o 10 -m $IGEP_ROOT/uav_dev/media -s $IGEP_ROOT/uav_dev/media/optitrack_b122.xml
