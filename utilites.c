#include "utilites.h"

void Time_To_Buf(stDS1307Time *time, uint16_t *buf)
{
	buf[0]=0x0500|(time->Hours>>4);
	buf[1]=0x0400|(time->Hours&0x0F);
	buf[2]=0x0300|(0x0A);//"-"
	buf[3]=0x0200|(time->Minutes>>4);
	buf[4]=0x0100|(time->Minutes&0x0F);
}

void Date_To_Buf(stDS1307Time *time, uint16_t *buf)
{
	buf[0]=0x0500|(time->Date>>4);
	buf[1]=0x0400|(time->Date&0x0F);
	buf[2]=0x0300|(0xFF);//"."
	buf[3]=0x0200|(time->Month>>4);
	buf[4]=0x0100|(time->Month&0x0F);
}

void Year_To_Buf(stDS1307Time *time, uint16_t *buf)
{
	buf[0]=0x0500|(0xF);
	buf[1]=0x0400|(2);
	buf[2]=0x0300|(0);
	buf[3]=0x0200|(time->Year>>4);
	buf[4]=0x0100|(time->Year&0x0F);
}

