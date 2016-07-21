#include "keyboard.h"
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>

static uint8_t lastKEY=KEY_CODE_NONE, previousKEY=KEY_CODE_NONE;

uint8_t KBD_ReadPins(void)
{
	uint8_t key=0;

	if((KBD_PIN_1 & _BV(KBD_PIN_A))==0)
	{
		key|=(1<<0);
	}
	
	if((KBD_PIN_1 & _BV(KBD_PIN_B))==0)
	{
		key|=(1<<1);
	}
	
	if((KBD_PIN_1 & _BV(KBD_PIN_C))==0)
	{
		key|=(1<<2);
	}
	
	if((KBD_PIN_2 & _BV(KBD_PIN_D))==0)
	{
		key|=(1<<3);
	}	
	
	return key;	
}

enKey KBD_ReadKey(void) 
{
	lastKEY=KBD_ReadPins();

	if(lastKEY!=KEY_CODE_NONE)
	{
		if(lastKEY!=previousKEY)
		{
			_delay_ms(1);
			if((lastKEY!=KEY_CODE_NONE) && (lastKEY==KBD_ReadPins()))
			{
				previousKEY=lastKEY;
				return lastKEY;
			}
			else
			{	
				lastKEY		= KEY_CODE_NONE;
				previousKEY = KEY_CODE_NONE;
				return KEY_CODE_NONE;	
			}
		}
		else
		{
			return KEY_CODE_NONE;
		}
	}
	else
	{
		previousKEY = KEY_CODE_NONE;
		return KEY_CODE_NONE;
	}

}
//-------------------------------
void  KBD_Init(void) 
{
	KBD_PORT_1 |= KBD_MASK_1;
	KBD_DDR_1 &= ~ KBD_MASK_1;

	KBD_PORT_2 |= KBD_MASK_2;
	KBD_DDR_2 &= ~ KBD_MASK_2;

	//lastPIN 	= KBD_MASK;
	//previousPIN = KBD_MASK;
}
