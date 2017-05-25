#! /bin/bash
if [ $# -eq 1 ]; then
  DRONE_TYPE=$1
else
  DRONE_TYPE=x4
fi
if [ ! -r ${DRONE_TYPE}/setup.xml ]; then
  echo "File ${DRONE_TYPE}/setup.xml not found or not readable -> wrong drone type selected"
  exit 1
fi
echo "Drone type set to $DRONE_TYPE"

. $FLAIR_ROOT/flair-dev/scripts/ubuntu_cgroup_hack.sh

if [ -f /proc/xenomai/version ];then
	EXEC=./LineFollower_rt
else
	EXEC=./LineFollower_nrt
fi

$EXEC -n ${DRONE_TYPE}_0 -a 127.0.0.1 -p 9000 -l ./ -x ${DRONE_TYPE}/setup.xml -t ${DRONE_TYPE}_simu -v dsp_stub -d 20000
