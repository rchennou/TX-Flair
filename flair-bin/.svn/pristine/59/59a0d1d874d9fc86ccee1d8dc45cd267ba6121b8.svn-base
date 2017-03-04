#! /bin/bash
ARCH_DIR=$(uname -m)

# $1 is the drone ip
if [ "$#" -ne 1 ] ; then
  echo "Usage: $0 drone_ip_address"
  exit 1
fi

${FLAIR_ROOT}/flair-bin/tools/scripts/dualshock3.sh -a ${1}:20000 -x ${FLAIR_ROOT}/flair-bin/tools/scripts/dualshock3.xml

