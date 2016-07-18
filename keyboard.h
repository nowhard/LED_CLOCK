#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

#define KBD_PIN_A		PD7
#define KBD_PIN_B		PD6
#define KBD_PIN_C		PD5
#define KBD_PIN_D		PD4


#define KBD_MASK (_BV(KBD_PIN_A)|_BV(KBD_PIN_B)|_BV(KBD_PIN_C)|_BV(KBD_PIN_D))

#define KBD_PIN			PIND
#define KBD_PORT		PORTD
#define KBD_DDR			DDRD


#define	KEY_NONE	KBD_MASK
#define KEY_A		((!(_BV(KBD_PIN_A)) & KBD_MASK)
#define KEY_B		((!(_BV(KBD_PIN_B)) & KBD_MASK)
#define KEY_C		((!(_BV(KBD_PIN_C)) & KBD_MASK)
#define KEY_D		((!(_BV(KBD_PIN_D)) & KBD_MASK)
#define KEY_AB		((!(_BV(KBD_PIN_A) | _BV(KBD_PIN_B))) & KBD_MASK)	


void  	KBD_Init(void);
uint8_t KBD_ReadKey(void);

#endif
