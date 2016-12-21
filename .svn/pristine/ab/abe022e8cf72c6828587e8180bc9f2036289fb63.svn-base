//======================================================================
/*!
@file Backlight.c
Implements control of the backlight LEDs.

@copyright (c) 2016, Bay Computer Associates.<br>
All rights reserved.<br>
This file contains CONFIDENTIAL material.<br>
Bay Computer Associates and forbids duplication of
this material with out express written permission
from Bay Computer Associates.

@author John Heaney<br>
Bay Computer Associates, Inc.<br>
136 Frances Ave.<br>
Cranston, RI 02910<br>
Tel. (401) 461-1484

Repository URL:		$HeadURL:  $
Last changed by:	$Author: jheaney $
Last changed on:	$Date:  $
Revision:			$Rev:  $
*/

//API implementation includes.
#include <linux/types.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>
#include "Backlight.h"
#include "STREAM_macros.h"


//////////////////////////////////////////////////
#define SHIFT_REGISTER_LENGTH_BITS 224
#define SHIFT_REGISTER_LENGTH_BYTES (SHIFT_REGISTER_LENGTH_BITS / 8)

#define FIELD_TO_TX_BUFFER(type, value) \
	TYPE_ENDIAN_TO_STREAM_ITERATOR(type, BE_, tx, iterator, value)


//======================================================================
//! Private variables.
static BacklightBrightness gBrightness1 = BACKLIGHT_BRIGHTNESS_DEFAULT;
static BacklightBrightness gBrightness2 = BACKLIGHT_BRIGHTNESS_DEFAULT;
static BacklightGrayscale gGrayscale1 = BACKLIGHT_GRAYSCALE_DEFAULT;
static BacklightGrayscale gGrayscale2 = BACKLIGHT_GRAYSCALE_DEFAULT;

static const char *device = "/dev/spidev2.0";
static uint8_t mode;
static uint8_t bits = 8;
static uint32_t speed = 500000;
static uint16_t delay;

static uint8_t tx[SHIFT_REGISTER_LENGTH_BYTES];

static const char * backlightErrDescs[BacklightErrCOUNT] = 
{
#define BACKLIGHT_ERROR_(enumTag, description) description,
	BACKLIGHT_ERROR_LIST
#undef BACKLIGHT_ERROR_
};

//======================================================================
//! Private prototypes.
static void BacklightFillTX(void);

//======================================================================
/*!
@brief	Set the brightness levels and optionally update the LEDs.
@details
The brightness levels are 7 bits, which give 128 levels of brightness control.
This is combined with grayscale values, resulting in the actual brightness of
an LED. There are two LEDs, so the brightness values should be set simultaneously
for both panels. The values are cached so they can be accessed and provided as
input to this function if one should remain the same.

Since the brightness and grayscale are set by different functions, updating the
LEDs is optional.
@see BacklightUpdateLEDs

@return		BacklightNoErr or errors returned if LEDs are updated.
@param	led1	Brightness value for backlight LED 1.
@param	led2	Brightness value for backlight LED 2.
@param	update	If true then the LEDs will be updated immediately.

@author	John Heaney
@test	12/06/2016 Unit Test: UNTESTED
*/
BacklightErrEnum SetBrightness(BacklightBrightness led1, BacklightBrightness led2, bool update)
{
	BacklightErrEnum	result;

	result = BacklightNoErr;

	if (led1 > BACKLIGHT_BRIGHTNESS_MAX)
		gBrightness1 = BACKLIGHT_BRIGHTNESS_MAX;
	else
		gBrightness1 = led1;

	if (led2 > BACKLIGHT_BRIGHTNESS_MAX)
		gBrightness2 = BACKLIGHT_BRIGHTNESS_MAX;
	else
		gBrightness2 = led2;

	if (update)
	{
		result = BacklightUpdateLEDs();
	}
	return result;
}

//======================================================================
/*!
@brief	Set the grayscale levels and optionally update the LEDs.
@details
The grayscale levels are 16 bits, which give 65536 levels of control.
This is combined with brightness values, resulting in the actual brightness of
an LED. There are two LEDs, so the grayscale values should be set simultaneously
for both panels. The values are cached so they can be accessed and provided as
input to this function if one should remain the same.

Since the brightness and grayscale are set by different functions, updating the
LEDs is optional.
@see BacklightUpdateLEDs

@return		BacklightNoErr or errors returned if LEDs are updated.
@param	led1	Grayscale value for backlight LED 1.
@param	led2	Grayscale value for backlight LED 2.
@param	update	If true then the LEDs will be updated immediately.

@author	John Heaney
@test	12/06/2016 Unit Test: UNTESTED
*/
BacklightErrEnum SetGrayscale(BacklightGrayscale led1, BacklightGrayscale led2, bool update)
{
	BacklightErrEnum	result;

	result = BacklightNoErr;

	gGrayscale1 = led1;
	gGrayscale2 = led2;
	if (update)
	{
		result = BacklightUpdateLEDs();
	}
	return result;
}

//======================================================================
/*!
@brief	Return the brightness level for LED 1.

@return		Brightness level for LED 1.

@author	John Heaney
@test	12/06/2016 Unit Test: UNTESTED
*/
BacklightBrightness	GetBrightness1(void)
{
	return gBrightness1;
}

//======================================================================
/*!
@brief	Return the brightness level for LED 2.

@return		Brightness level for LED 2.

@author	John Heaney
@test	12/06/2016 Unit Test: UNTESTED
*/
BacklightBrightness	GetBrightness2(void)
{
	return gBrightness2;
}

//======================================================================
/*!
@brief	Return the grayscale level for LED 1.

@return		Grayscale level for LED 1.

@author	John Heaney
@test	12/06/2016 Unit Test: UNTESTED
*/
BacklightGrayscale	GetGrayscale1(void)
{
	return gGrayscale1;
}


//======================================================================
/*!
@brief	Return the grayscale level for LED 2.

@return		Grayscale level for LED 2.

@author	John Heaney
@test	12/06/2016 Unit Test: UNTESTED
*/
BacklightGrayscale	GetGrayscale2(void)
{
	return gGrayscale2;
}


//======================================================================
/*!
@brief	Fill the buffer to tranmit to via the spi bus.
The buffer begins with some control bits for the command. It is followed
by the master brightness values and then RGB values for each of four
color LEDs. In this implementation R0 and G0 are used for backlight LED
1 and 2, respectively.

@return		None.

@author	John Heaney
@test	12/06/2016 Unit Test: UNTESTED
*/
static void BacklightFillTX(void)
{
	uint32_t	command;
	int			iterator;

	//SPI transmits in both directions, so this buffer captures whatever comes back.
	// We don't care about it. It will be ignored.
	uint8_t rx[ARRAY_SIZE(tx)];

	//The first 32 bits include the command to write, flags and global brightness.
	SHIFT_BITS_FROM_RIGHT(command	,0x25			,6);	//Write command code.
	SHIFT_BITS_FROM_RIGHT(command	,0x01			,1);	//OUTTMG 
	SHIFT_BITS_FROM_RIGHT(command	,0x00			,1);	//EXTGCK
	SHIFT_BITS_FROM_RIGHT(command	,0x01			,1);	//TMGRST
	SHIFT_BITS_FROM_RIGHT(command	,0x01			,1);	//DSPRPT 
	SHIFT_BITS_FROM_RIGHT(command	,0x00			,1);	//BLANK 
	SHIFT_BITS_FROM_RIGHT(command	,0x00			,7);	//Blue brightness unused.
	SHIFT_BITS_FROM_RIGHT(command	,gBrightness2	,7);	//Green brightness
	SHIFT_BITS_FROM_RIGHT(command	,gBrightness1	,7);	//Red brightness

	//Build up the transmit buffer from the start.
	iterator = 0;
	FIELD_TO_TX_BUFFER(UINT32_, command);
	FIELD_TO_TX_BUFFER(UINT16_, 0); //OUTB3
	FIELD_TO_TX_BUFFER(UINT16_, 0); //OUTG3
	FIELD_TO_TX_BUFFER(UINT16_, 0); //OUTR3
	FIELD_TO_TX_BUFFER(UINT16_, 0); //OUTB2
	FIELD_TO_TX_BUFFER(UINT16_, 0); //OUTG2
	FIELD_TO_TX_BUFFER(UINT16_, 0); //OUTR2
	FIELD_TO_TX_BUFFER(UINT16_, 0); //OUTB1
	FIELD_TO_TX_BUFFER(UINT16_, 0); //OUTG1
	FIELD_TO_TX_BUFFER(UINT16_, 0); //OUTR1
	FIELD_TO_TX_BUFFER(UINT16_, 0); //OUTB0
	FIELD_TO_TX_BUFFER(UINT16_, gGrayscale2); //OUTG0
	FIELD_TO_TX_BUFFER(UINT16_, gGrayscale1); //OUTR0
}

//======================================================================
/*!
@brief	Update the backlight LEDs.
This function uses the stored brightness and grayscale values for both
LEDs and creates a spi command message. It sends the command via the
linux ioctl driver for the spi bus.

@return		BacklightNoErr | spi bus errors.

@author	John Heaney
@test	12/06/2016 Unit Test: UNTESTED
*/
BacklightErrEnum BacklightUpdateLEDs(void)
{
	int					ret;
	int					fd;
	BacklightErrEnum	result;

	result = BacklightNoErr;

	//SPI transmits in both directions, so this buffer captures whatever comes back.
	// We don't care about it. It will be ignored.
	uint8_t rx[ARRAY_SIZE(tx)];

	//Parameter ioctl block for the spi driver.
	struct spi_ioc_transfer tr = 
	{
		.tx_buf = (unsigned long)tx,
		.rx_buf = (unsigned long)rx,
		.len = ARRAY_SIZE(tx),
		.delay_usecs = delay,
		.speed_hz = speed,
		.bits_per_word = bits,
	};

	BacklightFillTX();

	fd = open(device, O_RDWR);
	if (fd < 0)
		return BacklightOpenErr;

	//Set spi mode.
	ret = ioctl(fd, SPI_IOC_WR_MODE, &mode);
	if (ret == -1)
	{
		result = BacklightSpiModeErr;
	}

	//Set bits per word.
	if (ret >= 0)
	{
		ret = ioctl(fd, SPI_IOC_WR_BITS_PER_WORD, &bits);
		if (ret == -1)
		{
			result = BacklightSpiBitsErr;
		}
	}

	//Set max speed hz.
	if (ret >= 0)
	{
		ret = ioctl(fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed);
		if (ret == -1)
		{
			result = BacklightSpiSpeedErr;
		}
	}

	if (ret >= 0)
	{
		ret = ioctl(fd, SPI_IOC_MESSAGE(1), &tr);
		if (ret < 1)
		{
			result = BacklightSpiSendErr;
		}
	}

	close(fd);
	return result;
}

//======================================================================
/*!
@brief	Return a string version of a backlight error.
A string pointer is returned that describes the backlight error.

@return		String that describes a backlight error.

@param err An enumeration that indicates a backlight error.

@author	John Heaney
@test	12/06/2016 Unit Test: UNTESTED
*/
const char* BacklightErrDesc(BacklightErrEnum err)
{
	return backlightErrDescs[err];
}
