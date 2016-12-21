/*!
 *	@file 		usps_bb_api.h
 *	@author		BCA
 *	@version	1.0.0
 *	@date		12/2/16
 *	@brief		Header for USPS Blue Box API
 *	@copyright	© Bay Computer Associates, Incorporated 2016
				All rights reserved
				This file contains CONFIDENTIAL material
 *	@remark		Matilda USPS Blue Box
 *	@Repository URL: $HeadURL: $
 *	Last changed by: $Author: $
 *	Last changed on: $Date: $
 *	Revision:		$Rev: $
**/

#pragma once

#include <stdint.h>

// LED strip
void usps_bb_led_initialize(void);
void usps_bb_led_done(void);
void usps_bb_led_clear(void);
void usps_bb_led_show(void);
void usps_bb_led_set_pixel(uint16_t pixel,uint8_t r,uint8_t g,uint8_t b,uint8_t brightness);
void usps_bb_led_set_pixel_red(uint16_t pixel,uint8_t r);
void usps_bb_led_set_pixel_green(uint16_t pixel,uint8_t g);
void usps_bb_led_set_pixel_blue(uint16_t pixel,uint8_t b);
void usps_bb_led_set_pixel_brightness(uint16_t pixel,uint8_t brightness);
uint8_t usps_bb_led_get_pixel_red(uint16_t pixel);
uint8_t usps_bb_led_get_pixel_green(uint16_t pixel);
uint8_t usps_bb_led_get_pixel_blue(uint16_t pixel);
uint8_t usps_bb_led_get_pixel_brightness(uint16_t pixel);
void usps_bb_led_set(uint8_t r,uint8_t g,uint8_t b,uint8_t brightness);
void usps_bb_led_push_pixel_front(uint8_t r,uint8_t g,uint8_t b,uint8_t brightness);
void usps_bb_led_push_pixel_back(uint8_t r,uint8_t g,uint8_t b,uint8_t brightness);
void usps_bb_led_rotate_left(void);
void usps_bb_led_rotate_right(void);

// Backlight
void usps_bb_backlight_set_brightness(uint8_t brightness);
void usps_bb_backlight_set_grayscale(uint16_t grayscale);
void usps_bb_backlight_show(void);
uint8_t usps_bb_backlight_get_brightness(void);
uint16_t usps_bb_backlight_get_grayscale(void);

// Display
void usps_bb_display_initialize(void);
void usps_bb_display_text(const char *text);
void usps_bb_display_brightness(uint8_t brightness1, uint8_t brightness2);
void usps_bb_display_blink(uint8_t rate1, uint8_t rate2);

// Scale
uint16_t usps_bb_scale(void);

