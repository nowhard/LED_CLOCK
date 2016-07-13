#ifndef LED_DISPLAY_H
#define LED_DISPLAY_H

#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include<avr/interrupt.h>
//-------------------------------------------

#define LED_BUF_LEN				10
#define LED_NOT_DISPLAYED_LEN	5


void LED_SPI_Init(void);
void LED_SPI_WriteWord(uint16_t data);
void LED_Out_Buf(uint16_t *out_buf, uint8_t out_buf_len, uint8_t mask);

#endif
