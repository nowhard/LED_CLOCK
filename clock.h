#ifndef CLOCK_H
#define CLOCK_H

#include "i2c.h"


#define LED_MASK			0xFF
#define DISPLAY_BUF_LEN		16



typedef struct
{
	uint8_t hour;
	uint8_t minute;
	uint8_t brightness;
} stBrightness;

typedef struct
{
	stDS1307Time 	DS1307Time;
	stBrightness	brightnessDay;
	stBrightness	brightnessNight;
	uint8_t 		brightnessCurrent;
	uint16_t 		display_buf[DISPLAY_BUF_LEN];
	uint8_t			display_mask;
} stClock;

void Clock_Init(void);


#endif
