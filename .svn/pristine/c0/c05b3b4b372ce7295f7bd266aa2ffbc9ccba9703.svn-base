/*!
 *	@file		usps_bb_api.c
 *	@author		BCA
 *	@version	1.0.0
 *	@date		12/2/16
 *	@brief		Source for USPS Blue Box API
 *	@copyright	© Bay Computer Associates, Incorporated 2016
				All rights reserved
				This file contains CONFIDENTIAL material
 *	@remark		Matilda USPS Blue Box
 *	@Repository URL: $HeadURL: $
 *	Last changed by: $Author: $
 *	Last changed on: $Date: $
 *	Revision:		$Rev: $
**/

#include "usps_bb_api.h"
#include "dotstar.h"
#include "Backlight.h"
#include "SegmentDisplay.h"

#include <stdio.h>
#include <string.h>

static const char *cDevice="/dev/spidev1.0";
static const uint16_t cNumLEDs=240;
static const uint16_t cCenter=5;

/*!
 *	@brief		led initialize
 *	@details
 *	@retval		none
 *	@test
**/

void usps_bb_led_initialize()
{
	dotstar_create(cDevice,8000000,cNumLEDs);
}

/*!
 *	@brief		led done 
 *	@details
 *	@retval		none
 *	@test
**/

void usps_bb_led_done()
{
	dotstar_destroy();
}

/*!
 *	@brief		led clear 
 *	@details
 *	@retval		none
 *	@test
**/

void usps_bb_led_clear()
{
	dotstar_clear();
}

/*!
 *	@brief		led show 
 *	@details
 *	@retval		none
 *	@test
**/

void usps_bb_led_show()
{
	dotstar_show();
}

/*!
 *	@brief		set led pixel
 *	@details
 *	@param		[in] pixel: uint16_t pixel number
 *	@param		[in] r: uint8_t red
 *	@param		[in] g: uint8_t green
 *	@param		[in] b: uint8_t blue
 *	@param		[in] brightness: uint8_t brightness maximum 15
 *	@retval		none
 *	@test
**/

void usps_bb_led_set_pixel(
	uint16_t pixel,
	uint8_t r,
	uint8_t g,
	uint8_t b,
	uint8_t brightness)
{
	dotstar_set_pixel(pixel,r,g,b,brightness);
}

/*!
 *	@brief		set led pixel red
 *	@details
 *	@param		[in] pixel: uint16_t pixel number
 *	@param		[in] r: uint8_t red
 *	@retval		none
 *	@test
**/

void usps_bb_led_set_pixel_red(
	uint16_t pixel,
	uint8_t r)
{
	dotstar_set_pixel_red(pixel,r);
}

/*!
 *	@brief		set led pixel green
 *	@details
 *	@param		[in] pixel: uint16_t pixel number
 *	@param		[in] g: uint8_t green
 *	@retval		none
 *	@test
**/

void usps_bb_led_set_pixel_green(
	uint16_t pixel,
	uint8_t g)
{
	dotstar_set_pixel_green(pixel,g);
}

/*!
 *	@brief		set led pixel blue
 *	@details
 *	@param		[in] pixel: uint16_t pixel number
 *	@param		[in] b: uint8_t blue
 *	@retval		none
 *	@test
**/

void usps_bb_led_set_pixel_blue(
	uint16_t pixel,
	uint8_t b)
{
	dotstar_set_pixel_blue(pixel,b);
}

/*!
 *	@brief		set led pixel brightness
 *	@details
 *	@param		[in] pixel: uint16_t pixel number
 *	@param		[in] brightness: uint8_t brightness maximum 15
 *	@retval		none
 *	@test
**/

void usps_bb_led_set_pixel_brightness(
	uint16_t pixel,
	uint8_t brightness)
{
	dotstar_set_pixel_brightness(pixel,brightness);
}

/*!
 *	@brief		get led pixel red
 *	@details
 *	@param		[in] pixel: uint16_t pixel number
 *	@retval		r: uint8_t
 *	@test
**/

uint8_t usps_bb_led_get_pixel_red(
	uint16_t pixel)
{
	return dotstar_get_pixel_red(pixel);
}

/*!
 *	@brief		get led pixel green 
 *	@details
 *	@param		[in] pixel: uint16_t pixel number
 *	@retval		g: uint8_t
 *	@test
**/

uint8_t usps_bb_led_get_pixel_green(
	uint16_t pixel)
{
	return dotstar_get_pixel_green(pixel);
}


/*!
 *	@brief		get led pixel blue
 *	@details
 *	@param		[in] pixel: uint16_t pixel number
 *	@retval		b: uint8_t
 *	@test
**/

uint8_t usps_bb_led_get_pixel_blue(
	uint16_t pixel)
{
	return dotstar_get_pixel_blue(pixel);
}


/*!
 *	@brief		get led pixel brightness
 *	@details
 *	@param		[in] pixel: uint16_t pixel number
 *	@retval		brightness: uint8_t
 *	@test
**/

uint8_t usps_bb_led_get_pixel_brightness(
	uint16_t pixel)
{
	return dotstar_get_pixel_brightness(pixel);
}

/*!
 *	@brief		set led strip
 *	@details
 *	@param		[in] r: uint8_t red
 *	@param		[in] g: uint8_t green
 *	@param		[in] b: uint8_t blue
 *	@param		[in] brightness: uint8_t brightness maximum 15
 *	@retval		none
 *	@test
**/

void usps_bb_led_set(
	uint8_t r,
	uint8_t g,
	uint8_t b,
	uint8_t brightness)
{
	dotstar_set_strip(r,g,b,brightness);
}

/*!
 *	@brief		push led pixel to front
 *	@details
 *	@param		[in] r: uint8_t red
 *	@param		[in] g: uint8_t green
 *	@param		[in] b: uint8_t blue
 *	@param		[in] brightness: uint8_t brightness maximum 15
 *	@retval		none
 *	@test
**/

void usps_bb_led_push_pixel_front(
	uint8_t r,
	uint8_t g,
	uint8_t b,
	uint8_t brightness)
{
	dotstar_strip_push_pixel_front(r,g,b,brightness);
}

/*!
 *	@brief		push led pixel to back 
 *	@details
 *	@param		[in] r: uint8_t red
 *	@param		[in] g: uint8_t green
 *	@param		[in] b: uint8_t blue
 *	@param		[in] brightness: uint8_t brightness maximum 15
 *	@retval		none
 *	@test
**/

void usps_bb_led_push_pixel_back(
	uint8_t r,
	uint8_t g,
	uint8_t b,
	uint8_t brightness)
{
	dotstar_strip_push_pixel_back(r,g,b,brightness);
}

/*!
 *	@brief		rotate left
 *	@details
 *	@retval		none
 *	@test
**/

void usps_bb_led_rotate_left()
{
	dotstar_strip_rotate_left();
}

/*!
 *	@brief		rotate right
 *	@details
 *	@retval		none
 *	@test
**/

void usps_bb_led_rotate_right()
{
	dotstar_strip_rotate_right();
}

/*!
 *	@brief		set backlight brightness
 *	@details
 *	@param		[in] brightness: uint8_t brightness
 *	@retval		none
 *	@test
**/

void usps_bb_backlight_set_brightness(
	uint8_t brightness)
{
	SetBrightness(brightness,BACKLIGHT_BRIGHTNESS_MIN,false);
}

/*!
 *	@brief		set backlight grayscale
 *	@details
 *	@param		[in] grayscale: uint16_t grayscale
 *	@retval		none
 *	@test
**/

void usps_bb_backlight_set_grayscale(
	uint16_t grayscale)
{
	SetGrayscale(grayscale,BACKLIGHT_GRAYSCALE_MIN,false);
}

/*!
 *	@brief		show backlight
 *	@details
 *	@retval		none
 *	@test
**/

void usps_bb_backlight_show()
{
	BacklightUpdateLEDs();
}

/*!
 *	@brief		get backlight brightness
 *	@details
 *	@retval		uint8_t	
 *	@test
**/

uint8_t usps_bb_backlight_get_brightness()
{
	return GetBrightness1();
}

/*!
 *	@brief		get backlight grayscale
 *	@details
 *	@retval		uint16_t	
 *	@test
**/

uint16_t usps_bb_backlight_get_grayscale()
{
	return GetGrayscale1();
}

/*!
 *	@brief		initialize the text display
 *	@details	Set the two text LEDs to a known configuration.
 The display buffer is cleared. The brightness is set to maximum.
 The blink rate is set to 0 (not blinking).
 *	@retval		none	
 *	@test
**/
void usps_bb_display_initialize()
{
	SegDispInit();
}

/*!
 *	@brief		set display text
 *	@details	There are two 4 character alphanumeric segmented
	LEDs that are arranged side by side. Each character includes
	a decimal point to its right. The display text is set with
	a character string that is left justified on the display.
	The text may be comprised of up to 8 ASCII characters or up
	to 8 character pairs, where the second character is a period
	or decimal point('.'). Note that the optional decimal point
	must follow a character. Use a space if the decimal point
	is displayed alone.
 *	@param		[in] text: char *text
 *	@retval		none
 *	@test
**/
void usps_bb_display_text(
	const char *text)
{
	if (SegDispNoErr == SegDispText(0, text, strlen(text)))
		SegDispUpdate();
}

/*!
 *	@brief		set display brightness
 *	@details	There are two 4 character alphanumeric segmented
	LEDs that are arranged side by side. Each can have its 
	brightness adjusted independently. The brightness values are
	in the range of 0-15. Note that 0 is not off. To clear an LED,
	set its text to spaces.
 *	@param		[in] brightness1: 0-15
 *	@param		[in] brightness2: 0-15
 *	@retval		none
 *	@test
**/
void usps_bb_display_brightness(
	uint8_t brightness1, uint8_t brightness2)
{
	SegDispSetBrightness(brightness1, brightness2);
}

/*!
 *	@brief		set display blink rate
 *	@details	There are two 4 character alphanumeric segmented
	LEDs that are arranged side by side. Each can be independently
	set to blink or can be used to turn off the display. There are 
	five settings (0-4), as indicated in the following table.
		PARAMETER	|	DISPLAY	|	RATE
		0			|	on		|	Not blinking
		1			|	on		|	2 Hz
		2			|	on		|	1 Hz
		3			|	on		|	.5 Hz
		4			|	off		|	N/A
	NOTE that the blinking is a hardware function and each LED
	(4 characters) blink independently. If both LEDs are set to 
	the same rate, it is likely that they will become out of sync
	within seconds, so it is recommended that only one LED be set
	to blinking at a time. To blink the entire display, call this
	function repeatedly, alternating between 0 and 4 for both LEDs.
	Turning the display on and off this way does not affect the
	text being displayed or the brightness of the LEDs.
 *	@param		[in] rate1: 0-4
 *	@param		[in] rate2: 0-4
 *	@retval		none
 *	@test
**/
void usps_bb_display_blink(
	uint8_t rate1, uint8_t rate2)
{
	SegDispBlink(rate1, rate2);
}

/*!
 *	@brief		get scale weight
 *	@details	ounces
 *	@retval		uint16_t	
 *	@test
**/

uint16_t usps_bb_backlight_scale()
{
	return 0;
}


