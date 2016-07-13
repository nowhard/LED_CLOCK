#include "keyboard.h"
#include <avr/io.h>
#include <stdio.h>

#define KBD_PIN_LEFT		PD7
#define KBD_PIN_RIGHT		PD6
#define KBD_PIN_UP			PD5
#define KBD_PIN_DOWN		PD4
#define KBD_PIN_OK			PD3
#define KBD_PIN_GND			PD2

#define KBD_MASK (_BV(KBD_PIN_UP)|_BV(KBD_PIN_LEFT)|_BV(KBD_PIN_RIGHT))

#define KBD_PIN			PIND
#define KBD_PORT		PORTD
#define KBD_DDR			DDRD

uint8_t lastKey,prevKey;

unsigned char KBD_getKeyCode(uint8_t ah);

unsigned char KBD_getKeyCode(uint8_t ah) 
{


/*	if (!(ah & _BV(KBD_PIN_OK))) {
		return KEY_OK;
	}*/
	if (!(ah & _BV(KBD_PIN_UP))) {
		return KEY_UP;
	}
/*	if (!(ah & _BV(KBD_PIN_DOWN))) {
		return KEY_DOWN;
	}*/
	if (!(ah & _BV(KBD_PIN_LEFT))) {
		return KEY_LEFT;
	}
	if (!(ah & _BV(KBD_PIN_RIGHT))) {
		return KEY_RIGHT;
	}
	return 0;
}
//----------------------------
void KBD_readKey(void) 
{

	lastKey=KBD_getKeyCode(KBD_PIN & KBD_MASK);
	
	if (prevKey != lastKey) 
	{

	}
	prevKey = lastKey;

	return ;
}
//-------------------------------
void  KBD_init(void) 
{
	KBD_PORT |= KBD_MASK;
	KBD_DDR &= ~ KBD_MASK;

	lastKey = 0;
	prevKey = 0;
}
