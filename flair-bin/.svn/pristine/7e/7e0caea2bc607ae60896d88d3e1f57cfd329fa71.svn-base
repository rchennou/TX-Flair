#! /bin/bash
ARCH_DIR=$(uname -m)

. ${FLAIR_ROOT}/flair-bin/tools/scripts/ubuntu_cgroup_hack.sh

#we must run as root
if [ $EUID -ne 0 ]; then
  exec sudo -E $0 $*
fi

export LD_LIBRARY_PATH="${OECORE_HOST_SYSROOT}/usr/lib:${OECORE_HOST_SYSROOT}/lib"
${FLAIR_ROOT}/flair-bin/tools/$ARCH_DIR/unix/MavPlanner --inputAddress 127.0.0.1 --inputPort 5036 -x ${FLAIR_ROOT}/flair-bin/tools/scripts/mavlink.xml -m "forward" --outputAddress 127.0.0.1 --outputPort 5037 -a 127.0.0.1 -p 9000
