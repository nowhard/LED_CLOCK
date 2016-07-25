//#include "globals.h"
#include "menu.h"
#include "keyboard.h"
#include "timer1.h"
#include <avr/pgmspace.h>
#include "i2c.h"
#include <avr/wdt.h> 
#include "utilites.h"
#include "led_display.h"


typedef struct PROGMEM{
	void       *Next;
	void       *Previous;
	void       *Parent;
	void       *Child;
	uint8_t     Select;
	const char  Text[];
} menuItem;

menuItem* selectedMenuItem; // текущий пункт меню


#define MAKE_MENU(Name, Next, Previous, Parent, Child, Select, Text) \
    extern menuItem Next;     \
	extern menuItem Previous; \
	extern menuItem Parent;   \
	extern menuItem Child;  \
	menuItem Name = {(void*)&Next, (void*)&Previous, (void*)&Parent, (void*)&Child, (uint8_t)Select, { Text }}

#define PREVIOUS   ((menuItem*)pgm_read_word(&selectedMenuItem->Previous))
#define NEXT       ((menuItem*)pgm_read_word(&selectedMenuItem->Next))

#define PARENT     ((menuItem*)pgm_read_word(&selectedMenuItem->Parent))
#define CHILD      ((menuItem*)pgm_read_word(&selectedMenuItem->Child))
#define SELECT		(pgm_read_byte(&selectedMenuItem->Select))


#define NULL_ENTRY Null_Menu
menuItem        Null_Menu = {(void*)0, (void*)0, (void*)0, (void*)0, 0, {0x00}};

//                 NEXT,      PREVIOUS     PARENT,     CHILD

MAKE_MENU(m_s1i1,  m_s1i2,    NULL_ENTRY,  NULL_ENTRY, m_s2i1,       MENU_TIME, 			/*time*/"");
MAKE_MENU(m_s1i2,  m_s1i3,    m_s1i1,      NULL_ENTRY, m_s3i1,       MENU_DATE, 			/*data*/"");
MAKE_MENU(m_s1i3,  m_s1i4,	  m_s1i2,      NULL_ENTRY, m_s4i1,       MENU_YEAR, 			/*year*/"");
MAKE_MENU(m_s1i4,  m_s1i5,	  m_s1i3,      NULL_ENTRY, NULL_ENTRY,   MENU_TUNE_BRIGHTNESS_DAY,  	"");
MAKE_MENU(m_s1i5,  NULL_ENTRY,m_s1i4,      NULL_ENTRY, NULL_ENTRY,   MENU_TUNE_BRIGHTNESS_NIGHT,  	"");
// подменю Настройка времени
MAKE_MENU(m_s2i1,  NULL_ENTRY,NULL_ENTRY,  m_s1i1,     NULL_ENTRY,   MENU_TUNE_TIME, 		"");
// подменю Настройка даты
MAKE_MENU(m_s3i1,  NULL_ENTRY,NULL_ENTRY,  m_s1i2,     NULL_ENTRY,   MENU_TUNE_DATE, 		"");
// подменю Настройка года
MAKE_MENU(m_s4i1,  NULL_ENTRY,NULL_ENTRY,  m_s1i3,     NULL_ENTRY,   MENU_TUNE_YEAR, 		"");


void Menu_Change(menuItem* NewMenu)
{
	if ((void*)NewMenu == (void*)&NULL_ENTRY)
	  return;

	selectedMenuItem = NewMenu;
}

#define BLINK_CONST		30
//------------------------------------
void Menu_Display(stClock *clock) 
{
	static uint8_t blink_mask=0xFF;
	static uint16_t blink_counter=0;

//wdt_reset();	
	if(blink_counter<BLINK_CONST)
	{
		blink_counter++;
	}	
	else
	{
		blink_counter=0;
		blink_mask=~blink_mask;
	}


	switch(SELECT)
	{
		case MENU_TIME:
		{
			I2C_ReadTime(&clock->DS1307Time);
			clock->display_mask=0xFF;
			Time_To_Buf(&clock->DS1307Time, &clock->display_buf[LED_NOT_DISPLAYED_LEN]);

		}
		break;
		
		case MENU_DATE:
		{
			I2C_ReadTime(&clock->DS1307Time);
			clock->display_mask=0xFF;
			Date_To_Buf(&clock->DS1307Time, &clock->display_buf[LED_NOT_DISPLAYED_LEN]);
		}
		break;

		case MENU_YEAR:
		{
			I2C_ReadTime(&clock->DS1307Time);
			clock->display_mask=0xFF;
			Year_To_Buf(&clock->DS1307Time, &clock->display_buf[LED_NOT_DISPLAYED_LEN]);
		}
		break;

		case MENU_TUNE_BRIGHTNESS_DAY:
		{
			clock->display_mask=blink_mask;
		}
		break;

		case MENU_TUNE_BRIGHTNESS_NIGHT:
		{
			clock->display_mask=blink_mask;
		}
		break;

		case MENU_TUNE_TIME:
		{
			clock->display_mask=blink_mask;
		}
		break;

	    case MENU_TUNE_DATE:
		{
			clock->display_mask=blink_mask;
		}
		break;

		case MENU_TUNE_YEAR:
		{
			clock->display_mask=blink_mask;
		}
		break;

		default:
		{
		}
		break;
	}
}

void Menu_Key(enKey key, stClock *clock) {
	switch (key) 
	{
		case KEY_CODE_NONE: 
		{

		}
		break;
		//------------------------
		case KEY_CODE_A: 
		{
			switch(SELECT)//пункт меню
			{
				case MENU_TIME:
				{
					Menu_Change(NEXT);
				}
				break;

				case MENU_DATE:
				{
					Menu_Change(NEXT);
				}
				break;

				case MENU_YEAR:
				{
					Menu_Change(&m_s1i1);
				}
				break;
										
				case MENU_TUNE_TIME:
				{
					I2C_StoreTime(&clock->DS1307Time);
					Menu_Change(&m_s1i1);
				}
				break;


				case MENU_TUNE_DATE:
				{
					I2C_StoreDate(&clock->DS1307Time);
					Menu_Change(&m_s1i2);
				}
				break;


				case MENU_TUNE_YEAR:
				{
					I2C_StoreYear(&clock->DS1307Time);
					Menu_Change(&m_s1i3);
				}
				break;

				case MENU_TUNE_BRIGHTNESS_DAY:
				{

				}
				break;

				case MENU_TUNE_BRIGHTNESS_NIGHT:
				{

				}
				break;
				
				default:
				{
					
				}
				break;				
			}
		}
		break;

		//------------------------
		case KEY_CODE_B: 
		{
			switch(SELECT)//пункт меню
			{			
				case MENU_TUNE_TIME:
				{
					clock->DS1307Time.Minutes=BCD_Increment(clock->DS1307Time.Minutes,0,((5<<4)|9));
					Time_To_Buf(&clock->DS1307Time, &clock->display_buf[LED_NOT_DISPLAYED_LEN]);
				}
				break;


				case MENU_TUNE_DATE:
				{
					clock->DS1307Time.Month=BCD_Increment(clock->DS1307Time.Month,1,((1<<4)|2));
					Date_To_Buf(&clock->DS1307Time, &clock->display_buf[LED_NOT_DISPLAYED_LEN]);
				}
				break;


				case MENU_TUNE_YEAR:
				{
					clock->DS1307Time.Year=BCD_Increment(clock->DS1307Time.Year,0,((9<<4)|9));
					Year_To_Buf(&clock->DS1307Time, &clock->display_buf[LED_NOT_DISPLAYED_LEN]);
				}
				break;

				case MENU_TUNE_BRIGHTNESS_DAY:
				{
					
				}
				break;

				case MENU_TUNE_BRIGHTNESS_NIGHT:
				{

				}
				break;
				
				default:
				{
					Menu_Change(PREVIOUS);
				}
				break;				
			}
			
		}
		break;
		//------------------------
		case KEY_CODE_C:
		{ 
			switch(SELECT)//пункт меню
			{			
				case MENU_TUNE_TIME:
				{
					clock->DS1307Time.Hours=BCD_Increment(clock->DS1307Time.Hours,0,((2<<4)|3));
					Time_To_Buf(&clock->DS1307Time, &clock->display_buf[LED_NOT_DISPLAYED_LEN]);
				}
				break;


				case MENU_TUNE_DATE:
				{
					clock->DS1307Time.Date=BCD_Increment(clock->DS1307Time.Date,1,((3<<4)|1));
					Date_To_Buf(&clock->DS1307Time, &clock->display_buf[LED_NOT_DISPLAYED_LEN]);
				}
				break;


				case MENU_TUNE_YEAR:
				{

				}
				break;

				case MENU_TUNE_BRIGHTNESS_DAY:
				{

				}
				break;

				case MENU_TUNE_BRIGHTNESS_NIGHT:
				{

				}
				break;
				
				default:
				{
					Menu_Change(PREVIOUS);
				}
				break;				
			}			
		}
		break;
		//------------------------
		case KEY_CODE_D:
		{
	/*		switch(SELECT)//пункт меню
			{			
				case MENU_TUNE_TIME:
				{

				}
				break;


				case MENU_TUNE_DATE:
				{

				}
				break;


				case MENU_TUNE_YEAR:
				{

				}
				break;

				case MENU_TUNE_BRIGHTNESS_DAY:
				{

				}
				break;

				case MENU_TUNE_BRIGHTNESS_NIGHT:
				{

				}
				break;
				
				default:
				{
					Menu_Change(PREVIOUS);
				}
				break;				
			}*/

			Menu_Change(PREVIOUS);
		}
		break;
			
		//------------------------
		case KEY_CODE_AB://переход в режим настройки времени/даты/года
		{ 
			I2C_ReadTime(&clock->DS1307Time);
			Menu_Change(CHILD);
		}
		break;
		//------------------------
		case KEY_CODE_CD:
		{
			Menu_Change(&m_s1i4);
		}
		break;
		//------------------------
		default:
		{

		}
		break;
	}
}
//---------------------------------------------------
void Menu_Init(void) 
{
	selectedMenuItem = (menuItem*)&m_s1i1;
}
//--------------------------------------------------

