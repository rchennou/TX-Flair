//  created:    2014/07/16
//  filename:   ArDrone2CamH.cpp
//
//  author:     Guillaume Sanahuja
//
//  version:    $Id: $
//
//  purpose:    class for ardrone2 horizontal camera
//
//
/*********************************************************************/

/*
* A V4L2 driver for Aptina MT9M114 cameras.
*
* Copyright 2011 Aldebaran Robotics Written
* by Joseph Pinkasfeld with substantial inspiration from ov7670 code.
*
* Authors:
* joseph pinkasfeld <joseph.pinkasfeld@gmail.com>
* Ludovic SMAL <lsmal@aldebaran-robotics.com>
* Corentin Le Molgat <clemolgat@aldebaran-robotics.com>
* Arne Böckmann <arneboe@tzi.de>
*
* This file may be distributed under the terms of the GNU General
* Public License, version 2.
*/

#include "ArDrone2CamH.h"
#include <Unix_I2cPort.h>
#include <fcntl.h>
#include <unistd.h>

#define I2C_8BIT 1
#define I2C_16BIT 2
#define I2C_32BIT 4

/* Registers */
#define REG_CHIP_ID 0x0000
#define REG_MON_MAJOR_VERSION 0x8000
#define REG_MON_MINOR_VERION 0x8002
#define REG_MON_RELEASE_VERSION 0x8004
#define REG_RESET_AND_MISC_CONTROL 0x001A
#define REG_PAD_SLEW_CONTROL 0x001E
#define REG_COMMAND_REGISTER 0x0080
#define HOST_COMMAND_APPLY_PATCH 0x0001
#define HOST_COMMAND_SET_STATE 0x0002
#define HOST_COMMAND_REFRESH 0x0004
#define HOST_COMMAND_WAIT_FOR_EVENT 0x0008
#define HOST_COMMAND_OK 0x8000
#define REG_ACCESS_CTL_STAT 0x0982
#define REG_PHYSICAL_ADDRESS_ACCESS 0x098A
#define REG_LOGICAL_ADDRESS_ACCESS 0x098E
#define MCU_VARIABLE_DATA0 0x0990
#define MCU_VARIABLE_DATA1 0x0992
#define REG_RESET_REGISTER 0x301A
#define REG_DAC_TXLO_ROW 0x316A
#define REG_DAC_TXLO 0x316C
#define REG_DAC_LD_4_5 0x3ED0
#define REG_DAC_LD_6_7 0x3ED2
#define REG_DAC_ECL 0x316E
#define REG_DELTA_DK_CONTROL 0x3180
#define REG_SAMP_COL_PUP2 0x3E14
#define REG_COLUMN_CORRECTION 0x30D4
#define REG_LL_ALGO 0xBC04
#define LL_EXEC_DELTA_DK_CORRECTION 0x0200
#define REG_CAM_DGAIN_RED 0xC840
#define REG_CAM_DGAIN_GREEN_1 0xC842
#define REG_CAM_DGAIN_GREEN_2 0xC844
#define REG_CAM_DGAIN_BLUE 0xC846
#define REG_CAM_SYSCTL_PLL_ENABLE 0xC97E
#define REG_CAM_SYSCTL_PLL_DIVIDER_M_N 0xC980
#define REG_CAM_SYSCTL_PLL_DIVIDER_P 0xC982
#define REG_CAM_SENSOR_CFG_Y_ADDR_START 0xC800
#define REG_CAM_SENSOR_CFG_X_ADDR_START 0xC802
#define REG_CAM_SENSOR_CFG_Y_ADDR_END 0xC804
#define REG_CAM_SENSOR_CFG_X_ADDR_END 0xC806
#define REG_CAM_SENSOR_CFG_PIXCLK 0xC808
#define REG_CAM_SENSOR_CFG_ROW_SPEED 0xC80C
#define REG_CAM_SENSOR_CFG_FINE_INTEG_TIME_MIN 0xC80E
#define REG_CAM_SENSOR_CFG_FINE_INTEG_TIME_MAX 0xC810
#define REG_CAM_SENSOR_CFG_FRAME_LENGTH_LINES 0xC812
#define REG_CAM_SENSOR_CFG_LINE_LENGTH_PCK 0xC814
#define REG_CAM_SENSOR_CFG_FINE_CORRECTION 0xC816
#define REG_CAM_SENSOR_CFG_CPIPE_LAST_ROW 0xC818
#define REG_CAM_SENSOR_CFG_REG_0_DATA 0xC826
#define REG_CAM_SENSOR_CONTROL_READ_MODE 0xC834
#define CAM_SENSOR_CONTROL_VERT_FLIP_EN 0x0002
#define CAM_SENSOR_CONTROL_HORZ_FLIP_EN 0x0001
#define CAM_SENSOR_CONTROL_BINNING_EN 0x0330
#define CAM_SENSOR_CONTROL_SKIPPING_EN 0x0110
#define CAM_MON_HEARTBEAT 0x8006 //the frame counter. updates on vertical blanking.
#define REG_CAM_CROP_WINDOW_XOFFSET 0xC854
#define REG_CAM_CROP_WINDOW_YOFFSET 0xC856
#define REG_CAM_CROP_WINDOW_WIDTH 0xC858
#define REG_CAM_CROP_WINDOW_HEIGHT 0xC85A
#define REG_CAM_CROP_CROPMODE 0xC85C
#define REG_CAM_OUTPUT_WIDTH 0xC868
#define REG_CAM_OUTPUT_HEIGHT 0xC86A
#define REG_CAM_OUTPUT_FORMAT 0xC86C
#define REG_CAM_OUTPUT_OFFSET 0xC870
#define REG_CAM_PORT_OUTPUT_CONTROL 0xC984
#define REG_CAM_OUPUT_FORMAT_YUV 0xC86E
#define REG_CAM_STAT_AWB_CLIP_WINDOW_XSTART 0xC914
#define REG_CAM_STAT_AWB_CLIP_WINDOW_YSTART 0xC916
#define REG_CAM_STAT_AWB_CLIP_WINDOW_XEND 0xC918
#define REG_CAM_STAT_AWB_CLIP_WINDOW_YEND 0xC91A
#define REG_CAM_STAT_AE_INITIAL_WINDOW_XSTART 0xC91C
#define REG_CAM_STAT_AE_INITIAL_WINDOW_YSTART 0xC91E
#define REG_CAM_STAT_AE_INITIAL_WINDOW_XEND 0xC920
#define REG_CAM_STAT_AE_INITIAL_WINDOW_YEND 0xC922
#define REG_CAM_PGA_PGA_CONTROL 0xC95E
#define REG_SYSMGR_NEXT_STATE 0xDC00
#define REG_SYSMGR_CURRENT_STATE 0xDC01
#define REG_PATCHLDR_LOADER_ADDRESS 0xE000
#define REG_PATCHLDR_PATCH_ID 0xE002
#define REG_PATCHLDR_FIRMWARE_ID 0xE004
#define REG_PATCHLDR_APPLY_STATUS 0xE008
#define REG_AUTO_BINNING_MODE 0xE801
#define REG_CAM_SENSOR_CFG_MAX_ANALOG_GAIN 0xC81C
#define REG_CROP_CROPMODE 0xC85C
#define REG_CAM_AET_AEMODE 0xC878
#define REG_CAM_AET_TARGET_AVG_LUMA 0xC87A
#define REG_CAM_AET_TARGET_AVERAGE_LUMA_DARK 0xC87B
#define REG_CAM_AET_BLACK_CLIPPING_TARGET 0xC87C
#define REG_CAM_AET_AE_MAX_VIRT_AGAIN 0xC886
#define REG_CAM_AET_MAX_FRAME_RATE 0xC88C
#define REG_CAM_AET_MIN_FRAME_RATE 0xC88E
#define REG_CAM_AET_TARGET_GAIN 0xC890
#define REG_AE_ALGORITHM 0xA404
#define REG_AE_TRACK_MODE 0xA802
#define REG_AE_TRACK_AE_TRACKING_DAMPENING_SPEED 0xA80A
#define REG_CAM_LL_START_BRIGHTNESS 0xC926
#define REG_CAM_LL_STOP_BRIGHTNESS 0xC928
#define REG_CAM_LL_START_GAIN_METRIC 0xC946
#define REG_CAM_LL_STOP_GAIN_METRIC 0xC948
#define REG_CAM_LL_START_TARGET_LUMA_BM 0xC952
#define REG_CAM_LL_STOP_TARGET_LUMA_BM 0xC954
#define REG_CAM_LL_START_SATURATION 0xC92A
#define REG_CAM_LL_END_SATURATION 0xC92B
#define REG_CAM_LL_START_DESATURATION 0xC92C
#define REG_CAM_LL_END_DESATURATION 0xC92D
#define REG_CAM_LL_START_DEMOSAIC 0xC92E
#define REG_CAM_LL_START_AP_GAIN 0xC92F
#define REG_CAM_LL_START_AP_THRESH 0xC930
#define REG_CAM_LL_STOP_DEMOSAIC 0xC931
#define REG_CAM_LL_STOP_AP_GAIN 0xC932
#define REG_CAM_LL_STOP_AP_THRESH 0xC933
#define REG_CAM_LL_START_NR_RED 0xC934
#define REG_CAM_LL_START_NR_GREEN 0xC935
#define REG_CAM_LL_START_NR_BLUE 0xC936
#define REG_CAM_LL_START_NR_THRESH 0xC937
#define REG_CAM_LL_STOP_NR_RED 0xC938
#define REG_CAM_LL_STOP_NR_GREEN 0xC939
#define REG_CAM_LL_STOP_NR_BLUE 0xC93A
#define REG_CAM_LL_STOP_NR_THRESH 0xC93B
#define REG_CAM_LL_START_CONTRAST_BM 0xC93C
#define REG_CAM_LL_STOP_CONTRAST_BM 0xC93E
#define REG_CAM_LL_GAMMA 0xC940
#define REG_CAM_LL_START_CONTRAST_GRADIENT 0xC942
#define REG_CAM_LL_STOP_CONTRAST_GRADIENT 0xC943
#define REG_CAM_LL_START_CONTRAST_LUMA_PERCENTAGE 0xC944
#define REG_CAM_LL_STOP_CONTRAST_LUMA_PERCENTAGE 0xC945
#define REG_CAM_LL_START_FADE_TO_BLACK_LUMA 0xC94A
#define REG_CAM_LL_STOP_FADE_TO_BLACK_LUMA 0xC94C
#define REG_CAM_LL_CLUSTER_DC_TH_BM 0xC94E
#define REG_CAM_LL_CLUSTER_DC_GATE_PERCENTAGE 0xC950
#define REG_CAM_LL_SUMMING_SENSITIVITY_FACTOR 0xC951
#define REG_CAM_LL_MODE 0xBC02 //might be BC07.
#define REG_CCM_DELTA_GAIN 0xB42A
#define REG_CAM_HUE_ANGLE 0xC873
// AWB
#define REG_AWB_AWB_MODE 0xC909
#define REG_AWB_COL_TEMP 0xC8F0//color temp, only writeable if awb mode is manual. in kelvin
#define REG_AWB_COL_TEMP_MAX 0xC8EE//maximum color temp in kelvin
#define REG_AWB_COL_TEMP_MIN 0xC8EC//minimum color temp in kelvin
// UVC
#define REG_UVC_AE_MODE 0xCC00
#define REG_UVC_AUTO_WHITE_BALANCE_TEMPERATURE 0xCC01
#define REG_UVC_AE_PRIORITY 0xCC02
#define REG_UVC_POWER_LINE_FREQUENCY 0xCC03
#define REG_UVC_EXPOSURE_TIME 0xCC04
#define REG_UVC_BACKLIGHT_COMPENSATION 0xCC08
#define REG_UVC_BRIGHTNESS 0xCC0A //set brightness in auto exposure mode.
#define REG_UVC_CONTRAST 0xCC0C //not exactly what the name suggests. See chip documentation
#define REG_UVC_GAIN 0xCC0E
#define REG_UVC_HUE 0xCC10
#define REG_UVC_SATURATION 0xCC12
#define REG_UVC_SHARPNESS 0xCC14
#define REG_UVC_GAMMA 0xCC16
#define REG_UVC_WHITE_BALANCE_TEMPERATURE 0xCC18
#define REG_UVC_FRAME_INTERVAL 0xCC1C
#define REG_UVC_MANUAL_EXPOSURE 0xCC20
#define REG_UVC_FLICKER_AVOIDANCE 0xCC21
#define REG_UVC_ALGO 0xCC22
#define REG_UVC_RESULT_STATUS 0xCC24
/**This variable selects the system event that the host wishes to wait for.
* 1: end of frame
* 2: start of frame */
#define REG_CMD_HANDLER_WAIT_FOR_EVENT 0xFC00
/** This variable determines the number of system event occurrences for which the
* Command Handler component will wait */
#define REG_CMD_HANDLER_NUM_WAIT_EVENTS 0xFC02
/**Result status code for last refresh command. Updates after refresh command.
* Possible values:
0x00: ENOERR - refresh successful
0x13: EINVCROPX - invalid horizontal crop configuration
0x14: EINVCROPY - invalid vertical crop configuration
0x15: EINVTC - invalid Tilt Correction percentage
*/
#define REG_SEQ_ERROR_CODE 0x8406
/* SYS_STATE values (for SYSMGR_NEXT_STATE and SYSMGR_CURRENT_STATE) */
#define MT9M114_SYS_STATE_ENTER_CONFIG_CHANGE 0x28
#define MT9M114_SYS_STATE_STREAMING 0x31
#define MT9M114_SYS_STATE_START_STREAMING 0x34
#define MT9M114_SYS_STATE_ENTER_SUSPEND 0x40
#define MT9M114_SYS_STATE_SUSPENDED 0x41
#define MT9M114_SYS_STATE_ENTER_STANDBY 0x50
#define MT9M114_SYS_STATE_STANDBY 0x52
#define MT9M114_SYS_STATE_LEAVE_STANDBY 0x54

static struct regval_list mt9m114_720p36_regs[] = {
    {REG_LOGICAL_ADDRESS_ACCESS, 2, 0x0000},
    {REG_CAM_SENSOR_CFG_Y_ADDR_START, 2, 124},
    {REG_CAM_SENSOR_CFG_X_ADDR_START, 2, 4},
    {REG_CAM_SENSOR_CFG_Y_ADDR_END, 2, 851},
    {REG_CAM_SENSOR_CFG_X_ADDR_END, 2, 1291},
    {REG_CAM_SENSOR_CFG_PIXCLK, 4, 48000000},
    {REG_CAM_SENSOR_CFG_ROW_SPEED, 2, 0x0001},
    {REG_CAM_SENSOR_CFG_FINE_INTEG_TIME_MIN, 2, 219},
    {REG_CAM_SENSOR_CFG_FINE_INTEG_TIME_MAX, 2, 1558},
    {REG_CAM_SENSOR_CFG_FRAME_LENGTH_LINES, 2, 778},
    {REG_CAM_SENSOR_CFG_LINE_LENGTH_PCK, 2, 1689},
    {REG_CAM_SENSOR_CFG_FINE_CORRECTION, 2, 96},
    {REG_CAM_SENSOR_CFG_CPIPE_LAST_ROW, 2, 723},
    {REG_CAM_SENSOR_CFG_REG_0_DATA, 2, 0x0020},
// {REG_CAM_SENSOR_CONTROL_READ_MODE, 1, 0x0000},
    {REG_CAM_CROP_WINDOW_XOFFSET, 2, 0x0000},
    {REG_CAM_CROP_WINDOW_YOFFSET, 2, 0x0000},
    {REG_CAM_CROP_WINDOW_WIDTH, 2, 1280},
    {REG_CAM_CROP_WINDOW_HEIGHT, 2, 720},
    {REG_CROP_CROPMODE, 1, 0x03},
    {REG_CAM_OUTPUT_WIDTH, 2, 1280},
    {REG_CAM_OUTPUT_HEIGHT, 2, 720},
    {REG_CAM_AET_AEMODE, 1, 0x00},
    {REG_CAM_AET_MAX_FRAME_RATE, 2, 0x24AB},
    {REG_CAM_AET_MIN_FRAME_RATE, 2, 0x24AB},
    {REG_CAM_STAT_AWB_CLIP_WINDOW_XSTART, 2, 0x0000},
    {REG_CAM_STAT_AWB_CLIP_WINDOW_YSTART, 2, 0x0000},
    {REG_CAM_STAT_AWB_CLIP_WINDOW_XEND, 2, 1279},
    {REG_CAM_STAT_AWB_CLIP_WINDOW_YEND, 2, 719},
    {REG_CAM_STAT_AE_INITIAL_WINDOW_XSTART, 2, 0x0000},
    {REG_CAM_STAT_AE_INITIAL_WINDOW_YSTART, 2, 0x0000},
    {REG_CAM_STAT_AE_INITIAL_WINDOW_XEND, 2, 255},
    {REG_CAM_STAT_AE_INITIAL_WINDOW_YEND, 2, 143},
    { 0xffff, 0xffff ,0xffff }	/* END MARKER */
};

static struct regval_list mt9m114_vga_30_scaling_regs[] = {
    {REG_LOGICAL_ADDRESS_ACCESS, 2, 0x0000},
    {REG_CAM_SENSOR_CFG_Y_ADDR_START, 2, 4},
    {REG_CAM_SENSOR_CFG_X_ADDR_START, 2, 4},
    {REG_CAM_SENSOR_CFG_Y_ADDR_END, 2, 971},
    {REG_CAM_SENSOR_CFG_X_ADDR_END, 2, 1291},
    {REG_CAM_SENSOR_CFG_PIXCLK, 4, 48000000},
    {REG_CAM_SENSOR_CFG_ROW_SPEED, 2, 1},//FIXME according to the documentation this value is unused, however we still set the default. No idea why
    {REG_CAM_SENSOR_CFG_FINE_INTEG_TIME_MIN, 2, 219},
    {REG_CAM_SENSOR_CFG_FINE_INTEG_TIME_MAX, 2, 1460},
    {REG_CAM_SENSOR_CFG_FRAME_LENGTH_LINES, 2, 1006},//FIXME might be a typo. default value is 1007
    {REG_CAM_SENSOR_CFG_LINE_LENGTH_PCK, 2, 1591},//FIXME might be a typo? default is 1589
    {REG_CAM_SENSOR_CFG_FINE_CORRECTION, 2, 96},
    {REG_CAM_SENSOR_CFG_CPIPE_LAST_ROW, 2, 963},
    {REG_CAM_SENSOR_CFG_REG_0_DATA, 2, 0x0020},
// {REG_CAM_SENSOR_CONTROL_READ_MODE, 1, 0x0000},
    {REG_CAM_CROP_WINDOW_XOFFSET, 2, 0x0000},
    {REG_CAM_CROP_WINDOW_YOFFSET, 2, 0x0000},
    {REG_CAM_CROP_WINDOW_WIDTH, 2, 1280},
    {REG_CAM_CROP_WINDOW_HEIGHT, 2, 960},
    {REG_CROP_CROPMODE, 1, 3},
    {REG_CAM_OUTPUT_WIDTH, 2, 640},
    {REG_CAM_OUTPUT_HEIGHT, 2, 480},
    {REG_CAM_AET_AEMODE, 1, 0x00},
    {REG_CAM_AET_MAX_FRAME_RATE, 2, 0x1DFD},
    {REG_CAM_AET_MIN_FRAME_RATE, 2, 0x1DFD},
    {REG_CAM_STAT_AWB_CLIP_WINDOW_XSTART, 2, 0x0000},
    {REG_CAM_STAT_AWB_CLIP_WINDOW_YSTART, 2, 0x0000},
    {REG_CAM_STAT_AWB_CLIP_WINDOW_XEND, 2, 639},
    {REG_CAM_STAT_AWB_CLIP_WINDOW_YEND, 2, 479},
    {REG_CAM_STAT_AE_INITIAL_WINDOW_XSTART, 2, 0x0000},
    {REG_CAM_STAT_AE_INITIAL_WINDOW_YSTART, 2, 0x0000},
    {REG_CAM_STAT_AE_INITIAL_WINDOW_XEND, 2, 127},
    {REG_CAM_STAT_AE_INITIAL_WINDOW_YEND, 2, 95},
// {REG_AUTO_BINNING_MODE,1, 0x00},
    { 0xffff, 0xffff ,0xffff }//array end,
};

static struct regval_list mt9m114_qvga_30_scaling_regs[] = {
    {REG_LOGICAL_ADDRESS_ACCESS, 2, 0x0000},
    {REG_CAM_SENSOR_CFG_Y_ADDR_START, 2, 4},
    {REG_CAM_SENSOR_CFG_X_ADDR_START, 2, 4},
    {REG_CAM_SENSOR_CFG_Y_ADDR_END, 2, 971},
    {REG_CAM_SENSOR_CFG_X_ADDR_END, 2, 1291},
    {REG_CAM_SENSOR_CFG_PIXCLK, 4, 48000000},
    {REG_CAM_SENSOR_CFG_ROW_SPEED, 2, 1},
    {REG_CAM_SENSOR_CFG_FINE_INTEG_TIME_MIN, 2, 219},
    {REG_CAM_SENSOR_CFG_FINE_INTEG_TIME_MAX, 2, 1460},
    {REG_CAM_SENSOR_CFG_FRAME_LENGTH_LINES, 2, 1006},
    {REG_CAM_SENSOR_CFG_LINE_LENGTH_PCK, 2, 1591},
    {REG_CAM_SENSOR_CFG_FINE_CORRECTION, 2, 96},
    {REG_CAM_SENSOR_CFG_CPIPE_LAST_ROW, 2, 963},
    {REG_CAM_SENSOR_CFG_REG_0_DATA, 2, 0x0020},
    //{REG_CAM_SENSOR_CONTROL_READ_MODE, 1, 0x0000},
    {REG_CAM_CROP_WINDOW_XOFFSET, 2, 0x0000},
    {REG_CAM_CROP_WINDOW_YOFFSET, 2, 0x0000},
    {REG_CAM_CROP_WINDOW_WIDTH, 2, 1280},
    {REG_CAM_CROP_WINDOW_HEIGHT, 2, 960},
    {REG_CROP_CROPMODE, 1, 3},
    {REG_CAM_OUTPUT_WIDTH, 2, 320},
    {REG_CAM_OUTPUT_HEIGHT, 2, 240},
    {REG_CAM_AET_AEMODE, 1, 0x00},
    {REG_CAM_AET_MAX_FRAME_RATE, 2, 0x1DFD},
    {REG_CAM_AET_MIN_FRAME_RATE, 2, 0x1DFD},
    {REG_CAM_STAT_AWB_CLIP_WINDOW_XSTART, 2, 0x0000},
    {REG_CAM_STAT_AWB_CLIP_WINDOW_YSTART, 2, 0x0000},
    {REG_CAM_STAT_AWB_CLIP_WINDOW_XEND, 2, 319},
    {REG_CAM_STAT_AWB_CLIP_WINDOW_YEND, 2, 239},
    {REG_CAM_STAT_AE_INITIAL_WINDOW_XSTART, 2, 0x0000},
    {REG_CAM_STAT_AE_INITIAL_WINDOW_YSTART, 2, 0x0000},
    {REG_CAM_STAT_AE_INITIAL_WINDOW_XEND, 2, 63},
    {REG_CAM_STAT_AE_INITIAL_WINDOW_YEND, 2, 47},
//  {REG_AUTO_BINNING_MODE,1, 0x00},

    { 0xffff, 0xffff ,0xffff }
};
/*
static struct regval_list mt9m114_qvga_30_scaling_regs[] = {
  {REG_CAM_OUTPUT_WIDTH, 2, 320},
  {REG_CAM_OUTPUT_HEIGHT, 2, 240},
  { 0xffff, 0xffff ,0xffff }
};*/
static struct regval_list pga_regs[] = {
    { 0x098E, 2, 0},
    { 0xC95E, 2, 3},
    { 0xC95E, 2, 2},
    { 0x3640, 2, 368},
    { 0x3642, 2, 3787},
    { 0x3644, 2, 22480},
    { 0x3646, 2, 33549},
    { 0x3648, 2, 62062},
    { 0x364A, 2, 32303},
    { 0x364C, 2, 18603},
    { 0x364E, 2, 26192},
    { 0x3650, 2, 52556},
    { 0x3652, 2, 44686},
    { 0x3654, 2, 32431},
    { 0x3656, 2, 23244},
    { 0x3658, 2, 7056},
    { 0x365A, 2, 64140},
    { 0x365C, 2, 37614},
    { 0x365E, 2, 32207},
    { 0x3660, 2, 19178},
    { 0x3662, 2, 26800},
    { 0x3664, 2, 45101},
    { 0x3666, 2, 43151},
    { 0x3680, 2, 13964},
    { 0x3682, 2, 1869},
    { 0x3684, 2, 9871},
    { 0x3686, 2, 32394},
    { 0x3688, 2, 38832},
    { 0x368A, 2, 492},
    { 0x368C, 2, 2894},
    { 0x368E, 2, 4687},
    { 0x3690, 2, 45006},
    { 0x3692, 2, 34192},
    { 0x3694, 2, 973},
    { 0x3696, 2, 2349},
    { 0x3698, 2, 25323},
    { 0x369A, 2, 41294},
    { 0x369C, 2, 46959},
    { 0x369E, 2, 3405},
    { 0x36A0, 2, 47531},
    { 0x36A2, 2, 38860},
    { 0x36A4, 2, 22506},
    { 0x36A6, 2, 37359},
    { 0x36C0, 2, 3569},
    { 0x36C2, 2, 36620},
    { 0x36C4, 2, 30224},
    { 0x36C6, 2, 11116},
    { 0x36C8, 2, 42739},
    { 0x36CA, 2, 1681},
    { 0x36CC, 2, 61514},
    { 0x36CE, 2, 13265},
    { 0x36D0, 2, 44462},
    { 0x36D2, 2, 51635},
    { 0x36D4, 2, 23184},
    { 0x36D6, 2, 39789},
    { 0x36D8, 2, 22480},
    { 0x36DA, 2, 3885},
    { 0x36DC, 2, 64882},
    { 0x36DE, 2, 3505},
    { 0x36E0, 2, 46314},
    { 0x36E2, 2, 26864},
    { 0x36E4, 2, 36813},
    { 0x36E6, 2, 41555},
    { 0x3700, 2, 1325},
    { 0x3702, 2, 60557},
    { 0x3704, 2, 46961},
    { 0x3706, 2, 13199},
    { 0x3708, 2, 25234},
    { 0x370A, 2, 10253},
    { 0x370C, 2, 36912},
    { 0x370E, 2, 46449},
    { 0x3710, 2, 17713},
    { 0x3712, 2, 19282},
    { 0x3714, 2, 10509},
    { 0x3716, 2, 53295},
    { 0x3718, 2, 38417},
    { 0x371A, 2, 8881},
    { 0x371C, 2, 26834},
    { 0x371E, 2, 27981},
    { 0x3720, 2, 39469},
    { 0x3722, 2, 34321},
    { 0x3724, 2, 5232},
    { 0x3726, 2, 20978},
    { 0x3740, 2, 35307},
    { 0x3742, 2, 49806},
    { 0x3744, 2, 62036},
    { 0x3746, 2, 23250},
    { 0x3748, 2, 27830},
    { 0x374A, 2, 8111},
    { 0x374C, 2, 51085},
    { 0x374E, 2, 33653},
    { 0x3750, 2, 24914},
    { 0x3752, 2, 29270},
    { 0x3754, 2, 5133},
    { 0x3756, 2, 5933},
    { 0x3758, 2, 52436},
    { 0x375A, 2, 13362},
    { 0x375C, 2, 18166},
    { 0x375E, 2, 37550},
    { 0x3760, 2, 39566},
    { 0x3762, 2, 61300},
    { 0x3764, 2, 23602},
    { 0x3766, 2, 26198},
    { 0x3782, 2, 480},
    { 0x3784, 2, 672},
    { 0xC960, 2, 2800},
    { 0xC962, 2, 31149},
    { 0xC964, 2, 22448},
    { 0xC966, 2, 30936},
    { 0xC968, 2, 29792},
    { 0xC96A, 2, 4000},
    { 0xC96C, 2, 33143},
    { 0xC96E, 2, 33116},
    { 0xC970, 2, 33041},
    { 0xC972, 2, 32855},
    { 0xC974, 2, 6500},
    { 0xC976, 2, 31786},
    { 0xC978, 2, 26268},
    { 0xC97A, 2, 32319},
    { 0xC97C, 2, 29650},
    { 0xC95E, 2, 3},
    { 0xffff, 0xffff ,0xffff}
};

static struct regval_list ccm_awb_regs[] = {
    { 0xC892, 2, 615},
    { 0xC894, 2, 65306},
    { 0xC896, 2, 65459},
    { 0xC898, 2, 65408},
    { 0xC89A, 2, 358},
    { 0xC89C, 2, 3},
    { 0xC89E, 2, 65434},
    { 0xC8A0, 2, 65204},
    { 0xC8A2, 2, 589},
    { 0xC8A4, 2, 447},
    { 0xC8A6, 2, 65281},
    { 0xC8A8, 2, 65523},
    { 0xC8AA, 2, 65397},
    { 0xC8AC, 2, 408},
    { 0xC8AE, 2, 65533},
    { 0xC8B0, 2, 65434},
    { 0xC8B2, 2, 65255},
    { 0xC8B4, 2, 680},
    { 0xC8B6, 2, 473},
    { 0xC8B8, 2, 65318},
    { 0xC8BA, 2, 65523},
    { 0xC8BC, 2, 65459},
    { 0xC8BE, 2, 306},
    { 0xC8C0, 2, 65512},
    { 0xC8C2, 2, 65498},
    { 0xC8C4, 2, 65229},
    { 0xC8C6, 2, 706},
    { 0xC8C8, 2, 117},
    { 0xC8CA, 2, 284},
    { 0xC8CC, 2, 154},
    { 0xC8CE, 2, 261},
    { 0xC8D0, 2, 164},
    { 0xC8D2, 2, 172},
    { 0xC8D4, 2, 2700},
    { 0xC8D6, 2, 3850},
    { 0xC8D8, 2, 6500},
    { 0xC914, 2, 0},
    { 0xC916, 2, 0},
    { 0xC918, 2, 1279},
    { 0xC91A, 2, 719},
    { 0xC904, 2, 51},
    { 0xC906, 2, 64},
    { 0xC8F2, 1, 3},
    { 0xC8F3, 1, 2},
    { 0xC906, 2, 60},
    { 0xC8F4, 2, 0},
    { 0xC8F6, 2, 0},
    { 0xC8F8, 2, 0},
    { 0xC8FA, 2, 59172},
    { 0xC8FC, 2, 5507},
    { 0xC8FE, 2, 8261},
    { 0xC900, 2, 1023},
    { 0xC902, 2, 124},
    { 0xC90C, 1, 128},
    { 0xC90D, 1, 128},
    { 0xC90E, 1, 128},
    { 0xC90F, 1, 136},
    { 0xC910, 1, 128},
    { 0xC911, 1, 128},
    { 0xffff, 0xffff ,0xffff}
};


using std::string;
using namespace flair::core;

namespace flair {
namespace sensor {

//construct V4LCamera with 1280*720 because
//CV_CAP_PROP_FRAME_WIDTH and CV_CAP_PROP_FRAME_HEIGHT does not work properly (isp problem?)
ArDrone2CamH::ArDrone2CamH(string name,uint16_t width,uint16_t height,uint8_t priority) : V4LCamera(name,1,1280,720,cvimage::Type::Format::UYVY,priority) {
    //handle resolution
    if(width==1280 && height==720) {
        wh_regval_list=&mt9m114_720p36_regs[0];
    } else if(width==640 && height==360) {
        wh_regval_list=&mt9m114_vga_30_scaling_regs[0];
    } else if(width==320 && height==180) {
        wh_regval_list=&mt9m114_qvga_30_scaling_regs[0];
    } else {
        Thread::Err("Invalid width (%i) and height (%i)\n",width,height);
        wh_regval_list=&mt9m114_qvga_30_scaling_regs[0];//default value
    }

    //realocate output, because Camera was created with 1280*720
    //do not allocate imagedata, allocation is done by the camera
    delete output;
    output=new cvimage((IODevice*)this,width,height,cvimage::Type::Format::UYVY,"out",false);

    //i2cport
    //we assume there is no other device on this bus
    i2cport=new Unix_I2cPort((Thread*)this,"camv-i2c","/dev/i2c-3");
    i2cport->SetSlave(0x5d);

    mt9m114_detect();
    
    SetIsReady(true);
}

ArDrone2CamH::~ArDrone2CamH() {

}

void ArDrone2CamH::mt9m114_detect(void) {
    uint32_t chip_id;
    uint32_t mon_major_version;
    uint32_t mon_minor_version;
    uint32_t mon_release_version;

    soc1040_read_reg(REG_CHIP_ID, &chip_id,2);
    soc1040_read_reg(REG_MON_MAJOR_VERSION, &mon_major_version,2);
    soc1040_read_reg(REG_MON_MINOR_VERION, &mon_minor_version,2);
    soc1040_read_reg(REG_MON_RELEASE_VERSION, &mon_release_version,2);

    if(chip_id!=0)
        Printf("MT9M114 found : chip_id:%x major:%x minor:%x release:%x\n", chip_id,mon_major_version,mon_minor_version,mon_release_version);

    if (chip_id != 0x2481) { // default chipid
        Thread::Err("invalid chipid\n");
        return;
    }

    mt9m114_init();
}

void ArDrone2CamH::mt9m114_init(void) {
    int ret = 0;
    ret += mt9m114_reset();

    ret += mt9m114_PLL_settings();
    //ret += mt9m114_write_array(mt9m114_vga_30_scaling_regs);
    ret += mt9m114_write_array(wh_regval_list);
    ret += mt9m114_sensor_optimization();
    ret += mt9m114_errata_1();
    ret += mt9m114_errata_2();
    ret += mt9m114_write_array(pga_regs);
    ret += mt9m114_write_array(ccm_awb_regs);
    /*
    ret += mt9m114_CPIPE_preference();
    ret += mt9m114_features();
    ret += mt9m114_write_array(uvc_ctrl_regs);
    ret += mt9m114_change_config();
    ret += mt9m114_patch2_black_lvl_correction_fix();
    ret += mt9m114_patch3_adaptive_sensitivity();*/
    if (ret != 0) {
        Thread::Err("MT9M114","MT9M114 : init fail\n");
    }

}

int ArDrone2CamH::mt9m114_reset(void) {
    uint32_t v;
    Printf("MT9M114 : Resetting chip!\n");

    int fd=open("/dev/v4l-subdev8",O_WRONLY);//part of the reset sequence?
    close(fd);

    soc1040_read_reg( REG_RESET_AND_MISC_CONTROL, &v,2);
    soc1040_write_reg(REG_RESET_AND_MISC_CONTROL, v|0x01,2);
    SleepMS(100); //FIXME This sleep shouldn't be here according to the documentation
    soc1040_write_reg(REG_RESET_AND_MISC_CONTROL, v & (~1),2);
    SleepMS(100); //datasheet documentation
    mt9m114_errata_2();

    system("media-ctl -f \"\\\"soc1040\\\":0[UYVY2X8 1280x720]\"");//part of the reset sequence?
    return 0;
}

int ArDrone2CamH::mt9m114_PLL_settings(void) {
    soc1040_write_reg(REG_LOGICAL_ADDRESS_ACCESS, 0x0000,2);
    soc1040_write_reg(REG_CAM_SYSCTL_PLL_ENABLE, 1, 1); //no idea what it does. 1 is default
    soc1040_write_reg(REG_CAM_SYSCTL_PLL_DIVIDER_M_N, 0x0120,2); //no idea, default is 0x09a0
    soc1040_write_reg(REG_CAM_SYSCTL_PLL_DIVIDER_P, 0x0700,2);//no idea, default is 0x0700
    return 0;
}

int ArDrone2CamH::mt9m114_errata_1(void) {
    soc1040_write_reg( REG_SAMP_COL_PUP2,0xFF39,2); //no idea, register is undocumented
    return 0;
}

int ArDrone2CamH::mt9m114_errata_2(void) {
    //FIXME this doesn't make sense
    //bit 2 is reserved and the default value is 0 but it is set to 1.
    //bit 5 is reserved, default is 0 but it is set to 1
    //MSB is the actual reset register. No idea why the others are changed.
    soc1040_write_reg(REG_RESET_REGISTER, 564,2); //1000110100
    return 0;
}

int ArDrone2CamH::mt9m114_sensor_optimization(void) {
    //FIXME all registers used in here are undocumented. No idea about their purpose.
    //      Maybe some commands for the fpga?
    soc1040_write_reg( REG_DAC_TXLO_ROW,0x8270,2);
    soc1040_write_reg(REG_DAC_TXLO, 0x8270,2);
    soc1040_write_reg(REG_DAC_LD_4_5, 0x3605,2);
    soc1040_write_reg(REG_DAC_LD_6_7, 0x77FF,2);
    soc1040_write_reg(REG_DAC_ECL, 0xC233,2);
    soc1040_write_reg(REG_DELTA_DK_CONTROL, 0x87FF,2);
    soc1040_write_reg(REG_COLUMN_CORRECTION, 0x6080,2);
    soc1040_write_reg(REG_AE_TRACK_MODE,0x0008,2);
    return 0;
}

void ArDrone2CamH::SetGain(float value) {
    int ret = 0;
    uint16_t shiftedValue = value*255;

    printf("gain %i\n",shiftedValue);
    ret = soc1040_write_reg(REG_UVC_GAIN,shiftedValue,2);

    if(0 != ret) {
        Thread::Err("error writing value. errno: 0x%x\n",  ret);
        return ;
    }

    ret = check_uvc_status( __func__);
    if(0 != ret) {
        //error has already been printed by check_uvc_status.
        return;
    }
    uint32_t v;
    soc1040_read_reg(REG_UVC_GAIN,&v,2);
    printf("read %i\n",v);
    mt9m114_refresh();
}

void ArDrone2CamH::SetBrightness(float value) {
    int ret = 0;
    uint16_t shiftedValue = value*255;

    ret = soc1040_write_reg(REG_UVC_BRIGHTNESS,shiftedValue,2);

    if(0 != ret) {
        Thread::Err("error writing value. errno: 0x%x\n", ret);
        return;
    }
    ret = check_uvc_status( __func__);

    if(0 != ret) {
        //error has already been printed by check_uvc_status.
        return;
    }

    mt9m114_refresh();
}

void ArDrone2CamH::SetSaturation(float value) {
    int ret = 0;
    uint16_t shiftedValue = value*255;

    ret = soc1040_write_reg(REG_UVC_SATURATION,shiftedValue,2);

    if(0 != ret) {
        Thread::Err("error writing value. errno: 0x%x\n",  ret);
        return ;
    }

    ret = check_uvc_status( __func__);
    if(0 != ret) {
        //error has already been printed by check_uvc_status.
        return;
    }

    mt9m114_refresh();
}

void ArDrone2CamH::SetExposure(float value) {
    int ret = 0;
    uint32_t shiftedValue = value*350;//trouve experimentalment

    ret = soc1040_write_reg(REG_UVC_EXPOSURE_TIME,shiftedValue,4);

    if(0 != ret) {
        Thread::Err("error writing value. errno: 0x%x\n",  ret);
        return ;
    }

    ret = check_uvc_status( __func__);
    if(0 != ret) {
        //error has already been printed by check_uvc_status.
        return;
    }

    mt9m114_refresh();
}

void ArDrone2CamH::SetHue(float value) {
    int8_t shiftedValue = (value-.5)*255;

    int ret = soc1040_write_reg(REG_CAM_HUE_ANGLE, shiftedValue,1);

    if(0 != ret) {
        Thread::Err("error writing value. errno: 0x%x\n",  ret);
        return ;
    }

    mt9m114_refresh();
}
//not exactly what the name suggests. See chip documentation
void ArDrone2CamH::SetContrast(float value) {
    int ret = 0;
    uint16_t shiftedValue = 16+(value*48);//min 16, max 64

    ret = soc1040_write_reg(REG_UVC_CONTRAST,shiftedValue,2);

    if(0 != ret) {
        Thread::Err("error writing value. errno: 0x%x\n", ret);
        return ;
    }
    ret = check_uvc_status( __func__);
    if(0 != ret) {
        //error has already been printed by check_uvc_status.
        return ;
    }
    mt9m114_refresh();
}

void ArDrone2CamH::SetAutoExposure(bool value) {
    if(value == true) {
        soc1040_write_reg( REG_UVC_AE_MODE, 0x02,1);
    } else {
        soc1040_write_reg( REG_UVC_AE_MODE, 0x01,1);
    }

    mt9m114_refresh();
}

/**
 * soc1040_read_reg - Read a value from a register in an soc1040 sensor device
 * @reg: register address / offset
 * @val: stores the value that gets read
 * @data_length: length of data to be read
 *
 * Read a value from a register in an soc1040 sensor device.
 * The value is returned in 'val'.
 * Returns zero if successful, or non-zero otherwise.
 */
int ArDrone2CamH::soc1040_read_reg(uint16_t reg, uint32_t *val,uint16_t data_length) {
    int err;
    unsigned char data[4];
    unsigned char add[2];

    if (data_length != I2C_8BIT && data_length != I2C_16BIT
            && data_length != I2C_32BIT)
        return -EINVAL;

    /* Write addr - high byte goes out first */
    add[0] = (uint8_t) (reg >> 8);;
    add[1] = (uint8_t) (reg & 0xff);
    err=i2cport->Write(add,2);

    /* Read back data */
    if (err >= 0) {
        err = i2cport->Read(data,data_length);
    }
    if (err >= 0) {
        *val = 0;
        /* high byte comes first */
        if (data_length == I2C_8BIT)
            *val = data[0];
        else if (data_length == I2C_16BIT)
            *val = data[1] + (data[0] << 8);
        else
            *val = data[3] + (data[2] << 8) +
                   (data[1] << 16) + (data[0] << 24);
        return 0;
    }
    Thread::Err("read from offset 0x%x error %d\n", reg, err);
    return err;
}

/**
 * Write a value to a register in soc1040 sensor device.
 * @reg: Address of the register to read value from.
 * @val: Value to be written to a specific register.
 * Returns zero if successful, or non-zero otherwise.
 */
int ArDrone2CamH::soc1040_write_reg(uint16_t reg,uint32_t val, uint16_t data_length) {
    int err = 0;
    unsigned char data[6];

    if (data_length != I2C_8BIT && data_length != I2C_16BIT
            && data_length != I2C_32BIT)
        return -EINVAL;


    /* high byte goes out first */
    data[0] = (uint8_t) (reg >> 8);
    data[1] = (uint8_t) (reg & 0xff);
    if (data_length == I2C_8BIT) {
        data[2] = val & 0xff;
    } else if (data_length == I2C_16BIT) {
        data[2] = (val >> 8) & 0xff;
        data[3] = val & 0xff;
    } else {
        data[2] = (val >> 24) & 0xff;
        data[3] = (val >> 16) & 0xff;
        data[4] = (val >> 8) & 0xff;
        data[5] = val & 0xff;
    }

    err = i2cport->Write(data,2+data_length);

    if (err >= 0) return 0;

    Thread::Err("write from offset 0x%x error %d\n", reg, err);

    return err;
}

/*
 * Write a list of register settings; ff/ff stops the process.
 */
int ArDrone2CamH::mt9m114_write_array(struct regval_list *vals) {
    int i=0;

    while ((vals[i].reg_num != 0xffff) || (vals[i].value != 0xffff)) {
        int ret = soc1040_write_reg(vals[i].reg_num,  vals[i].value,vals[i].size);
        if (ret < 0) {
            return ret;
        }
        i++;
    }
    return 0;
}
/**
* Reads the uvc_result_status register.
* If it contains an error the error is printed to dmesg together with funcName.
*
* @note uvc_result_status updates on vertical blanking. Therefore it might not
* contain the correct value if you do not wait until vertical blanking.
* @param funcName Name of the calling function.
* @return In case of error: The errno code or -1 if the error code is unknown. 0 Otherwise.
*/
int ArDrone2CamH::check_uvc_status(const char* funcName) {
    uint32_t result;
    soc1040_read_reg(REG_UVC_RESULT_STATUS, &result,1);
    /* uvc_result_status can contain the following error codes:
    0x00 ENOERR no error - change was accepted and actioned.
    0x08 EACCES permission denied.
    0x09 EBUSY entity busy, cannot support operation.
    0x0C EINVAL invalid argument.
    0x0E ERANGE parameter out-of-range.
    0x0F ENOSYS operation not supported.
    */
    switch(result) {
    case 0: //no error
        //Printf("%s REG_UVC_RESULT_STATUS: ENOERR\n", funcName);
        return 0;
    case 0x08: //EACCES
        Printf("%s REG_UVC_RESULT_STATUS: EACCES\n", funcName);
        return EACCES;
    case 0x09: //EBUSY
        Printf("%s REG_UVC_RESULT_STATUS: EBUSY\n", funcName);
        return EBUSY;
    case 0x0C: //EINVAL
        Printf("%s REG_UVC_RESULT_STATUS: EINVAL\n", funcName);
        return EINVAL;
    case 0x0E: //ERANGE
        Printf("%s REG_UVC_RESULT_STATUS: ERANGE\n", funcName);
        return ERANGE;
    case 0x0F: //ENOSYS
        Printf("%s REG_UVC_RESULT_STATUS: ENOSYS\n", funcName);
        return ENOSYS;
    default:
        Printf("%s REG_UVC_RESULT_STATUS: Unknown error code\n", funcName);
        return -1;
    }
}

/**
* Refresh subsystems without requiring a sensor configuration change.
* @note This call blocks till the next frame.
* @return
*/
int ArDrone2CamH::mt9m114_refresh(void) {
    //Printf("referesh\n");
    uint32_t v=0;//a temporary variable used for several read commands
    //make sure that the refresh command is really processed and that
    //exposure and user changes are processed as well.
    soc1040_read_reg(REG_UVC_ALGO, &v,2);
    v |= 0b111;
    soc1040_write_reg(REG_UVC_ALGO, v,2);
    //Changes to REG_UVC_ALGO take effect on vertical blanking, therefore wait one frame.
    mt9m114_wait_num_frames(1);
    // First check that the FW is ready to accept a Refresh command
    soc1040_read_reg(REG_COMMAND_REGISTER, &v,2);
    if (v & HOST_COMMAND_REFRESH) {
        Thread::Warn("Refresh cmd bit is already set 0x%x\n",v);
        return -1;
    }
    // Issue the Refresh command, and set the 'OK' bit at the time time so
    //we can detect if the command fails
    soc1040_write_reg(REG_COMMAND_REGISTER, HOST_COMMAND_REFRESH|HOST_COMMAND_OK,2);
    // Wait for the FW to complete the command
    poll_command_register_bit(HOST_COMMAND_REFRESH);
    // Check the 'OK' bit to see if the command was successful
    soc1040_read_reg( REG_COMMAND_REGISTER, &v,2);
    if ( !(v & HOST_COMMAND_OK)) {
        Thread::Err("refresh command fail\n");
        return -1;
    }
    //check refresh command error code
    soc1040_read_reg(REG_SEQ_ERROR_CODE, &v,1);
    if(v != 0) {
        Thread::Err("Refresh ERROR: %x\n", v);
    }
    soc1040_read_reg( REG_UVC_RESULT_STATUS, &v,1);
    //Printf("REG_UVC_RESULT_STATUS: %x\n", v);
    //the refresh command schedules an update on the next end of frame.
    //It does not wait until the end of frame is actually reached.
    //Therefore we need to wait until the end of the frame manually.
    mt9m114_wait_num_frames(1);
    //Printf("referesh ok\n");
    return 0;
}

/**
* Waits until a number of frames have passed
* This method can be used to wait for vertical blanking as vertical blanking
* occurs at the end of a frame.
* @param sd
* @param numFrames the number of frames to wait
* @return -1 in case of error, 0 otherwise.
*/
int ArDrone2CamH::mt9m114_wait_num_frames(uint16_t numFrames) {
    //Printf("wait\n");
    //FIXME copy & paste from set_state_command
    uint32_t v=0;
    uint32_t frameCountBefore = 0;
    uint32_t frameCountAfter = 0;
    //get the current frame count
    soc1040_read_reg(CAM_MON_HEARTBEAT,&frameCountBefore,2);
    //Printf("frame %i\n",frameCountBefore);
    //specify for which event we want to wait: 2 = start of next frame
    soc1040_write_reg(REG_CMD_HANDLER_WAIT_FOR_EVENT, 2, 2);
    //specify for how much frames we want to wait
    soc1040_write_reg( REG_CMD_HANDLER_NUM_WAIT_EVENTS, numFrames,2);
    // (Optional) First check that the FW is ready to accept a new command
    soc1040_read_reg(REG_COMMAND_REGISTER, &v,2);
    if (v & HOST_COMMAND_WAIT_FOR_EVENT) {
        //This should never happen as long as nobody opens the driver device in async mode.
        Thread::Warn("Host command wait for event already set 0x%x\n",v);
        return -1;
    }
    // (Mandatory) Issue the wait for command
    // We set the 'OK' bit so we can detect if the command fails. The chip will unset the OK bit if everything is ok.
    soc1040_write_reg(REG_COMMAND_REGISTER, HOST_COMMAND_WAIT_FOR_EVENT | HOST_COMMAND_OK,2);
    // Wait for the FW to complete the command (clear the HOST_COMMAND_1 bit)
    poll_command_register_bit(HOST_COMMAND_WAIT_FOR_EVENT);
    // Check the 'OK' bit to see if the command was successful
    soc1040_read_reg(REG_COMMAND_REGISTER, &v,2);
    if ( !(v & HOST_COMMAND_OK)) {
        Thread::Warn("wait for end of frame failed: TIMEOUT?!\n");
        return -1;
    }
    //read frame count after
    soc1040_read_reg(CAM_MON_HEARTBEAT, &frameCountAfter,2);
    if(frameCountBefore == frameCountAfter) {
        Thread::Warn("wait for end of frame failed. Frame is still the same.\n");
    }
    //Printf("wait ok\n");
    return 0;
}

/**
*
* @param bit_mask
* @return 0 if everything is ok, 1 otherwise
*/
int ArDrone2CamH::poll_command_register_bit(uint16_t bit_mask) {
    int i=0;
    uint32_t v=0;
    //Printf("poll_command_register_bit\n");
    for (i = 0; i < 500; i++) {
        SleepMS(10);
        soc1040_read_reg(REG_COMMAND_REGISTER, &v,2);
        if (!(v & bit_mask)) {
            //Printf("poll_command_register_bit ok\n");
            return 0;
        }
    }
    Printf("poll_command_register_bit ko\n");
    return 1;
}

} // end namespace sensor
} // end namespace flair
