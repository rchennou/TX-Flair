#! /bin/bash

. $FLAIR_ROOT/flair-dev/scripts/ubuntu_cgroup_hack.sh

if [ -f /proc/xenomai/version ];then
	EXEC=./SquareFollower_simulator_rt
else
	EXEC=./SquareFollower_simulator_nrt
fi

$EXEC -n x8_0 -t x8 -p 9000 -a 127.0.0.1 -x setup_x8.xml -o 10 -m $FLAIR_ROOT/flair-bin/models -s $FLAIR_ROOT/flair-bin/models/city_tile.xml

