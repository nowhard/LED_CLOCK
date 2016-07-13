#ifndef CLOCK_H
#define CLOCK_H

#include "i2c.h"

#define ADDR_BRIGHTNESS		0x8
#define LED_MASK			0xFF
#define DISPLAY_BUF_LEN		16


typedef enum
{
	TUNE_NONE=0,
	TUNE_TIME,
	TUNE_DATE,
	TUNE_YEAR,
} enTune;

typedef enum
{
	STATE_DISPLAY_TIME=0,
	STATE_DISPLAY_DATE,
	STATE_DISPLAY_YEAR,
	STATE_TUNE_TIME_HOURS,
	STATE_TUNE_TIME_MINUTES,
	STATE_TUNE_DATE_MONTH,
	STATE_TUNE_DATE_DAY,
	STATE_TUNE_YEAR,
}
enClockState;

typedef struct
{
	stDS1307Time 	DS1307Time;
	uint8_t 		brightness; 
	uint16_t 		display_buf[DISPLAY_BUF_LEN];
	uint8_t			display_mask;
	enTune 			tune;
} stClock;

void Clock_Init(void);
void Clock_Time_To_Buf(stDS1307Time *time, uint16_t *buf);
void Clock_Buf_To_Time(uint16_t *buf, stDS1307Time *time);
void Clock_Date_To_Buf(stDS1307Time *time, uint16_t *buf);
void Clock_Buf_To_Date(uint16_t *buf, stDS1307Time *time);
void Clock_Year_To_Buf(stDS1307Time *time, uint16_t *buf);
void Clock_Buf_To_Year(uint16_t *buf, stDS1307Time *time);

#endif
