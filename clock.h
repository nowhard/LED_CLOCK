#ifndef CLOCK_H
#define CLOCK_H

#include "i2c.h"

#define ADDR_BRIGHTNESS_DAY			0x8
#define ADDR_BRIGHTNESS_NIGHT		0x8
#define LED_MASK			0xFF
#define DISPLAY_BUF_LEN		16



typedef struct
{
	uint8_t timeDay[2];
	uint8_t brightnessDay;
	uint8_t timeNight[2];
	uint8_t brightnessNight;
} stBrightness;

typedef struct
{
	stDS1307Time 	DS1307Time;
	stBrightness	brightness;
	uint16_t 		display_buf[DISPLAY_BUF_LEN];
	uint8_t			display_mask;
} stClock;

void Clock_Init(void);


#endif
