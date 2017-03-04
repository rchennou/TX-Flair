DIR=build_$(uname -m)

#verifie l'existence du lien symbolique build
if [ -d build ];then
	if ! readlink build > /dev/null ; then
		#it is a directory, exit to do not erase anything
		err "Error: build already exsits and is a directory; it should be a symlink."
		exit 1
	fi
	if ! readlink build | grep -w $DIR >/dev/null; then
		echo "Warning, build was pointing to another directory."
	fi
	rm build
fi

#creation du repertoire
mkdir -p $DIR
#creation du lien symbolique
ln -s $DIR build

#creation project x86
cd build

rm -f CMakeCache.txt
rm -rf CMakeFiles
${OECORE_HOST_NATIVE_SYSROOT}/usr/bin/cmake ../ -G "CodeBlocks - Unix Makefiles" -DCMAKE_TOOLCHAIN_FILE=${OECORE_CMAKE_HOST_TOOLCHAIN}

