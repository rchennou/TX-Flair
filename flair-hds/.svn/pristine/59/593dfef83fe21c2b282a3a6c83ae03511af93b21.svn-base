//  created:    2014/07/16
//  filename:   ArDrone2CamV.cpp
//
//  author:     Guillaume Sanahuja
//
//  version:    $Id: $
//
//  purpose:    class for ardrone2 horizontal camera
//
//
/*********************************************************************/

//control functions from V4L2 driver:

/*
 * A V4L2 driver for OmniVision OV7670 cameras.
 *
 * Copyright 2006 One Laptop Per Child Association, Inc.  Written
 * by Jonathan Corbet with substantial inspiration from Mark
 * McClelland's ovcamchip code.
 *
 * Copyright 2006-7 Jonathan Corbet <corbet@lwn.net>
 *
 * This file may be distributed under the terms of the GNU General
 * Public License, version 2.
 */

#include "ArDrone2CamV.h"
#include <Unix_I2cPort.h>

#define PI ((float)3.14159265358979323846)

/* Registers */
#define REG_GAIN	0x00	/* Gain lower 8 bits (rest in vref) */
#define REG_BLUE	0x01	/* blue gain */
#define REG_RED		0x02	/* red gain */
#define REG_VREF	0x03	/* Pieces of GAIN, VSTART, VSTOP */
#define REG_COM1	0x04	/* Control 1 */
#define  COM1_CCIR656	  0x40  /* CCIR656 enable */
#define REG_BAVE	0x05	/* U/B Average level */
#define REG_GbAVE	0x06	/* Y/Gb Average level */
#define REG_AECHH	0x07	/* AEC MS 5 bits */
#define REG_RAVE	0x08	/* V/R Average level */
#define REG_COM2	0x09	/* Control 2 */
#define  COM2_SSLEEP	  0x10	/* Soft sleep mode */
#define REG_PID		0x0a	/* Product ID MSB */
#define REG_VER		0x0b	/* Product ID LSB */
#define REG_COM3	0x0c	/* Control 3 */
#define  COM3_SWAP	  0x40	  /* Byte swap */
#define  COM3_SCALEEN	  0x08	  /* Enable scaling */
#define  COM3_DCWEN	  0x04	  /* Enable downsamp/crop/window */
#define REG_COM4	0x0d	/* Control 4 */
#define REG_COM5	0x0e	/* All "reserved" */
#define REG_COM6	0x0f	/* Control 6 */
#define REG_AECH	0x10	/* More bits of AEC value */
#define REG_CLKRC	0x11	/* Clocl control */
#define   CLK_EXT	  0x40	  /* Use external clock directly */
#define   CLK_SCALE	  0x3f	  /* Mask for internal clock scale */
#define REG_COM7	0x12	/* Control 7 */
#define   COM7_RESET	  0x80	  /* Register reset */
#define   COM7_FMT_MASK	  0x38
#define   COM7_FMT_VGA	  0x00
#define	  COM7_FMT_CIF	  0x20	  /* CIF format */
#define   COM7_FMT_QVGA	  0x00	  /* QVGA format */
#define   COM7_FMT_QCIF	  0x08	  /* QCIF format */
#define	  COM7_RGB	  0x04	  /* bits 0 and 2 - RGB format */
#define	  COM7_YUV	  0x00	  /* YUV */
#define	  COM7_BAYER	  0x01	  /* Bayer format */
#define	  COM7_PBAYER	  0x05	  /* "Processed bayer" */
#define REG_COM8	0x13	/* Control 8 */
#define   COM8_FASTAEC	  0x80	  /* Enable fast AGC/AEC */
#define   COM8_AECSTEP	  0x40	  /* Unlimited AEC step size */
#define   COM8_BFILT	  0x20	  /* Band filter enable */
#define   COM8_AGC	  0x04	  /* Auto gain enable */
#define   COM8_AWB	  0x02	  /* White balance enable */
#define   COM8_AEC	  0x01	  /* Auto exposure enable */
#define REG_COM9	0x14	/* Control 9  - gain ceiling */
#define REG_COM10	0x15	/* Control 10 */
#define   COM10_HSYNC	  0x40	  /* HSYNC instead of HREF */
#define   COM10_PCLK_HB	  0x20	  /* Suppress PCLK on horiz blank */
#define   COM10_HREF_REV  0x08	  /* Reverse HREF */
#define   COM10_VS_LEAD	  0x04	  /* VSYNC on clock leading edge */
#define   COM10_VS_NEG	  0x02	  /* VSYNC negative */
#define   COM10_HS_NEG	  0x01	  /* HSYNC negative */
#define REG_HSTART	0x17	/* Horiz start high bits */
#define REG_HSTOP	0x18	/* Horiz stop high bits */
#define REG_VSTART	0x19	/* Vert start high bits */
#define REG_VSTOP	0x1a	/* Vert stop high bits */
#define REG_PSHFT	0x1b	/* Pixel delay after HREF */
#define REG_MIDH	0x1c	/* Manuf. ID high */
#define REG_MIDL	0x1d	/* Manuf. ID low */
#define REG_MVFP	0x1e	/* Mirror / vflip */
#define   MVFP_MIRROR	  0x20	  /* Mirror image */
#define   MVFP_FLIP	  0x10	  /* Vertical flip */

#define REG_AEW		0x24	/* AGC upper limit */
#define REG_AEB		0x25	/* AGC lower limit */
#define REG_VPT		0x26	/* AGC/AEC fast mode op region */
#define REG_HSYST	0x30	/* HSYNC rising edge delay */
#define REG_HSYEN	0x31	/* HSYNC falling edge delay */
#define REG_HREF	0x32	/* HREF pieces */
#define REG_TSLB	0x3a	/* lots of stuff */
#define   TSLB_YLAST	  0x04	  /* UYVY or VYUY - see com13 */
#define REG_COM11	0x3b	/* Control 11 */
#define   COM11_NIGHT	  0x80	  /* NIght mode enable */
#define   COM11_NMFR	  0x60	  /* Two bit NM frame rate */
#define   COM11_HZAUTO	  0x10	  /* Auto detect 50/60 Hz */
#define	  COM11_50HZ	  0x08	  /* Manual 50Hz select */
#define   COM11_EXP	  0x02
#define REG_COM12	0x3c	/* Control 12 */
#define   COM12_HREF	  0x80	  /* HREF always */
#define REG_COM13	0x3d	/* Control 13 */
#define   COM13_GAMMA	  0x80	  /* Gamma enable */
#define	  COM13_UVSAT	  0x40	  /* UV saturation auto adjustment */
#define   COM13_UVSWAP	  0x01	  /* V before U - w/TSLB */
#define REG_COM14	0x3e	/* Control 14 */
#define   COM14_DCWEN	  0x10	  /* DCW/PCLK-scale enable */
#define REG_EDGE	0x3f	/* Edge enhancement factor */
#define REG_COM15	0x40	/* Control 15 */
#define   COM15_R10F0	  0x00	  /* Data range 10 to F0 */
#define	  COM15_R01FE	  0x80	  /*            01 to FE */
#define   COM15_R00FF	  0xc0	  /*            00 to FF */
#define   COM15_RGB565	  0x10	  /* RGB565 output */
#define   COM15_RGB555	  0x30	  /* RGB555 output */
#define REG_COM16	0x41	/* Control 16 */
#define   COM16_AWBGAIN   0x08	  /* AWB gain enable */
#define REG_COM17	0x42	/* Control 17 */
#define   COM17_AECWIN	  0xc0	  /* AEC window - must match COM4 */
#define   COM17_CBAR	  0x08	  /* DSP Color bar */

/*
 * This matrix defines how the colors are generated, must be
 * tweaked to adjust hue and saturation.
 *
 * Order: v-red, v-green, v-blue, u-red, u-green, u-blue
 *
 * They are nine-bit signed quantities, with the sign bit
 * stored in 0x58.  Sign for v-red is bit 0, and up from there.
 */
#define	REG_CMATRIX_BASE 0x4f
//#define   CMATRIX_LEN 6
#define REG_CMATRIX_SIGN 0x58


#define REG_BRIGHT	0x55	/* Brightness */
#define REG_CONTRAS	0x56	/* Contrast control */

#define REG_GFIX	0x69	/* Fix gain control */

#define REG_REG76	0x76	/* OV's name */
#define   R76_BLKPCOR	  0x80	  /* Black pixel correction enable */
#define   R76_WHTPCOR	  0x40	  /* White pixel correction enable */

#define REG_RGB444	0x8c	/* RGB 444 control */
#define   R444_ENABLE	  0x02	  /* Turn on RGB444, overrides 5x5 */
#define   R444_RGBX	  0x01	  /* Empty nibble at end */

#define REG_HAECC1	0x9f	/* Hist AEC/AGC control 1 */
#define REG_HAECC2	0xa0	/* Hist AEC/AGC control 2 */

#define REG_BD50MAX	0xa5	/* 50hz banding step limit */
#define REG_HAECC3	0xa6	/* Hist AEC/AGC control 3 */
#define REG_HAECC4	0xa7	/* Hist AEC/AGC control 4 */
#define REG_HAECC5	0xa8	/* Hist AEC/AGC control 5 */
#define REG_HAECC6	0xa9	/* Hist AEC/AGC control 6 */
#define REG_HAECC7	0xaa	/* Hist AEC/AGC control 7 */
#define REG_BD60MAX	0xab	/* 60hz banding step limit */

using std::string;
using namespace flair::core;

namespace flair { namespace sensor {

ArDrone2CamV::ArDrone2CamV(string name,uint8_t priority) : V4LCamera(name,2,320,240,cvimage::Type::Format::UYVY,priority) {
    //i2cport
    //we assume there is no other device on this bus
    i2cport=new Unix_I2cPort((Thread*)this,"camv-i2c","/dev/i2c-2");
    i2cport->SetSlave(0x42>>1);
    
    SetIsReady(true);
}

ArDrone2CamV::~ArDrone2CamV() {

}

void ArDrone2CamV::SetGain(float value) {
	if(ov7670_write(REG_GAIN, (int)(value*255) & 0xff)!=2) {
	    Thread::Err("error writting gain\n");
	}
}

void ArDrone2CamV::SetAutoGain(bool value) {
    unsigned char com8;

    if(ov7670_read(REG_COM8, &com8)!=1) {
        Thread::Err("error reading com8\n");
        return;
    }

    if (value) com8 |= COM8_AGC;
    else com8 &= ~COM8_AGC;

    if(ov7670_write(REG_COM8, com8)!=2) {
	    Thread::Err("error writting com8\n");
	}
}

void ArDrone2CamV::SetAutoExposure(bool value) {
    unsigned char com8;

    if(ov7670_read(REG_COM8, &com8)!=1) {
        Thread::Err("error reading com8\n");
        return;
    }

    if (value) com8 |= COM8_AEC;
    else com8 &= ~COM8_AEC;

    if(ov7670_write(REG_COM8, com8)!=2) {
	    Thread::Err("error writting com8\n");
	}
}

void ArDrone2CamV::SetExposure(float value) {
	unsigned char com1,aech, aechh;
	uint16_t value16=value*255.;//16 bit register but values after 255 does not change anything...

    if(ov7670_read(REG_COM1, &com1)!=1) {
        Thread::Err("error reading com1\n");
        return;
    }

    if(ov7670_read(REG_AECHH, &aechh)!=1) {
        Thread::Err("error reading aechh\n");
        return;
    }

	com1 = (com1 & 0xfc) | (value16 & 0x03);
	aech = (value16 >> 2) & 0xff;
	aechh = (aechh & 0xc0) | ((value16 >> 10) & 0x3f);

	if(ov7670_write(REG_COM1, com1)!=2) {
	    Thread::Err("error writting com1\n");
	}
	if(ov7670_write(REG_AECH, aech)!=2) {
	    Thread::Err("error writting aech\n");
	}
	if(ov7670_write(REG_AECHH, aechh)!=2) {
	    Thread::Err("error writting aechh\n");
	}
}

void ArDrone2CamV::SetBrightness(float value) {
    uint8_t v;
	v = ov7670_abs_to_sm(value*255.);

	if(ov7670_write(REG_BRIGHT, v)!=2) {
	    Thread::Err("error writting REG_BRIGHT\n");
	}
}

void ArDrone2CamV::SetSaturation(float value) {
	int matrix[CMATRIX_LEN];

	sat=value;

	ov7670_calc_cmatrix(matrix);
	ov7670_store_cmatrix(matrix);
}

void ArDrone2CamV::SetHue(float value) {
	int matrix[CMATRIX_LEN];

	hue = value*2*PI-PI;

	ov7670_calc_cmatrix(matrix);
	ov7670_store_cmatrix(matrix);
}

void ArDrone2CamV::SetContrast(float value) {
	ov7670_write(REG_CONTRAS, (unsigned char)(value*255));
}

unsigned char ArDrone2CamV::ov7670_abs_to_sm(uint8_t v) {
    if(v==0) v=1;//0 non gére sinon...
	if (v > 127) return v & 0x7f;
	return (128 - v) | 0x80;
}

int ArDrone2CamV::ov7670_store_cmatrix(int matrix[CMATRIX_LEN]) {
	int i, ret;
	unsigned char signbits = 0;

	/*
	 * Weird crap seems to exist in the upper part of
	 * the sign bits register, so let's preserve it.
	 */
	ret = ov7670_read(REG_CMATRIX_SIGN, &signbits);
	signbits &= 0xc0;

	for (i = 0; i < CMATRIX_LEN; i++) {
		unsigned char raw;

		if (matrix[i] < 0) {
			signbits |= (1 << i);
			if (matrix[i] < -255)
				raw = 0xff;
			else
				raw = (-1 * matrix[i]) & 0xff;
		}
		else {
			if (matrix[i] > 255)
				raw = 0xff;
			else
				raw = matrix[i] & 0xff;
		}
		ret += ov7670_write(REG_CMATRIX_BASE + i, raw);
	}
	ret += ov7670_write(REG_CMATRIX_SIGN, signbits);
	return ret;
}

void ArDrone2CamV::ov7670_calc_cmatrix(int matrix[CMATRIX_LEN]) {
	int i;
	/*
	 * Apply the current saturation setting first.
	 */
	for (i = 0; i < CMATRIX_LEN; i++)
		matrix[i] = (cmatrix[i]*(int)(sat*255)) >> 7;
	/*
	 * Then, if need be, rotate the hue value.
	 */
	if (hue != 0) {
		float sinth, costh;

		sinth = sinf(hue);
		costh = cosf(hue);

		matrix[0] = matrix[3]*sinth + matrix[0]*costh;
		matrix[1] = matrix[4]*sinth + matrix[1]*costh;
		matrix[2] = matrix[5]*sinth + matrix[2]*costh;
		matrix[3] = matrix[3]*costh - matrix[0]*sinth;
		matrix[4] = matrix[4]*costh - matrix[1]*sinth;
		matrix[5] = matrix[5]*costh - matrix[2]*sinth;
	}
}

int ArDrone2CamV::ov7670_write(uint8_t reg,uint8_t value) {
    uint8_t tx[2];

    tx[0]=reg;
    tx[1]=value;

    return i2cport->Write(tx, 2);
}

int ArDrone2CamV::ov7670_read(uint8_t reg,uint8_t *value) {
    uint8_t tx=reg;

    if(i2cport->Write(&tx,1)!=1) {
        Thread::Err("error writing register address\n");
    }
    if(i2cport->Read(value,1)!=1) {
        Thread::Err("error reading register\n");
    }

	return 1;
}

} // end namespace sensor
} // end namespace flair
