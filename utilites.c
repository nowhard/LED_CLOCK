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

void Time_Brightness_To_Buf(stBrightness *brightness, uint16_t *buf)
{
	buf[0]=0x0500|(brightness->hour>>4);
	buf[1]=0x0400|(brightness->hour&0x0F);
	buf[2]=0x0300|(0x0A);//"-"
	buf[3]=0x0200|(brightness->minute>>4);
	buf[4]=0x0100|(brightness->minute&0x0F);		
}

void Value_Brightness_To_Buf(stBrightness *brightness, uint16_t *buf)
{
	buf[0]=0x0500|(0xF);
	buf[1]=0x0400|(0xF);
	buf[2]=0x0300|(0xF);
	buf[3]=0x0200|(0xF);
	buf[4]=0x0100|((brightness->brightness>>1)&0x0F);	
}

void Determine_Current_Brightness(stClock *clock)
{
	if((clock->brightnessDay.hour<MIN_NIGHT_TO_DAY_HOUR) | (clock->brightnessDay.hour>MAX_NIGHT_TO_DAY_HOUR))
	{
		clock->brightnessDay.hour=MAX_NIGHT_TO_DAY_HOUR;
	}

	if((clock->brightnessNight.hour<MIN_DAY_TO_NIGHT_HOUR) | (clock->brightnessNight.hour>MAX_DAY_TO_NIGHT_HOUR))
	{
		clock->brightnessNight.hour=MAX_DAY_TO_NIGHT_HOUR;
	}

	if((clock->DS1307Time.Hours==clock->brightnessDay.hour) && (clock->DS1307Time.Minutes==clock->brightnessDay.minute) && (clock->brightnessCurrent!=clock->brightnessDay.brightness))
	{
		clock->brightnessCurrent=clock->brightnessDay.brightness;	
	}

	if((clock->DS1307Time.Hours==clock->brightnessNight.hour) && (clock->DS1307Time.Minutes==clock->brightnessNight.minute) && (clock->brightnessCurrent!=clock->brightnessNight.brightness))
	{
		clock->brightnessCurrent=clock->brightnessNight.brightness;	
	}
}

uint8_t BCD_Increment(uint8_t bcd, uint8_t bcd_min, uint8_t bcd_max)
{	
	if((bcd&0xF)<9)
	{
		bcd+=0x01;
	}
	else
	{
		bcd+=0x10;
		bcd&=0xF0;
	}
	
	if(bcd<bcd_min)
	{
		bcd=bcd_min;			
	}

	if(bcd>bcd_max)
	{
		bcd=bcd_min;			
	}

	return bcd;
}

