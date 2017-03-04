#! /bin/bash

. $FLAIR_ROOT/flair-dev/scripts/ubuntu_cgroup_hack.sh

if [ -f /proc/xenomai/version ];then
	EXEC=./DemoGps_rt
else
	EXEC=./DemoGps_nrt
fi

$EXEC -n x4_0 -a 127.0.0.1 -p 9000 -l /tmp -x setup_x4.xml -t x4_simu
