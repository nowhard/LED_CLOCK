#ifndef _MENU_H_
#define _MENU_H_


#include <ctype.h>
#include "keyboard.h"
#include "clock.h"

enum {
    MENU_CANCEL=1,
    MENU_TIME,
    MENU_DATE,
    MENU_YEAR,
    MENU_TUNE_TIME,
    MENU_TUNE_DATE,
    MENU_TUNE_YEAR,
    MENU_TUNE_BRIGHTNESS_DAY_VAL,
	MENU_TUNE_BRIGHTNESS_DAY_TIME,
	MENU_TUNE_BRIGHTNESS_NIGHT_VAL,
	MENU_TUNE_BRIGHTNESS_NIGHT_TIME,
};


void	Menu_Init(void);
void 	Menu_Key(enKey key, stClock *clock);
void 	Menu_Display(stClock *clock);

  
#endif
