//file generated automatically by compile_info.sh script
//do not edit it manually

#include <string>

#define USER "rafik@rafik-Linux"
#define DATE "vendredi 3 mars 2017, 19:06:52 (UTC+0100)"
#define GCC_REV "4.9.1"
#define GCC_PATH "/opt/robomap3/1.7.3/core2-64/sysroots/x86_64-pokysdk-linux/usr/bin/x86_64-poky-linux/x86_64-poky-linux-gcc"
#define SVN_PATH "/home/rafik/flair/flair-src/tools/Dbt2csv"
#define SVN_REV "148"

inline void compile_info(std::string name) { 
	fprintf(stderr,"Using %s library:\n",name.c_str());
	fprintf(stderr,"  -built by " USER " on " DATE "\n");
	fprintf(stderr,"  -with GCC " GCC_REV " from " GCC_PATH "\n");
	fprintf(stderr,"  -svnversion of " SVN_PATH " is " SVN_REV "\n\n");
}
