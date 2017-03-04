#! /bin/bash
ARCH_DIR=$(uname -m)

#This script is the only one that calls itself with sudo.
#As a consequence, only one exception is needed in sudoers (the following 2 lines)
#  Defaults!/opt/flair/flair-bin/tools/scripts/dualshock3.sh setenv
#  uav ALL=(root) /opt/flair/flair-bin/tools/scripts/dualshock3.sh

#we must run as root
if [ $EUID -ne 0 ]; then
  exec sudo -E $0 $*
fi

. ${FLAIR_ROOT}/flair-bin/tools/scripts/ubuntu_cgroup_hack.sh

export LD_LIBRARY_PATH="${OECORE_HOST_SYSROOT}/usr/lib:${OECORE_HOST_SYSROOT}/lib"
${FLAIR_ROOT}/flair-bin/tools/$ARCH_DIR/unix/dualshock3 $*
