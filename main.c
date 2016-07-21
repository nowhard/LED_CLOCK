#include<avr/interrupt.h>
#include <ctype.h>
#include <stdint.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>

#include "led_display.h"
#include "clock.h"


int main(void)
{
	Clock_Init();
	//sei();

	while(1)
	{
		Clock_Cycle();
	}
}




