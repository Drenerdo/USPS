/*!
 *	@file		dotstar.c
 *	@author		BCA
 *	@version	1.0.0
 *	@date		12/2/16
 *	@brief		Source for Dotstar LED strip API
 *	@copyright	© Bay Computer Associates, Incorporated 2016
				All rights reserved
				This file contains CONFIDENTIAL material
 *	@remark		Matilda USPS Blue Box
 *	@Repository URL: $HeadURL: $
 *	Last changed by: $Author: $
 *	Last changed on: $Date: $
 *	Revision:		$Rev: $
**/

#include "dotstar.h"
#include <stdio.h>
#include <stdlib.h> // for malloc
#include <string.h> // for memset
#include <unistd.h> // for close
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>

static uint32_t *pixels = NULL;
static uint32_t numLEDs = 0;
static int fd;

static const uint8_t header_data[4] = {
    0x00, 0x00, 0x00, 0x00
};

static uint8_t * footer_data;

static struct spi_ioc_transfer xfer[3] = {
    { .tx_buf        = 0, // Header
      .rx_buf        = 0,
      .len           = 4,
      .delay_usecs   = 0,
      .bits_per_word = 8,
      .cs_change     = 0 },
    { .rx_buf        = 0, // Color payload
      .delay_usecs   = 0,
      .bits_per_word = 8,
      .cs_change     = 0 },
    { .tx_buf        = 0, // Footer
      .rx_buf        = 0,
      .len           = 4,
      .delay_usecs   = 0,
      .bits_per_word = 8,
      .cs_change     = 0 }
};

int dotstar_create(const char * device,
                   uint32_t frequency,
                   uint32_t num_leds)
{
    int ret = 0;
    
    if (num_leds == 0) {
        printf("Enter a value > 0 for the number of LEDs.\n");
        return -1;
    }

    fd = open(device, O_RDWR);
	if (fd < 0) {
		printf("Can't open device. Try sudo.\n");
        return -1;
    }

    uint8_t mode = 0;
	ret = ioctl(fd, SPI_IOC_WR_MODE, &mode);
	if (ret == -1) {
		printf("Can't set spi mode.\n");
        return -1;
    }

    uint8_t bits = 8;
	ret = ioctl(fd, SPI_IOC_WR_BITS_PER_WORD, &bits);
	if (ret == -1) {
		printf("Can't set bits per word.\n");
        return -1;
    }
    
	ret = ioctl(fd, SPI_IOC_WR_MAX_SPEED_HZ, &frequency);
	if (ret == -1) {
		printf("Can't set max speed HZ.\n");
        return -1;
    }
    
    numLEDs = num_leds;
    xfer[0].speed_hz = frequency;
    xfer[1].speed_hz = frequency;
    xfer[2].speed_hz = frequency;
    xfer[1].len = numLEDs * 4;
    xfer[2].len = (numLEDs + 15)/16;
        
    pixels = (uint32_t *) calloc(numLEDs, 4);

	// Set first byte of each 4-byte pixel to 0xFF, rest to 0x00 (off)
    for (uint32_t i = 0; i < numLEDs; i++)
    {
        pixels[i * 4] = 0xFF;
    }

    // Datasheet says 32*1 bits for footer, but testing shows we must use
    // at least (numLEDs + 1)/2 high values.
    footer_data = (uint8_t *) malloc(xfer[2].len);

    memset(footer_data, 0xFF, xfer[2].len);
    
	return 0;
}

void dotstar_destroy()
{
	if (fd) {
		close(fd);
		fd = -1;
	}
    
	if (pixels) {
        free(pixels);
    }

    if (footer_data) {
        free(footer_data);
    }
}

void dotstar_clear()
{
	uint32_t i;
	for (uint8_t * ptr = (uint8_t*)pixels, i = 0; i < numLEDs; i++, ptr += 4) {
        // Ignore brightness
		ptr[1] = 0x00;
        ptr[2] = 0x00;
        ptr[3] = 0x00;
	}
}

void dotstar_show()
{
    if (numLEDs == 0) {
        return;
    }
    
    xfer[0].tx_buf = (unsigned long)header_data;
    xfer[1].tx_buf = (unsigned long)pixels;
    xfer[2].tx_buf = (unsigned long)footer_data;

    int ret = ioctl(fd, SPI_IOC_MESSAGE(3), xfer);
	if (ret < 1) {
		printf("Can't send spi message.\n");
    }
}

void dotstar_set_pixel(uint16_t p, uint8_t r, uint8_t g, uint8_t b, uint8_t brightness)
{
	if (p < numLEDs) {
		uint8_t *ptr = (uint8_t*)&pixels[p];
		ptr[3] = r;
		ptr[2] = g;
		ptr[1] = b;
        if (brightness > PIXEL_MAX_BRIGHTNESS) {
            brightness = PIXEL_MAX_BRIGHTNESS;
        }
        ptr[0] = brightness | 0xE0;
	}
}

void dotstar_set_pixel_red(uint16_t p, uint8_t r)
{
	if (p < numLEDs) {
		uint8_t *ptr = (uint8_t*)&pixels[p];
		ptr[3] = r;
	}
}

void dotstar_set_pixel_green(uint16_t p, uint8_t g)
{
	if (p < numLEDs) {
		uint8_t *ptr = (uint8_t*)&pixels[p];
		ptr[2] = g;
	}
}

void dotstar_set_pixel_blue(uint16_t p, uint8_t b)
{
	if (p < numLEDs) {
		uint8_t *ptr = (uint8_t*)&pixels[p];
		ptr[1] = b;
	}
}

void dotstar_set_pixel_brightness(uint16_t p, uint8_t brightness)
{
	if (p < numLEDs) {
		uint8_t *ptr = (uint8_t*)&pixels[p];
        if (brightness > PIXEL_MAX_BRIGHTNESS) {
            brightness = PIXEL_MAX_BRIGHTNESS;
        }
        ptr[0] = brightness | 0xE0;
	}
}

uint8_t dotstar_get_pixel_red(uint16_t p)
{
    if (p < numLEDs) {
        uint8_t *ptr = (uint8_t*)&pixels[p];
	    return ptr[3];
	} else {
        return 0;
    }
}

uint8_t dotstar_get_pixel_green(uint16_t p)
{
    if (p < numLEDs) {
        uint8_t *ptr = (uint8_t*)&pixels[p];
	    return ptr[2];
	} else {
        return 0;
    }
}

uint8_t dotstar_get_pixel_blue(uint16_t p)
{
    if (p < numLEDs) {
        uint8_t *ptr = (uint8_t*)&pixels[p];
	    return ptr[1];
	} else {
        return 0;
    }
}

uint8_t dotstar_get_pixel_brightness(uint16_t p)
{
    if (p < numLEDs) {
        uint8_t *ptr = (uint8_t*)&pixels[p];
	    return ptr[0] & 0x0F;
	} else {
        return 0;
    }
}

void dotstar_set_strip(uint8_t r, uint8_t g, uint8_t b, uint8_t brightness)
{
    if (brightness > PIXEL_MAX_BRIGHTNESS) {
        brightness = PIXEL_MAX_BRIGHTNESS;
    }
    for (uint8_t * ptr = (uint8_t*)pixels, i = 0; i < numLEDs; i++, ptr += 4) {
        ptr[0] = brightness | 0xE0;
		ptr[1] = b;
        ptr[2] = g;
        ptr[3] = r;
	}
}

void dotstar_strip_push_pixel_front(uint8_t r, uint8_t g, uint8_t b, uint8_t brightness)
{
    uint32_t i;
	for (uint8_t * ptr = (uint8_t*)&pixels[numLEDs-2], i = 0; i < numLEDs-1; i++, ptr -= 4) {
        ptr[4] = ptr[0];
		ptr[5] = ptr[1];
        ptr[6] = ptr[2];
        ptr[7] = ptr[3];
	}
    dotstar_set_pixel(0, r, g, b, brightness);
}

void dotstar_strip_push_pixel_back(uint8_t r, uint8_t g, uint8_t b, uint8_t brightness)
{
    uint32_t i;
	for (uint8_t * ptr = (uint8_t*)pixels, i = 0; i < numLEDs-1; i++, ptr += 4) {
        ptr[0] = ptr[4];
		ptr[1] = ptr[5];
        ptr[2] = ptr[6];
        ptr[3] = ptr[7];
	}
    dotstar_set_pixel(numLEDs - 1, r, g, b, brightness);
}

void dotstar_strip_rotate_left()
{
    uint32_t i;
    uint8_t r, g, b, brightness;
    brightness = dotstar_get_pixel_brightness(0);
	b = dotstar_get_pixel_blue(0);
    g = dotstar_get_pixel_green(0);
    r = dotstar_get_pixel_red(0);
    
    dotstar_strip_push_pixel_back(r, g, b, brightness);
}

void dotstar_strip_rotate_right()
{
    uint32_t i;
    uint8_t r, g, b, brightness;
    brightness = dotstar_get_pixel_brightness(numLEDs - 1);
	b = dotstar_get_pixel_blue(numLEDs - 1);
    g = dotstar_get_pixel_green(numLEDs - 1);
    r = dotstar_get_pixel_red(numLEDs - 1);
    
    dotstar_strip_push_pixel_front(r, g, b, brightness);
}

#if defined(DOTSTAR_STANDALONE)
// compile with -std=gnu99
#include <time.h>

int main()
{
    int leds = 240;
    int center = 5;
    int test = 2;
    struct timespec tim;
    tim.tv_sec = 0;
    tim.tv_nsec = 1000 * 10000;

    dotstar_create("/dev/spidev1.0", 5000000, leds);
    
    // Initialization
    if (test == 2) {
        dotstar_set_strip(0, 0, 0, 0);
        for (int i = 0; i < center; i++)
        {
            dotstar_strip_push_pixel_front(255, 255, 0, 15);
        }
        dotstar_show();
    }
    
    while(1)
    {
        if (test == 1) {
            for (int i = 0; i < 256; i+=2)
            {
                dotstar_set_strip(0, 0, i, 15);
                dotstar_show();
                nanosleep(&tim, NULL);
            }
            for (int i = 255; i > 0; i-=2)
            {
                dotstar_set_strip(0, 0, i, 15);
                dotstar_show();
                nanosleep(&tim, NULL);
            }
        }
        else if (test == 2) {
        
            for (int i = 0; i < leds-center; i++)
            {
                dotstar_strip_rotate_right();
                dotstar_show();
                nanosleep(&tim, NULL);
            }
            for (int i = 0; i < leds-center; i++)
            {
                dotstar_strip_rotate_left();
                dotstar_show();
                nanosleep(&tim, NULL);
            }
        }
    }
    dotstar_destroy();
}
#endif

