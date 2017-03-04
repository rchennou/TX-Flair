#! /bin/bash

if [ -f /proc/xenomai/version ];then
	EXEC=./Sinus_rt
else
	EXEC=./Sinus_nrt
fi

$EXEC

