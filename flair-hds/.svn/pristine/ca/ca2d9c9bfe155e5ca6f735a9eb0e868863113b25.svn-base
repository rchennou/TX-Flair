#! /bin/bash

. $FLAIR_ROOT/flair-dev/scripts/ubuntu_cgroup_hack.sh

if [ -f /proc/xenomai/version ];then
	EXEC=./ApriltagFollower_simulator_rt
else
	EXEC=./ApriltagFollower_simulator_nrt
fi

$EXEC -a 127.0.0.1 -p 9000 -x setup_x4.xml -o 10 -m $FLAIR_ROOT/flair-bin/models -s $FLAIR_ROOT/flair-bin/models/indoor_flight_arena.xml
