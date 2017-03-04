DIR=build_$(uname -m)

function info () {
	echo -e "\033[32m$1\033[0m"
}

function warn () {
	echo -e "\033[33m$1\033[0m"
}

function err () {
	echo -e "\033[31m$1\033[0m"
	exit 1
}

if ! [ -f  ./CMakeLists.txt ]; then
	err "Current directory does not contain CMakeLists.txt"
fi

#get cmake
CMAKE=${OECORE_HOST_NATIVE_SYSROOT}/usr/bin/cmake

#verifie l'existence du lien symbolique build
if [ -d build ];then
	if ! readlink build > /dev/null ; then
		#it is a directory, exit to do not erase anything
		err "Error: build already exsits and is a directory; it should be a symlink."
	fi
	if ! readlink build | grep -w $DIR >/dev/null; then
		warn "Warnink, build was pointing to another directory."
	fi
	rm build
fi

#creation du repertoire
mkdir -p $DIR
#creation du lien symbolique
ln -s $DIR build

#creation project x86
info "*************  Creating project for x86 *************"
cd build
rm -f CMakeCache.txt
rm -rf CMakeFiles
${CMAKE} ../ -G "CodeBlocks - Unix Makefiles" -DCMAKE_TOOLCHAIN_FILE=${OECORE_CMAKE_HOST_TOOLCHAIN}
# -DCMAKE_BUILD_TYPE=Release 

#creation projet ARM
info "************* Creating project for ARM *************"
cd ..
mkdir -p build_arm
cd build_arm
rm -f CMakeCache.txt
rm -rf CMakeFiles

${CMAKE} ../ -G "CodeBlocks - Unix Makefiles" -DCMAKE_TOOLCHAIN_FILE=${OECORE_CMAKE_CROSS_TOOLCHAIN}
# -DCMAKE_BUILD_TYPE=Release
