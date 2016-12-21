//======================================================================
/*!
@file SegmentDisplay.c

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

//======================================================================
//! API implementation includes.
#include <fcntl.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <linux/types.h>
#include "SegmentDisplay.h"
#include "STREAM_macros.h"

//======================================================================
//! Private definitions.
//i2c addresses for left and right LED displays.
#define SEGDISP_I2CADDR0 0x70
#define SEGDISP_I2CADDR1 0x71

//Each display is 4 characters.
#define SEGDISP_NUM_CHARS 4

//Commands to the segment LED.
#define HT16K33_CMD_OSC_ON		0x21
#define HT16K33_CMD_BRIGHTNESS	0xE0
#define HT16K33_CMD_BLINK		0x80
#define HT16K33_CMD_WRITE		0x00

//The specific decimal point segment bit within SegDispBitmask.
#define SEGDISP_DP_BITPOS 14
#define SEGDISP_DP_BITMASK (1 << SEGDISP_DP_BITPOS)

//Use this macro to put character bitmasks into the display buffers. The offset is the 
// character position, not the byte offset. There are two display buffers because the
// display is divided between two i2c controllers; each displaying 4 characters. The
// buffNum parameter is 0 or 1.
#define SEGDISP_STREAM_ENDIAN LE_
#define SEGDISP_DISPLAY_OFFSET(offset) (1 + offset * sizeof(SegDispBitmask))
#define CHAR_TO_DISP_BUFFER(buffNum, c, offset) \
	TYPE_ENDIAN_TO_STREAM_OFFSET(SEGDISP_BITMASK_STREAM_TYPE, SEGDISP_STREAM_ENDIAN, \
								displayBuffer##buffNum, SEGDISP_DISPLAY_OFFSET(offset), c)
//Use this macro to get character bitmasks from the display buffers. The offset is the 
// character position, not the byte offset. The buffNum parameter is 0 or 1.
#define CHAR_FROM_DISP_BUFFER(buffNum, offset) \
	TYPE_ENDIAN_FROM_STREAM_OFFSET(SEGDISP_BITMASK_STREAM_TYPE, SEGDISP_STREAM_ENDIAN, \
								displayBuffer##buffNum, SEGDISP_DISPLAY_OFFSET(offset))

//======================================================================
//! Private variables.

//ioctl device driver.
static const char *device = "/dev/i2c-2";

//Create commands for each blink parameter value. The commands look like this:
// cccccrre, where c is the blink command code, r is the rate and e is an enable bit.
// If the enable bit is 0 then the display of off. If the enable bit is 1 and the rate
// is 0 then the display is on, but not blinking.
static const uint8_t segDispBlinkCmds[SegDispBlinkCOUNT] = 
{
#define DISPLAY_BLINK_(enumTag, displayEnable) \
						BIT_FIELD_VALUE(	displayEnable				,0	,1) |	\
						BIT_FIELD_VALUE(	(displayEnable * enumTag)	,1	,2) |	\
						HT16K33_CMD_BLINK,
	DISPLAY_BLINK_LIST
#undef DISPLAY_BLINK_
};

//Create an array of error descriptions indexed by the error enumeration.
static const char * segDispErrDescs[SegDispErrCOUNT] = 
{
#define DISPLAY_ERROR_(enumTag, description) description,
	DISPLAY_ERROR_LIST
#undef DISPLAY_ERROR_
};

//i2c byte buffers for sending to display. Note there are two buffers because there
// are two LEDs and there is one extra byte in each to hold the initial write command.
static uint8_t displayBuffer0[1 + (SEGDISP_NUM_CHARS * sizeof(SegDispBitmask))];
static uint8_t displayBuffer1[1 + (SEGDISP_NUM_CHARS * sizeof(SegDispBitmask))];

//This is a table of character segment bitmasks indexed by ASCII code.
static const SegDispBitmask alphafonttable[] = 
{
0b0000000000000001,
0b0000000000000010,
0b0000000000000100,
0b0000000000001000,
0b0000000000010000,
0b0000000000100000,
0b0000000001000000,
0b0000000010000000,
0b0000000100000000,
0b0000001000000000,
0b0000010000000000,
0b0000100000000000,
0b0001000000000000,
0b0010000000000000,
0b0100000000000000,
0b1000000000000000,
0b0000000000000000,
0b0000000000000000,
0b0000000000000000,
0b0000000000000000,
0b0000000000000000,
0b0000000000000000,
0b0000000000000000,
0b0000000000000000,
0b0001001011001001,
0b0001010111000000,
0b0001001011111001,
0b0000000011100011,
0b0000010100110000,
0b0001001011001000,
0b0011101000000000,
0b0001011100000000,
0b0000000000000000, //  
0b0000000000000110, // !
0b0000001000100000, // "
0b0001001011001110, // #
0b0001001011101101, // $
0b0000110000100100, // %
0b0010001101011101, // &
0b0000010000000000, // '
0b0010010000000000, // (
0b0000100100000000, // )
0b0011111111000000, // *
0b0001001011000000, // +
0b0000100000000000, // ,
0b0000000011000000, // -
0b0000000000000000, // .
0b0000110000000000, // /
0b0000110000111111, // 0
0b0000000000000110, // 1
0b0000000011011011, // 2
0b0000000010001111, // 3
0b0000000011100110, // 4
0b0010000001101001, // 5
0b0000000011111101, // 6
0b0000000000000111, // 7
0b0000000011111111, // 8
0b0000000011101111, // 9
0b0001001000000000, // :
0b0000101000000000, // ;
0b0010010000000000, // <
0b0000000011001000, // =
0b0000100100000000, // >
0b0001000010000011, // ?
0b0000001010111011, // @
0b0000000011110111, // A
0b0001001010001111, // B
0b0000000000111001, // C
0b0001001000001111, // D
0b0000000011111001, // E
0b0000000001110001, // F
0b0000000010111101, // G
0b0000000011110110, // H
0b0001001000000000, // I
0b0000000000011110, // J
0b0010010001110000, // K
0b0000000000111000, // L
0b0000010100110110, // M
0b0010000100110110, // N
0b0000000000111111, // O
0b0000000011110011, // P
0b0010000000111111, // Q
0b0010000011110011, // R
0b0000000011101101, // S
0b0001001000000001, // T
0b0000000000111110, // U
0b0000110000110000, // V
0b0010100000110110, // W
0b0010110100000000, // X
0b0001010100000000, // Y
0b0000110000001001, // Z
0b0000000000111001, // [
0b0010000100000000, // 
0b0000000000001111, // ]
0b0000110000000011, // ^
0b0000000000001000, // _
0b0000000100000000, // `
0b0001000001011000, // a
0b0010000001111000, // b
0b0000000011011000, // c
0b0000100010001110, // d
0b0000100001011000, // e
0b0000000001110001, // f
0b0000010010001110, // g
0b0001000001110000, // h
0b0001000000000000, // i
0b0000000000001110, // j
0b0011011000000000, // k
0b0000000000110000, // l
0b0001000011010100, // m
0b0001000001010000, // n
0b0000000011011100, // o
0b0000000101110000, // p
0b0000010010000110, // q
0b0000000001010000, // r
0b0010000010001000, // s
0b0000000001111000, // t
0b0000000000011100, // u
0b0010000000000100, // v
0b0010100000010100, // w
0b0010100011000000, // x
0b0010000000001100, // y
0b0000100001001000, // z
0b0000100101001001, // {
0b0001001000000000, // |
0b0010010010001001, // }
0b0000010100100000, // ~
0b0011111111111111,
};

//======================================================================
//! Private prototypes.
SegDispErrEnum SegDispWriteByte(uint8_t byte, bool led1, bool led2);
SegDispErrEnum SegDispWriteBuffer(uint8_t i2cAddr, uint8_t * buffer, SegDispDisplayOffset bufferSize);


//======================================================================
/*!
@brief	Set the brightness levels and optionally update the LEDs.
@details
There are two LEDs, so there are two brightness parameters to allow
each to be set independently, but simultaneously. The brightness levels
range from 0-15. Any larger value will be ignored, so it is possible to
set one brightness level without affecting the other LED.
NOTE that a level of 0 is not off. To turn off the display without 
erasing the text, use the SegDispBlink function.

@return		SegDispNoErr | SegDispWriteByte() errors.
@param	brightness1	Brightness level (0-15) for LED1.
@param	brightness2	Brightness level (0-15) for LED2.

@author	John Heaney
@test	12/07/2016 Unit Test: UNTESTED
*/
SegDispErrEnum	SegDispSetBrightness(
									 SegDispBrightness brightness1, 
									 SegDispBrightness brightness2)
{
	uint8_t			byte;
	SegDispErrEnum	err = SegDispNoErr;

	if (brightness1 <= SEGDISP_BRIGHTNESS_MAX)
	{
		err = SegDispWriteByte(HT16K33_CMD_BRIGHTNESS | brightness1, true, false);
	}
	if (SegDispNoErr == err)
	{
		if (brightness2 <= SEGDISP_BRIGHTNESS_MAX)
		{
			err = SegDispWriteByte(HT16K33_CMD_BRIGHTNESS | brightness2, false, true);
		}
	}
	return err;
}

//======================================================================
/*!
@brief	Provide a description string corresponding to an error code.

@return		Pointer to error description string.
@param	err	Error enumeration.

@author	John Heaney
@test	12/07/2016 Unit Test: UNTESTED
*/
const char* SegDispErrDesc(SegDispErrEnum err)
{
	return segDispErrDescs[err];
}

//======================================================================
/*!
@brief	Place a segment bitmask in the display buffer.
@details
There are two LEDs, so there are two display buffers. This fact is hidden
by this function in that the display offset input will map to the 
correct buffer. Each LED is 4 characters, so the range of display offsets 
is 0-7, spanning both buffers.

The bitmasks correspond to segments in each character, so they are not 
ASCII characters. Use SegDispAscii() to write an ASCII character. One of
the segments is a decimal point, so there is a bit in the bitmask for that.

This does not update the display on the LED. Use SegDispUpdate() for that.

@return		SegDispNoErr | SegDispTooLong.
@param	displayOffset	Offset spanning the entire display (0-7).
@param	bitmask			Bitmask for one character, including decimal point.

@author	John Heaney
@test	12/07/2016 Unit Test: UNTESTED
*/
SegDispErrEnum SegDispSetBitmask(
								 SegDispDisplayOffset displayOffset, 
								 SegDispBitmask bitmask)
{
	SegDispErrEnum			result = SegDispNoErr;
	SegDispDisplayOffset	bufferOffset;

	if (displayOffset < SEGDISP_NUM_CHARS)
	{
		bufferOffset = displayOffset;
		CHAR_TO_DISP_BUFFER(0, bitmask, bufferOffset);
	}
	else
	{
		bufferOffset = displayOffset - SEGDISP_NUM_CHARS;
		if (bufferOffset < SEGDISP_NUM_CHARS)
		{
			CHAR_TO_DISP_BUFFER(1, bitmask, bufferOffset);
		}
		else
		{
			result = SegDispTooLong;
		}
	}
	return result;
}

//======================================================================
/*!
@brief	Return a segment bitmask from the display buffer.
@details
See SegDispSetBitmask() for a description of the display buffers.

@return		SegDispNoErr | SegDispTooLong.
@param	displayOffset	Offset spanning the entire display (0-7).
@param	bitmask			Pointer to recieve bitmask for one character.

@author	John Heaney
@test	12/07/2016 Unit Test: UNTESTED
*/
SegDispErrEnum SegDispGetBitmask(
								 SegDispDisplayOffset displayOffset, 
								 SegDispBitmask * bitmask)
{
	SegDispErrEnum			result = SegDispNoErr;
	SegDispDisplayOffset	bufferOffset;

	if (displayOffset < SEGDISP_NUM_CHARS)
	{
		bufferOffset = displayOffset;
		*bitmask = CHAR_FROM_DISP_BUFFER(0, bufferOffset);
	}
	else
	{
		bufferOffset = displayOffset - SEGDISP_NUM_CHARS;
		if (bufferOffset < SEGDISP_NUM_CHARS)
		{
			*bitmask = CHAR_FROM_DISP_BUFFER(1, bufferOffset);
		}
		else
		{
			result = SegDispTooLong;
		}
	}
	return result;
}

//======================================================================
/*!
@brief	Write an ASCII character and decimal point to the display buffer.
@details
Convert an ASCII character to a segment bit mask. The decimal point is
a separate segment of the character, so it is controlled via a separate
parameter.

This does not update the display on the LED. Use SegDispUpdate() for that.

@return		SegDispNoErr | SegDispTooLong.
@param	displayOffset	Offset spanning the entire display (0-7).
@param	ascii			ASCII character.
@param	dp				Set to true to include the decimal point.

@author	John Heaney
@test	12/07/2016 Unit Test: UNTESTED
*/
SegDispErrEnum SegDispAscii(
							SegDispDisplayOffset displayOffset, 
							uint8_t ascii,  
							bool dp)
{
	SegDispBitmask	bitmask;

	if (ascii < ARRAY_SIZE(alphafonttable))
		bitmask = alphafonttable[ascii];
	else
		bitmask = 0;

	if (dp) bitmask |= SEGDISP_DP_BITMASK;

	return SegDispSetBitmask(displayOffset, bitmask);
}

//======================================================================
/*!
@brief	Clear the display buffer.
@details
This does not update the display on the LED. Use SegDispUpdate() for that.

@return		None.

@author	John Heaney
@test	12/07/2016 Unit Test: UNTESTED
*/
void SegDispClear(void)
{
	int	i;

	for (i = 0; i < sizeof(displayBuffer0); i++)
	{
		displayBuffer0[i] = 0;    
		displayBuffer1[i] = 0;    
	}
}

//======================================================================
/*!
@brief	Update the LEDs with the contents of the display buffer.
@details
The segment bitmasks in the display buffer are sent to the LEDs via
the i2c bus. Call this after setting the contents of the display buffer(s)
to show the display on the LEDs.

@return		SegDispNoErr | errors from SegDispWriteBuffer.

@author	John Heaney
@test	12/07/2016 Unit Test: UNTESTED
*/
SegDispErrEnum SegDispUpdate(void)
{
	SegDispErrEnum	err = SegDispNoErr;

	displayBuffer0[0] = HT16K33_CMD_WRITE;
	err = SegDispWriteBuffer(SEGDISP_I2CADDR0, displayBuffer0, sizeof(displayBuffer0));

	if (SegDispNoErr == err)
	{
		displayBuffer1[0] = HT16K33_CMD_WRITE;
		err = SegDispWriteBuffer(SEGDISP_I2CADDR1, displayBuffer1, sizeof(displayBuffer1));
	}

	return err;
}

//======================================================================
/*!
@brief	Initialize the display, setting it to a known condition.
@details
Turn on the oscillators. Clear the display and update it.
Set the display to on and not blinking. Set the brightness
to maximum. Nothing will be displayed, so any initial configuration
can be accomplished after this call.

@return		SegDispNoErr | errors from SegDispWriteBuffer.

@author	John Heaney
@test	12/07/2016 Unit Test: UNTESTED
*/
SegDispErrEnum SegDispInit()
{
	SegDispErrEnum	err = SegDispNoErr;

	SegDispClear();
	err = SegDispUpdate();
	if (SegDispNoErr != err)
		return err;

	err = SegDispWriteByte(HT16K33_CMD_OSC_ON, true, true);
	if (SegDispNoErr != err)
		return err;

	err = SegDispBlink(SegDispNO_BLINK, SegDispNO_BLINK);
	if (SegDispNoErr != err)
		return err;

	err = SegDispSetBrightness(SEGDISP_BRIGHTNESS_MAX, SEGDISP_BRIGHTNESS_MAX);
	if (SegDispNoErr != err)
		return err;

}

//======================================================================
/*!
@brief	Configure the state of the display with respect to blinking.
@details
This function controls the hardware level blinking, but also controls
whether the display is on. Each LED is controlled separately, so each
half of the display can be configured independently and simultaneously.
There are five settings (0-4), as indicated in the following table.
		PARAMETER			|	DISPLAY	|	RATE
		SegDispNO_BLINK		|	on		|	Not blinking
		SegDispBLINK_2HZ	|	on		|	2 Hz
		SegDispBLINK_1HZ	|	on		|	1 Hz
		SegDispBLINK_HALFHZ	|	on		|	.5 Hz
		SegDispDISP_OFF		|	off		|	N/A

If the parameter is greater than these values then it will be ignored, so
passing a large value for one LED allows the caller to set only the other.

NOTE that the blinking is a hardware function and each LED (4 characters)
blink independently. If both LEDs are set to the same rate, it is
likely that they will become out of sync within seconds, so it is
recommended that only one LED be set to blinking at a time. To blink
the entire display, call this function repeatedly, alternating between
SegDispNO_BLINK and SegDispDISP_OFF for both LEDs. Turning the display
on and off this way does not affect the text being displayed or the
brightness of the LEDs.

@return		SegDispNoErr | errors from SegDispWriteBuffer.
@param	rate1 Blink parameter for LED1.
@param	rate2 Blink parameter for LED2.

@author	John Heaney
@test	12/07/2016 Unit Test: UNTESTED
*/
SegDispErrEnum SegDispBlink(
							SegDispBlinkEnum rate1, 
							SegDispBlinkEnum rate2)
{
	SegDispErrEnum	err = SegDispNoErr;
	uint8_t			rate;

	rate = rate1;
	if (rate < SegDispBlinkCOUNT)
	{
		err = SegDispWriteByte(segDispBlinkCmds[rate], true, false);
	}
	if (SegDispNoErr == err)
	{
		rate = rate2;
		if (rate < SegDispBlinkCOUNT)
		{
			err = SegDispWriteByte(segDispBlinkCmds[rate], false, true);
		}
	}

	return err;
}

//======================================================================
/*!
@brief	Write the contents of a byte buffer over i2c bus.
@details
There are two i2c busses; one per LED. An ID is passed into this function
to address the specific device. The linux ioctl device control api is
used to communicate.

There are a number of possible errors associated with using ioctl. Each
error has an associated text description, which is available via the 
SegDispErrDesc() function.

@return		SegDispNoErr | errors related to ioctl.
@param	i2cAddr Address of the target i2c bus.
@param	buffer Pointer to byte buffer to transmit.
@param	bufferSize Number of bytes in buffer to send.

@author	John Heaney
@test	12/07/2016 Unit Test: UNTESTED
*/
SegDispErrEnum SegDispWriteBuffer(
								  uint8_t i2cAddr, 
								  uint8_t * buffer, 
								  SegDispDisplayOffset bufferSize)
{
	int				fd;
	int				ret;
	SegDispErrEnum	result;

	result = SegDispNoErr;

	fd = open(device, O_RDWR);
	if (fd < 0)
	{
		result = SegDispOpenErr;
	}
	else
	{
		//Acquire i2c bus.
		ret = ioctl(fd, I2C_SLAVE, i2cAddr);
		if (ret == -1)
		{
			result = SegDispAcquireI2CErr;
		}
		else
		{
			//Send the bytes.
			ret = write(fd, buffer, bufferSize);
			if (ret == -1)
			{
				result = SegDispWriteI2CErr;
			}
		}

		close(fd);
	}
	return result;
}

//======================================================================
/*!
@brief	Write one byte over i2c bus.
@details
There are two i2c busses; one per LED. This function assumes that the 
caller will want to send the same byte to one or both of them. Rather
than pass in the desired i2c address, there is a boolean for each 
i2c bus that determines if the byte should be written to the
corresponding bus.

@return		SegDispNoErr | errors from SegDispWriteBuffer().
@param	byte Byte to send (typically, a command).
@param	led1 Set to true to send command to LED1.
@param	led2 Set to true to send command to LED2.

@author	John Heaney
@test	12/07/2016 Unit Test: UNTESTED
*/
SegDispErrEnum SegDispWriteByte(
								uint8_t byte, 
								bool led1, 
								bool led2)
{
	SegDispErrEnum	err = SegDispNoErr;

	if (led1)
	{
		err = SegDispWriteBuffer(SEGDISP_I2CADDR0, &byte, 1);
	}

	if ((SegDispNoErr == err) && led2)
	{
		err = SegDispWriteBuffer(SEGDISP_I2CADDR1, &byte, 1);
	}
	return err;
}

//======================================================================
/*!
@brief	Write text into the display buffer.
@details
There are two LEDs and two display buffers. This function hides that by
having the offset span the two buffers.
Since each character of an LED includes a separate segment for a decimal
point to its right, the source string is really either one or two 
ASCII characters per LED character. If a source character is not a decimal
point then it occupies one LED character. If it is a decimal point then
it occupies the same LED character as the prior ASCII character in the 
source string.

The display is not updated. Follow this with a call to SegDispUpdate().

NOTE that two decimal points in a row will only produce one decimal 
point because they will both be associated with the same prior source
character. To print a consecutive decimal point, include a space to
provide a placeholder LED character.

@return		SegDispNoErr | errors from SegDispWriteBuffer().
@param	displayOffset Offset into display buffer (0-7).
@param	buffer Buffer with ASCII characters to write.
@param	bufferSize Number of characters in buffer.

@author	John Heaney
@test	12/07/2016 Unit Test: UNTESTED
*/
SegDispErrEnum	SegDispText(
							SegDispDisplayOffset displayOffset, 
							const char * buffer, 
							SegDispDisplayOffset bufferSize)
{
	int				i;
	char			byte;
	SegDispErrEnum	err = SegDispNoErr;
	SegDispBitmask	mask;

	//Process each ASCII character from the source buffer.
	for (i = 0; i < bufferSize; i++)
	{
		byte = buffer[i];

		//Treating the source as a C string, so terminate on NULL.
		if (0 == byte)
			break;

		if ('.' == byte)
		{
			//The byte is a period, so it must be associated with a prior character.
			// There is a special case where the first character is a decimal point,
			// in which case we have to write it to the first location.
			if ((i > 0) && (displayOffset > 0))
				displayOffset--;

			err = SegDispGetBitmask(displayOffset, &mask);
			if (SegDispNoErr == err)
			{
				//Just turn on the decimal point bit of the mask that was just
				// read and write it back to the same location.
				err = SegDispSetBitmask(displayOffset, mask | SEGDISP_DP_BITMASK);
			}
		}
		else
		{
			//Write the character into the display buffer with no period.
			err = SegDispAscii(displayOffset, byte,  false);
		}
		if (SegDispNoErr != err)
			break;

		//Update the display offset every time. When the source character is 
		// a decimal point then the offset was decremented, so incrementing
		// is always the right thing to do.
		displayOffset++;
	}
	return err;
}
