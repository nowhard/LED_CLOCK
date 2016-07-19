#ifndef _MENU_H_
#define _MENU_H_


#include <ctype.h>
#include "keyboard.h"

enum {
    MENU_CANCEL=1,
    MENU_TIME,
    MENU_DATE,
    MENU_YEAR,
    MENU_TUNE_HOURS,
	MENU_TUNE_MINUTES,
    MENU_TUNE_DAY,
	MENU_TUNE_MONTH,
    MENU_TUNE_YEAR,
    MENU_TUNE_BRIGHTNESS,
};


void	Menu_Init(void);
void 	Menu_Key(enKey key);
void 	Menu_Display(void);

  
#endif
