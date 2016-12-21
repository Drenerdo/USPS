/*!
@file Backlight.h
API for controlling the backlight LED panels. 
There are two white LED panels that will be controlled via a 
Texas Instruments TLC59711, 12 channel, 16-bit per channel
PWM, RGB, LED Driver.
The controller groups the outputs into 4 set of RGB values, 
intended to be used for controlling four colored LEDs. Since
the LEDs being used are monochrome (white), only the RGB0
outputs are used. The R0 component controls the first LED
and the G0 component controls the second.
The controller allows for a master control for the brightness
of the RGB components of all four color LEDs, as well as the
component of each individual LED. The master brightness control
supports 128 levels. The individual LED components are each 16
bit and are referred to as grayscale. Since only two monochrome
LEDs are supported, the brightness and grayscale controls are
really redundant. The only effective difference between the two
is the resolution of the brightness vs. the grayscale values.
It probly makes sense to hold one at its maximum value and 
adjust the other.

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

Repository URL:		$HeadURL: $
Last changed by:	$Author: jheaney $
Last changed on:	$Date:  $
Revision:			$Rev:  $
*/

#ifndef _BACKLIGHT_H
#define _BACKLIGHT_H

#include <stdint.h>
#include <stdbool.h>

#include "ProjectConfig.h"

//BACKLIGHT_ERROR_(enumTag, description)
#define BACKLIGHT_ERROR_LIST \
BACKLIGHT_ERROR_(BacklightNoErr			,"No backlight error."		) \
BACKLIGHT_ERROR_(BacklightOpenErr		,"Can't open device."		) \
BACKLIGHT_ERROR_(BacklightSpiModeErr	,"Can't set spi mode."		) \
BACKLIGHT_ERROR_(BacklightSpiBitsErr	,"Can't set bits per word."	) \
BACKLIGHT_ERROR_(BacklightSpiSpeedErr	,"Can't set max speed hz."	) \
BACKLIGHT_ERROR_(BacklightSpiSendErr	,"Can't send spi message."	) \
//Comment terminates list macro. Do not delete.

typedef enum
{
#define BACKLIGHT_ERROR_(enumTag, description) enumTag,
	BACKLIGHT_ERROR_LIST
#undef BACKLIGHT_ERROR_
	BacklightErrCOUNT
} BacklightErrEnum;

#define BACKLIGHT_BRIGHTNESS_MIN 0
#define BACKLIGHT_BRIGHTNESS_MAX 0x7F
#define BACKLIGHT_GRAYSCALE_MIN 0
#define BACKLIGHT_GRAYSCALE_MAX 0xFFFF
#define BACKLIGHT_BRIGHTNESS_DEFAULT BACKLIGHT_BRIGHTNESS_MAX
#define BACKLIGHT_GRAYSCALE_DEFAULT BACKLIGHT_GRAYSCALE_MAX

typedef uint8_t BacklightBrightness;
typedef uint16_t BacklightGrayscale;

//Set LED functions.
BacklightErrEnum SetBrightness(
	BacklightBrightness led1, 
	BacklightBrightness led2, 
	bool update);
BacklightErrEnum SetGrayscale(
	BacklightGrayscale led1, 
	BacklightGrayscale led2, 
	bool update);

BacklightErrEnum BacklightUpdateLEDs(void);

//Access functions.
BacklightBrightness	GetBrightness1(void);
BacklightBrightness	GetBrightness2(void);
BacklightGrayscale	GetGrayscale1(void);
BacklightGrayscale	GetGrayscale2(void);

const char*			BacklightErrDesc(BacklightErrEnum err);

#endif
