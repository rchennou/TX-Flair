#! /bin/bash

. $FLAIR_ROOT/flair-dev/scripts/ubuntu_cgroup_hack.sh

if [ -f /proc/xenomai/version ];then
	EXEC=./SquareFleet_simulator_rt
else
	EXEC=./SquareFleet_simulator_nrt
fi

$EXEC -n x8 -a 127.0.0.1 -p 9000 -x setup_x8.xml -o 10 -m $FLAIR_ROOT/flair-bin/models -s $FLAIR_ROOT/flair-bin/models/indoor_flight_arena.xml
