#! /bin/bash
if [ $# -eq 1 ]; then
  DRONE_TYPE=$1
else
  DRONE_TYPE=x4
fi
if [ ! -r ${DRONE_TYPE}/setup.xml ]; then
  echo "File ${DRONE_TYPE}/setup.xml not found or not readable -> wrong drone type (${DRONE_TYPE}) selected"
  exit 1
fi
echo "Drone type set to $DRONE_TYPE"

. $FLAIR_ROOT/flair-dev/scripts/ubuntu_cgroup_hack.sh

export LD_PRELOAD=/usr/lib/x86_64-linux-gnu/libstdc++.so.6:/usr/lib/x86_64-linux-gnu/libdrm_intel.so.1:/usr/lib/x86_64-linux-gnu/libdrm_nouveau.so.2:/usr/lib/x86_64-linux-gnu/libdrm_radeon.so.1

if [ -f /proc/xenomai/version ]; then
	EXEC=./LineFollower_simulator_rt
else
	EXEC=./LineFollower_simulator_nrt
fi

if [ -r ./scene.xml ]; then
	SCENE=./scene.xml
else
	SCENE=$FLAIR_ROOT/flair-bin/models/indoor_flight_arena_with_line.xml
fi

$EXEC -n ${DRONE_TYPE}_0 -t $DRONE_TYPE -a 127.0.0.1 -p 9000 -x $DRONE_TYPE/setup.xml -o 10 -m $FLAIR_ROOT/flair-bin/models -s $SCENE
