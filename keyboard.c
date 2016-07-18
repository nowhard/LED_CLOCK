#include "keyboard.h"
#include <avr/io.h>
#include <stdio.h>


static uint8_t lastPIN;

uint8_t KBD_ReadKey(void) 
{

	lastPIN=(KBD_PIN & KBD_MASK);
	if(lastPIN!=KBD_MASK)
	{
		_delay_ms(1);
		if((lastPIN!=KBD_MASK) && (lastPIN==(KBD_PIN & KBD_MASK)))
		{
			return lastPIN;
		}
		else
		{	
			lastPIN=KBD_MASK;
			return KEY_NONE;	
		}
	}
	else
	{
		return KEY_NONE;
	}
}
//-------------------------------
void  KBD_Init(void) 
{
	KBD_PORT |= KBD_MASK;
	KBD_DDR &= ~ KBD_MASK;

	lastKey = 0;
	prevKey = 0;
}
