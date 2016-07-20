#ifndef UTILITES_H
#define UTILITES_H

#include "i2c.h"

void Time_To_Buf(stDS1307Time *time, uint16_t *buf);
void Date_To_Buf(stDS1307Time *time, uint16_t *buf);
void Year_To_Buf(stDS1307Time *time, uint16_t *buf);

#endif
