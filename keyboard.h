#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

#include <stdint.h>

#define KBD_PIN_A		PD0
#define KBD_PIN_B		PD1
#define KBD_PIN_C		PD2
#define KBD_PIN_D		PC6


#define KBD_MASK_1 (_BV(KBD_PIN_A)|_BV(KBD_PIN_B)|_BV(KBD_PIN_C))

#define KBD_PIN_1			PIND
#define KBD_PORT_1			PORTD
#define KBD_DDR_1			DDRD

#define KBD_MASK_2 (_BV(KBD_PIN_D))

#define KBD_PIN_2			PINC
#define KBD_PORT_2			PORTC
#define KBD_DDR_2			DDRC



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
