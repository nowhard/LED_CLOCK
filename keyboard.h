#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

#include <stdint.h>

#define KBD_PIN_A		PD0
#define KBD_PIN_B		PD1
#define KBD_PIN_C		PD2
#define KBD_PIN_D		PD3


#define KBD_MASK (_BV(KBD_PIN_A)|_BV(KBD_PIN_B)|_BV(KBD_PIN_C) |_BV(KBD_PIN_D))

#define KBD_PIN			PIND
#define KBD_PORT		PORTD
#define KBD_DDR			DDRD





typedef enum
{
	KEY_CODE_NONE=0,
	KEY_CODE_A=1,
	KEY_CODE_B=2,
	KEY_CODE_C=4,
	KEY_CODE_D=8,
	KEY_CODE_AB=3,
	KEY_CODE_CD=12,
} enKey;	


void  	KBD_Init(void);
enKey 	KBD_ReadKey(void);

#endif
