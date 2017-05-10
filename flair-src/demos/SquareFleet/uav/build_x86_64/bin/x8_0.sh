#! /bin/bash

. $FLAIR_ROOT/flair-dev/scripts/ubuntu_cgroup_hack.sh

if [ -f /proc/xenomai/version ];then
	EXEC=./SquareFleet_rt
else
	EXEC=./SquareFleet_nrt
fi

$EXEC -n x8_0 -a 127.0.0.1 -p 9000 -l ./ -x setup_x8.xml -t x8_simu0 -b 127.255.255.255:20010
