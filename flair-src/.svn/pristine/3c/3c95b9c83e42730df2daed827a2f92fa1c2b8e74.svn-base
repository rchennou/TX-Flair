#! /bin/bash

. $FLAIR_ROOT/flair-dev/scripts/ubuntu_cgroup_hack.sh

if [ -f /proc/xenomai/version ];then
	EXEC=./Gps_simulator_rt
else
	EXEC=./Gps_simulator_nrt
fi

$EXEC -n x4_0 -t x4 -p 9000 -a 127.0.0.1 -x setup_x4.xml -o 10 -m $FLAIR_ROOT/flair-bin/models -s $FLAIR_ROOT/flair-bin/models/indoor_flight_arena.xml
