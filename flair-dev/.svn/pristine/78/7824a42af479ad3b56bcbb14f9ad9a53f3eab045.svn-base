#usage svn_revision.sh gcc dir file
#gcc: gcc path
#dir: directory to get svn revision
#file: output file to put revision

USER=$(whoami)@$(hostname)
DATE=$(date)
GCC_REV=$($1 -dumpversion)
SVN_PATH=$(readlink -f $2)
SVN_REV=$(svnversion $(readlink -f $2))

mkdir -p $(dirname $3)

cat > $3 <<EOF
//file generated automatically by compile_info.sh script
//do not edit it manually

#include <string>

#define USER "${USER}"
#define DATE "${DATE}"
#define GCC_REV "${GCC_REV}"
#define GCC_PATH "$1"
#define SVN_PATH "${SVN_PATH}"
#define SVN_REV "${SVN_REV}"

inline void compile_info(std::string name) { 
	fprintf(stderr,"Using %s library:\n",name.c_str());
	fprintf(stderr,"  -built by " USER " on " DATE "\n");
	fprintf(stderr,"  -with GCC " GCC_REV " from " GCC_PATH "\n");
	fprintf(stderr,"  -svnversion of " SVN_PATH " is " SVN_REV "\n\n");
}
EOF
