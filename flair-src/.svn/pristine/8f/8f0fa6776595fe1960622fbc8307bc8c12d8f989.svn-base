#! /bin/bash

. $FLAIR_ROOT/flair-dev/scripts/ubuntu_cgroup_hack.sh

if [ -f /proc/xenomai/version ];then
	EXEC=./CircleFollower_rt
else
	EXEC=./CircleFollower_nrt
fi

$EXEC -n x8_0 -a 127.0.0.1 -p 9000 -l /tmp -x setup_x8.xml -t x8_simu
