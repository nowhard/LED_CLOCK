#include "clock.h"
#include "led_display.h"
#include "keyboard.h"

stClock clock;
enClockState ClockState;

void Clock_Init(void)
{
	I2C_Init();
	I2C_DS1307Init(&clock.DS1307Time);
	KBD_Init();
	LED_SPI_Init();

	//clock.brightness=I2C_Read(SLA_ADDR,ADDR_BRIGHTNESS);
	clock.display_buf[0]=0xA0F;
	clock.display_buf[1]=0x9FF;
	clock.display_buf[2]=0xB05;
	clock.display_buf[3]=0xC01;		
	clock.display_buf[4]=0xF00;
	//clock.display_buf[3]=(0xA00|clock.brightness);
	
	clock.display_buf[5]=0x101;
	clock.display_buf[6]=0x202;
	clock.display_buf[7]=0x303;
	clock.display_buf[8]=0x404;
	clock.display_buf[9]=0x505;

	clock.display_mask	=0xFF;
}




#define DISP_COUNTER	1000

void Clock_Cycle(void)
{
	static uint16_t dispCounter=0;
	static uint8_t  keyCode=KEY_NONE;

	keyCode=KBD_ReadKey();

	Menu_Key(keyCode);


	if(dispCounter==DISP_COUNTER)
	{
		dispCounter=0;
		Menu_Display();
	}
	else
	{
		dispCounter++;
	}
}
