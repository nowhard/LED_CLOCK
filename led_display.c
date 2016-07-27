#include "led_display.h"


//--------------------------------------------------------------------------------
void LED_Out(stClock *clock, uint8_t out_buf_len)//вывод буфера в SPI bit-bang
{
	uint8_t i;

	clock->display_buf[0]=(0xA00|clock->brightnessCurrent|0x01);

	for(i=0;i<out_buf_len;i++)
	{
		if(i>=5)
		{
			if(clock->display_mask&(1<<(i-5)))
			{
				LED_SPI_WriteWord(clock->display_buf[i]);
			}
			else
			{
				LED_SPI_WriteWord(clock->display_buf[i]|0xF);
			}
		}
		else
		{
			LED_SPI_WriteWord(clock->display_buf[i]);
		}
	}

	return;	
}
//------------------------------------------------------------------------------------------------

#define SPI_PORTX PORTB
#define SPI_DDRX DDRB
 
#define SPI_MISO 4 
#define SPI_MOSI 3
#define SPI_SCK 5
#define SPI_SS 2
 
/*инициализация SPI модуля в режиме master*/
void LED_SPI_Init(void)
{
   /*настройка портов ввода-вывода
   все выводы, кроме MISO выходы*/
   SPI_DDRX |= (1<<SPI_MOSI)|(1<<SPI_SCK)|(1<<SPI_SS);
   SPI_PORTX &= ~(1<<SPI_SS); 
 
   /*разрешение spi,старший бит вперед,мастер, режим 0*/
   SPCR = (1<<SPE)|(0<<DORD)|(1<<MSTR)|(0<<CPOL)|(0<<CPHA)|(0<<SPR1)|(0<<SPR0);

   SPSR = (0<<SPI2X);
}

void LED_SPI_WriteWord(uint16_t data)
{ 
   SPDR = ((uint8_t *)(&data))[1];
   while(!(SPSR & (1<<SPIF)));

   SPDR = ((uint8_t *)(&data))[0];
   while(!(SPSR & (1<<SPIF)));

	_delay_us(10);	
   SPI_PORTX |= (1<<SPI_SS);
   _delay_us(10);
   SPI_PORTX &= ~(1<<SPI_SS);   
   _delay_us(10);
}
