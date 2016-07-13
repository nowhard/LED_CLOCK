#include "clock.h"
#include "led_display.h"

stClock clock;
enClockState ClockState;

void Clock_Init(void)
{
	I2C_Init();
	I2C_DS1307Init(&clock.DS1307Time);
	//KBD_init();
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


void Clock_Time_To_Buf(stDS1307Time *time, uint16_t *buf)
{
	buf[0]=0x0500|(time->Hours>>4);
	buf[1]=0x0400|(time->Hours&0x0F);
	buf[2]=0x0300|(0x0A);//"-"
	buf[3]=0x0200|(time->Minutes>>4);
	buf[4]=0x0100|(time->Minutes&0x0F);
}


void Clock_Buf_To_Time(uint16_t *buf, stDS1307Time *time)
{
	time->Hours		=((buf[0]&0x0F)<<4)|(buf[1]&0x0F);
	time->Minutes	=((buf[3]&0x0F)<<4)|(buf[4]&0x0F);
}

void Clock_Date_To_Buf(stDS1307Time *time, uint16_t *buf)
{

}


void Clock_Buf_To_Date(uint16_t *buf, stDS1307Time *time)
{

}

void Clock_Year_To_Buf(stDS1307Time *time, uint16_t *buf)
{

}


void Clock_Buf_To_Year(uint16_t *buf, stDS1307Time *time)
{

}

void Clock_Cycle(void)
{
	_delay_ms(500);
	I2C_ReadTime(&clock.DS1307Time);
	Clock_Time_To_Buf(&clock.DS1307Time,&clock.display_buf[LED_NOT_DISPLAYED_LEN]);
	LED_Out_Buf(&clock.display_buf,LED_BUF_LEN,0x1);

	switch(ClockState)
	{
		case STATE_DISPLAY_TIME:
		{
		}
		break;

		case STATE_DISPLAY_DATE:
		{
		}
		break;

		case STATE_DISPLAY_YEAR:
		{
		}
		break;

		case STATE_TUNE_TIME_HOURS:
		{
		}
		break;

		case STATE_TUNE_TIME_MINUTES:
		{
		}
		break;

		case STATE_TUNE_DATE_MONTH:
		{
		}
		break;

		case STATE_TUNE_DATE_DAY:
		{
		}
		break;

		case STATE_TUNE_YEAR:
		{
		}
		break;

		default:
		{
		}
		break;


	}

}
