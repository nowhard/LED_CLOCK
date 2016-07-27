#include "clock.h"
#include "led_display.h"
#include "keyboard.h"
#include "menu.h"
#include "utilites.h"

stClock clock;

void Clock_Init(void)
{
	Menu_Init();
	I2C_Init();
	I2C_DS1307Init(&clock.DS1307Time);
	KBD_Init();
	LED_SPI_Init();

	I2C_Read_Buf(ADDR_BRIGHTNESS_DAY, 	(uint8_t*)&clock.brightnessDay, sizeof(stBrightness));
	I2C_Read_Buf(ADDR_BRIGHTNESS_NIGHT, (uint8_t*)&clock.brightnessNight, sizeof(stBrightness));
	
	if((clock.brightnessDay.hour<MIN_NIGHT_TO_DAY_HOUR) | (clock.brightnessDay.hour>MAX_NIGHT_TO_DAY_HOUR))
	{
		clock.brightnessDay.hour=MAX_NIGHT_TO_DAY_HOUR;
	}

	if((clock.brightnessNight.hour<MIN_DAY_TO_NIGHT_HOUR) | (clock.brightnessNight.hour>MAX_DAY_TO_NIGHT_HOUR))
	{
		clock.brightnessNight.hour=MAX_DAY_TO_NIGHT_HOUR;
	}


	clock.display_buf[0]=0xA0F;
	clock.display_buf[1]=0x9FF;
	clock.display_buf[2]=0xB05;
	clock.display_buf[3]=0xC01;		
	clock.display_buf[4]=0xF00;
	
/*	clock.display_buf[5]=0x101;
	clock.display_buf[6]=0x202;
	clock.display_buf[7]=0x303;
	clock.display_buf[8]=0x404;
	clock.display_buf[9]=0x505;*/
}




#define DISP_COUNTER	1000

void Clock_Cycle(void)
{
	static uint16_t dispCounter=0;

	Menu_Key(KBD_ReadKey(), &clock);

	if(dispCounter==DISP_COUNTER)
	{
		dispCounter=0;
		Menu_Display(&clock);
		LED_Out(&clock, LED_BUF_LEN);
	}
	else
	{
		dispCounter++;
	}
}
