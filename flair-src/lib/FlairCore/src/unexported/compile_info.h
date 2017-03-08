//file generated automatically by compile_info.sh script
//do not edit it manually

#include <string>

#define USER "rafik@rafik-Linux"
#define DATE "mardi 7 mars 2017, 23:13:32 (UTC+0100)"
#define GCC_REV "4.9.1"
#define GCC_PATH "/opt/robomap3/1.7.3/armv7a-neon/sysroots/x86_64-pokysdk-linux/usr/bin/arm-poky-linux-gnueabi/arm-poky-linux-gnueabi-gcc"
#define SVN_PATH "/home/rafik/flair/flair-src/lib/FlairCore"
#define SVN_REV "148"

inline void compile_info(std::string name) { 
	fprintf(stderr,"Using %s library:\n",name.c_str());
	fprintf(stderr,"  -built by " USER " on " DATE "\n");
	fprintf(stderr,"  -with GCC " GCC_REV " from " GCC_PATH "\n");
	fprintf(stderr,"  -svnversion of " SVN_PATH " is " SVN_REV "\n\n");
}
