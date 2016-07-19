#ifndef UTILITES_H
#define UTILITES_H

#include "i2c.h"

void Time_To_Buf(stDS1307Time *time, uint16_t *buf);
void Buf_To_Time(uint16_t *buf, stDS1307Time *time);
void Date_To_Buf(stDS1307Time *time, uint16_t *buf);
void Buf_To_Date(uint16_t *buf, stDS1307Time *time);
void Year_To_Buf(stDS1307Time *time, uint16_t *buf);
void Buf_To_Year(uint16_t *buf, stDS1307Time *time);

#endif
