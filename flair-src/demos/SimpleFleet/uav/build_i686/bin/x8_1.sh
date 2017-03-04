#! /bin/bash

. $FLAIR_ROOT/flair-dev/scripts/ubuntu_cgroup_hack.sh

if [ -f /proc/xenomai/version ];then
	EXEC=./SimpleFleet_rt
else
	EXEC=./SimpleFleet_nrt
fi

$EXEC -n x8_1 -a 127.0.0.1 -p 9001 -l ./ -x setup_x8.xml -t x8_simu1 -b 127.255.255.255:20010 -d 20020
