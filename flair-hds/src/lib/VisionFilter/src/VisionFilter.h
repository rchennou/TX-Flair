#include <string>
#include <cxtypes.h>

/*!
* \brief InitVisionFilter
*
* Setup DSP executable file. \n
* If this method is not called, no DSP processing will be available. \n
*
* \param args arguments
* "file=" DSP executable file
* "globalTimeoutMs=" timeout for all DSP functions, in ms (timeout is only
* used to display a warning. -1 to disable timeout. Default is -1.
* 
* \return true if initialization succeeds, false otherwise
*/
bool InitVisionFilter(std::string args);

void CloseVisionFilter(void);

enum class PictureFormat_t {
                Gray,/*!< gray 8 bits */
                RGB,/*!< rgb 24 bits */
                YUV_422ile,/*!< YUV 4:2:2 interleaved */
                YUV_422p,/*!< YUV 4:2:2 planer */
                } ;
								
void saveToJpeg(IplImage* src_img,std::string filename,PictureFormat_t input_format,PictureFormat_t output_format,unsigned char compression_level=95);