#ifndef UTILITES_H
#define UTILITES_H

#include "i2c.h"
#include "clock.h"

#define MIN_DAY_TO_NIGHT_HOUR	12
#define MAX_DAY_TO_NIGHT_HOUR	23


#define MIN_NIGHT_TO_DAY_HOUR	1
#define MAX_NIGHT_TO_DAY_HOUR	11

void Time_To_Buf(stDS1307Time *time, uint16_t *buf);
void Date_To_Buf(stDS1307Time *time, uint16_t *buf);
void Year_To_Buf(stDS1307Time *time, uint16_t *buf);
void Time_Brightness_To_Buf(stBrightness *brightness, uint16_t *buf);
void Value_Brightness_To_Buf(stBrightness *brightness, uint16_t *buf);

void Determine_Current_Brightness(stClock *clock);

uint8_t BCD_Increment(uint8_t bcd, uint8_t bcd_min, uint8_t bcd_max);

#endif
