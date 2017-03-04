#! /bin/sh
ARCH_DIR=$(uname -m)

#defaults options values
PORT=9000
NAME="FlairGCS"

usage() {
  USAGE="usage: $0 [-n name] [-p port] [-?]|[-h]"
  echo $USAGE;
  exit 1
}

while getopts h?n:p: OPT; do
  case $OPT in
  n)      NAME=$OPTARG;;
  p)      PORT=$OPTARG;;
  h|\?)     usage;;
  esac
done
shift `expr $OPTIND - 1`

#bail out in case unknown options remain
[ "$1" = "--" ] && usage 

export LD_LIBRARY_PATH="${OECORE_HOST_SYSROOT}/usr/lib:${OECORE_HOST_SYSROOT}/lib"
${FLAIR_ROOT}/flair-bin/tools/${ARCH_DIR}/unix/flairgcs -n $NAME -p $PORT
