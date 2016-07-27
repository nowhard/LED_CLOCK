#include<avr/interrupt.h>
#include <ctype.h>
#include <stdint.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>

#include "led_display.h"
#include "clock.h"
#include <avr/wdt.h> 

int main(void)
{
	Clock_Init();
	wdt_enable(WDTO_1S);
	sei();

	while(1)
	{
		Clock_Cycle();
		wdt_reset();
	}
}




