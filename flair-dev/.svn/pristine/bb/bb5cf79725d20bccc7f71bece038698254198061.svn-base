if [ -f /etc/lsb-release ]; then
  . /etc/lsb-release
fi

if [ _$DISTRIB_ID == _Ubuntu ]; then
  #we must run as root
  if [ $EUID -ne 0 ]; then
    exec sudo -E $0 $*
  fi

  #we must run in root cgroup to escape possible restrictions on scheduling
  if [ -d /sys/fs/cgroup/cpu ]; then
    echo $$ > /sys/fs/cgroup/cpu/tasks
  fi
fi

