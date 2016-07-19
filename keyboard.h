#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

#include <stdint.h>

#define KBD_PIN_A		PD7
#define KBD_PIN_B		PD6
#define KBD_PIN_C		PD5
#define KBD_PIN_D		PD4


#define KBD_MASK (_BV(KBD_PIN_A)|_BV(KBD_PIN_B)|_BV(KBD_PIN_C)|_BV(KBD_PIN_D))

#define KBD_PIN			PIND
#define KBD_PORT		PORTD
#define KBD_DDR			DDRD


#define	KEY_NONE	KBD_MASK
#define KEY_A		((!(_BV(KBD_PIN_A))) & KBD_MASK)
#define KEY_B		((!(_BV(KBD_PIN_B))) & KBD_MASK)
#define KEY_C		((!(_BV(KBD_PIN_C))) & KBD_MASK)
#define KEY_D		((!(_BV(KBD_PIN_D))) & KBD_MASK)
#define KEY_AB		(( !(_BV(KBD_PIN_A) | _BV(KBD_PIN_B)) ) & KBD_MASK)
#define KEY_CD		(( !(_BV(KBD_PIN_C) | _BV(KBD_PIN_D)) ) & KBD_MASK)


typedef enum
{
	KEY_CODE_NONE=0,
	KEY_CODE_A,
	KEY_CODE_B,
	KEY_CODE_C,
	KEY_CODE_D,
	KEY_CODE_AB,
	KEY_CODE_CD,
} enKey;	


void  	KBD_Init(void);
enKey 	KBD_ReadKey(void);

#endif
