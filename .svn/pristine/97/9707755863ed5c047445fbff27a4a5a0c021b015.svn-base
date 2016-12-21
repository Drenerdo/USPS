/*!
@file SegmentDisplay.h
This the API for the driver that controls the two segmented LEDs that 
comprise the text display.
The two LEDs are physically located side by side to provide an 8
character alphanumeric display. Each character also includes a period
or decimal point to its right. Each character is defined either by
one ASCII text character, which means its corresponding period is
off, or by an ASCII text character followed by a period, which means
it is immediately followed by a period. The maximum string length of
a text display is 16, which would be 8 characters with a decimal point
after each. For example, "A.B.C.D.1.2.3.4."

Note that an empty character can be provided with a space and a lone
period can be created by immediately following a space.
For example, "1/2= .5" uses six characters on the display, as does
"1/2=0.5", but "1/2=.5" uses only five with the decimal point being
part of the = character.

The display brightness can also be controlled. The two LEDs are 
controlled independently, so the first four characters may be set
to a different brightness than the second four.

The display can also be made to blink. Again, the two LEDs are controlled
independently, so the first four characters can be configured differently
than the second four. The option are to not blink or to blink at three
possible rates of .5, 1 or 2 Hz. NOTE that the blink rate is a hardware
function. Setting the two LEDs to the same rate will not keep them in 
sync. It is likely that there will be a slight difference that will 
become more apparent over many seconds. It is recommended that only half
of the display be set to a blinking rate using this feature. Otherwise,
the application can blink the entire display by alternating the text with
no text.

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

#ifndef _SEGMENT_DISPLAY_H
#define _SEGMENT_DISPLAY_H

#include <stdint.h>
#include <stdbool.h>

#include "ProjectConfig.h"

//======================================================================
//! Definitions.

//Define error codes and corresponding description strings as a
// list macro. The enum list is created immediately below. The
// string array is created in the implementation file.
//DISPLAY_ERROR_(enumTag			,description)
#define DISPLAY_ERROR_LIST \
DISPLAY_ERROR_(SegDispNoErr			,"No display error."		) \
DISPLAY_ERROR_(SegDispOpenErr		,"Can't open device."		) \
DISPLAY_ERROR_(SegDispAcquireI2CErr	,"Failed to acquire i2c."	) \
DISPLAY_ERROR_(SegDispWriteI2CErr	,"Failed to write to i2c."	) \
DISPLAY_ERROR_(SegDispTooLong		,"Too many characters."		) \
//Comment terminates list macro. Do not delete.

typedef enum
{
#define DISPLAY_ERROR_(enumTag, description) enumTag,
	DISPLAY_ERROR_LIST
#undef DISPLAY_ERROR_
	SegDispErrCOUNT
} SegDispErrEnum;

//There are two types defined for the bitmask values used to
// control the segments of an LED character. One is the C
// type and the other is a byte stream type used to fill the
// i2c byte buffer.
typedef uint16_t SegDispBitmask;
#define SEGDISP_BITMASK_STREAM_TYPE UINT16_

//Valid ranges for SegDispSetBrightness() parameter values.
#define SEGDISP_BRIGHTNESS_MIN 0
#define SEGDISP_BRIGHTNESS_MAX 15
#define SEGDISP_BRIGHTNESS_DEFAULT SEGDISP_BRIGHTNESS_MAX

//Parameter values for SegDispBlink().
//DISPLAY_BLINK_(enumTag			,displayEnable)
#define DISPLAY_BLINK_LIST \
DISPLAY_BLINK_(SegDispNO_BLINK		,1	)\
DISPLAY_BLINK_(SegDispBLINK_2HZ		,1	)\
DISPLAY_BLINK_(SegDispBLINK_1HZ		,1	)\
DISPLAY_BLINK_(SegDispBLINK_HALFHZ	,1	)\
DISPLAY_BLINK_(SegDispDISP_OFF		,0	)\
//Comment terminates list macro. Do not delete.

typedef enum
{
#define DISPLAY_BLINK_(enumTag, displayEnable) enumTag,
	DISPLAY_BLINK_LIST
#undef DISPLAY_BLINK_
	SegDispBlinkCOUNT
} SegDispBlinkEnum;

typedef uint8_t SegDispBrightness;
typedef uint8_t SegDispDisplayOffset;

//======================================================================
//! Public function prototypes.

//Set LED functions.
void SegDispClear(void);

SegDispErrEnum	SegDispInit();
SegDispErrEnum	SegDispAscii(SegDispDisplayOffset displayOffset, uint8_t ascii, bool dp);
SegDispErrEnum	SegDispSetBitmask(SegDispDisplayOffset displayOffset, SegDispBitmask bitmask);
SegDispErrEnum	SegDispText(SegDispDisplayOffset displayOffset, const char * buffer, SegDispDisplayOffset bufferSize);
SegDispErrEnum	SegDispUpdate(void);
SegDispErrEnum	SegDispSetBrightness(SegDispBrightness brightness1, SegDispBrightness brightness2);
SegDispErrEnum	SegDispBlink(SegDispBlinkEnum rate1, SegDispBlinkEnum rate2);

const char*		SegDispErrDesc(SegDispErrEnum err);

#endif
