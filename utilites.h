#ifndef UTILITES_H
#define UTILITES_H

#include "i2c.h"

void Time_To_Buf(stDS1307Time *time, uint16_t *buf);
void Date_To_Buf(stDS1307Time *time, uint16_t *buf);
void Year_To_Buf(stDS1307Time *time, uint16_t *buf);

uint8_t BCD_Increment(uint8_t bcd, uint8_t bcd_min, uint8_t bcd_max);

#endif
