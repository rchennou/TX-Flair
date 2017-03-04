#! /bin/bash

. $IGEP_ROOT/uav_dev/bin/noarch/ubuntu_cgroup_hack.sh

if [ -f /proc/xenomai/version ];then
	EXEC=./demo_pid_rt
else
	EXEC=./demo_pid_nrt
fi

$EXEC -n x4_0 -a 127.0.0.1 -p 9000 -l ./ -x setup_x4.xml -t x4_simu $*
