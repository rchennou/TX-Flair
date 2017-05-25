#include "VisionFilter.h"
#include <dspcv_gpp.h>
#include <stdexcept>
#include <FindArgument.h>
#include "compile_info.h"

using namespace std;

static void constructor() __attribute__((constructor));

void constructor() {
  compile_info("HdsVisionFilter");
}

unsigned char convertPictureFormat(PictureFormat_t format) {
		switch(format) {
			case PictureFormat_t::Gray:
				return GRAY;
			case PictureFormat_t::YUV_422p:
				return YUV_422P;
      case PictureFormat_t::YUV_422ile:
				return YUV_422ILE;
      default:
        fprintf(stderr,"format %i not handled\n",format);
		}
}

void saveToJpeg(IplImage* src_img,string filename,PictureFormat_t input_format,PictureFormat_t output_format,unsigned char compression_level) {
    dspSaveToJpeg(src_img,filename.c_str(),convertPictureFormat(input_format),convertPictureFormat(output_format),compression_level);
}

bool InitVisionFilter(string args) {
	string file=FindArgument(args,"file=",true);
	if(file=="") {
		return false;
	}
	
	string timeoutString=FindArgument(args,"globalTimeoutMs=",false);
	int timeout;
	if(timeoutString=="") {
		timeout=-1;
	} else {
		try {
			timeout=stoi(timeoutString);
		}
		catch (const std::invalid_argument) {
			fprintf(stderr,"InitVisionFilter, invalid argument for globalTimeoutMs (%s)\n",timeoutString.c_str());
			return false;
		}
	}
	return initDsp(file.c_str(),timeout);
}

void CloseVisionFilter(void) {
  closeDsp();
}
