#include "utilites.h"

void Time_To_Buf(stDS1307Time *time, uint16_t *buf)
{
	buf[0]=0x0500|(time->Hours>>4);
	buf[1]=0x0400|(time->Hours&0x0F);
	buf[2]=0x0300|(0x0A);//"-"
	buf[3]=0x0200|(time->Minutes>>4);
	buf[4]=0x0100|(time->Minutes&0x0F);
}


void Buf_To_Time(uint16_t *buf, stDS1307Time *time)
{
	time->Hours		=((buf[0]&0x0F)<<4)|(buf[1]&0x0F);
	time->Minutes	=((buf[3]&0x0F)<<4)|(buf[4]&0x0F);
}

void Date_To_Buf(stDS1307Time *time, uint16_t *buf)
{

}


void Buf_To_Date(uint16_t *buf, stDS1307Time *time)
{

}

void Year_To_Buf(stDS1307Time *time, uint16_t *buf)
{

}


void Buf_To_Year(uint16_t *buf, stDS1307Time *time)
{

}
