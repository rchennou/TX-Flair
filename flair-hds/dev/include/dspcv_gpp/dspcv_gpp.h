#include <cxtypes.h>

//codes conversions couleurs (from opencv_common.h)
//TODO: un seul .h
#define DSP_BGR2GRAY 6
#define DSP_YUYV2GRAY 62
#define DSP_UYVY2GRAY 63

//formats d'images pour compression JPG (from opencv_common.h)
//TODO: un seul .h
#define CHROMA_NA -1     /**< Chroma format not applicable. */
#define YUV_420P 1       /**< YUV 4:2:0 planer. */
#define YUV_422P 2       /**< YUV 4:2:2 planer. */
#define YUV_422IBE 3     /**< YUV 4:2:2 interleaved (big endian). */
#define YUV_422ILE 4     /**< YUV 4:2:2 interleaved (little endian). */
#define YUV_444P 5       /**< YUV 4:4:4 planer. */
#define YUV_411P 6       /**< YUV 4:1:1 planer. */
#define GRAY 7           /**< Gray format. */
//#define RGB 8            /**< RGB color format. */
#define YUV_420SP 9      /**< YUV 420 semi_planar format.(Luma 1st plane,
                             *   CbCr interleaved 2nd plane)
                             */
#define ARGB8888 10      /**< Alpha plane. */
#define RGB555 11        /**< RGB 555 color format. */
#define RGB565 12        /**< RGB 565 color format. */
#define YUV_444ILE 13    /**< YUV 4:4:4 interleaved (little endian). */

#if defined (__cplusplus)
extern "C" {
#endif /* defined (__cplusplus) */

bool initDsp(const char* dspExecutable,int warningTimeoutMs=-1) ;
bool closeDsp(void) ;

//allocate a cmem cached buffer on heap
char* shMemAlloc(size_t size);

//free buffer allocated by shMemAlloc
char* shMemFree(char* buf);
 
void dspSaveToJpeg(IplImage* src_img,const char* filename,unsigned char input_format,unsigned char output_format,unsigned char compression_level=95);
 
/**
 * @brief 
 * @param src_img must be one channel
 * @param out_buf must be allocated by shMemAlloc, and freed by user with shMemFree
 * @param out_buf_size
 * @param compression_level from 0 to 100
 */
unsigned int dspConvertToJpeg(IplImage* src_img,char* out_buf,unsigned int out_buf_size,unsigned char input_format,unsigned char output_format,unsigned char compression_level=95);

void dspGoodFeaturesToTrack(IplImage* img_src,CvPoint* features,unsigned int* count,float quality_level, float min_distance);


void dspPyrDown(IplImage* img_src,IplImage* img_dst,unsigned char level);


void dspCalcOpticalFlowPyrLK(IplImage* img_A,IplImage* img_B,IplImage* pyr_A,IplImage* pyr_B,
        CvPoint* features_A,CvPoint* features_B,int count,CvSize winSize,
        int level,char *feat_status,unsigned int *error,CvTermCriteria criteria,int flags);

void dspCvtColor(IplImage* img_src,IplImage* img_dst,int code);

void dspThreshold(IplImage* img_src,IplImage* img_dst, float threshold,float max_value,int threshold_type );

void dspCloneImage(IplImage* img_src,IplImage* img_dst);

void dspSobel(IplImage* src_img,IplImage* dst_img,int dx,int dy);

int dspHoughLines2(IplImage* img_src, CvMat* line_storage, int method,
                              float rho_step, float theta_step, int threshold,
                              float param1=0, float param2=0);

int32_t dspHoughLines2_test(IplImage* img_src, CvMat* line_storage, int32_t method,
                              float rho, float theta_min,float theta_max,float theta_step, int32_t threshold);

//search for all rho
//search theta between theta_moy-delta_theta and theta_moy+delta_theta
int32_t dspHoughLinesTracking(IplImage* img_src, CvMat* line_storage, int32_t method,
                              float rho_step, float theta_moy,float delta_theta,float theta_step, int32_t threshold);
/*
int32_t dspHoughLines2_cv(IplImage* img, CvMat* line_storage, int32_t method,
            float rho, float theta, int32_t threshold,
            float param1=0, float param2=0);
*/
															 
#if defined (__cplusplus)
}
#endif /* defined (__cplusplus) */


