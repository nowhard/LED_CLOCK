#include "keyboard.h"
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>

static uint8_t lastPIN, previousPIN;

enKey KBD_ReadKey(void) 
{
	lastPIN=(KBD_PIN & KBD_MASK);

	if((lastPIN!=KBD_MASK) && (lastPIN!=previousPIN))
	{
		_delay_ms(1);
		if((lastPIN!=KBD_MASK) && (lastPIN==(KBD_PIN & KBD_MASK)))
		{
			previousPIN=lastPIN;

			if(lastPIN==KEY_A)  return KEY_CODE_A;
			if(lastPIN==KEY_B)  return KEY_CODE_B;
			if(lastPIN==KEY_C)  return KEY_CODE_C;
			if(lastPIN==KEY_D)  return KEY_CODE_D;
			if(lastPIN==KEY_AB) return KEY_CODE_AB;
			if(lastPIN==KEY_CD) return KEY_CODE_CD;

			return lastPIN;
		}
		else
		{	
			lastPIN		=KBD_MASK;
			previousPIN = KBD_MASK;
			return KEY_CODE_NONE;	
		}
	}
	else
	{
		previousPIN = KBD_MASK;
		return KEY_CODE_NONE;
	}
}
//-------------------------------
void  KBD_Init(void) 
{
	KBD_PORT |= KBD_MASK;
	KBD_DDR &= ~ KBD_MASK;

	lastPIN 	= KBD_MASK;
	previousPIN = KBD_MASK;
}
