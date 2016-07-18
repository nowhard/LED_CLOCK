//#include "globals.h"
#include "menu.h"
#include "keyboard.h"
#include "core.h"
#include "timer1.h"
#include "adc.h"
#include <avr/pgmspace.h>
#include "i2c.h"
#include "led_process.h"
#include "ext_int.h"
 #include <avr/wdt.h> 



typedef struct PROGMEM{
	void       *Next;
	void       *Previous;
	void       *Parent;
	void       *Child;
	uint8_t     Select;
	const char  Text[];
} menuItem;

menuItem* selectedMenuItem; // текущий пункт меню

volatile unsigned char time_tune_state=0, date_tune_state=0;//метки состояния настройки(настройка минута-час, день-месяц)
//extern volatile unsigned int frequency;
extern unsigned int mid_mas[];
volatile unsigned long freq=0;
//menuItem* menuStack[10];
//volatile uint8_t menuStackTop;


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

char strNULL[] PROGMEM = "";

#define NULL_ENTRY Null_Menu
menuItem        Null_Menu = {(void*)0, (void*)0, (void*)0, (void*)0, 0, {0x00}};

//                 NEXT,      PREVIOUS     PARENT,     CHILD

MAKE_MENU(m_s1i1,  m_s1i2,    NULL_ENTRY,  NULL_ENTRY, m_s2i1,       MENU_TIME, 			/*time*/"");
MAKE_MENU(m_s1i2,  m_s1i3,    m_s1i1,      NULL_ENTRY, m_s3i1,       MENU_DATE, 			/*data*/"");
MAKE_MENU(m_s1i3,  m_s1i4,	  m_s1i2,      NULL_ENTRY, m_s4i1,       MENU_YEAR, 			/*year*/"");
MAKE_MENU(m_s1i4,  m_s1i5,    m_s1i3,      NULL_ENTRY, NULL_ENTRY,   MENU_TUNE_BRIGHTNESS,  "");

// подменю Настройка времени
MAKE_MENU(m_s2i1,  m_s2i2,	  NULL_ENTRY,  m_s1i1,     NULL_ENTRY,   MENU_TUNE_HOURS, 		"");
MAKE_MENU(m_s2i2,  NULL_ENTRY,m_s2i1,	   m_s1i1,     NULL_ENTRY,   MENU_TUNE_MINUTES,		"");
// подменю Настройка даты
MAKE_MENU(m_s3i1,  m_s3i2,	  NULL_ENTRY,  m_s1i2,     NULL_ENTRY,   MENU_TUNE_DAY, 		"");
MAKE_MENU(m_s3i2,  NULL_ENTRY,m_s3i1,  	   m_s1i2,     NULL_ENTRY,   MENU_TUNE_MONTH, 		"");
// подменю Настройка года
MAKE_MENU(m_s4i1,  NULL_ENTRY,NULL_ENTRY,  m_s1i3,     NULL_ENTRY,   MENU_TUNE_YEAR, 		"");


//volatile unsigned char disp_buf[6]={0};//буфер дисплея
//unsigned char mode=0;//режим клавиатуры(режим меню, режим правки)

extern volatile unsigned char brightness;
uint8_t selectMenu(msg_par par);

void menuChange(menuItem* NewMenu)
{
	if ((void*)NewMenu == (void*)&NULL_ENTRY)
	  return;

	selectedMenuItem = NewMenu;
}
//------------------------------------
unsigned char dispMenu(void) 
{
//	menuItem* tempMenu;
//	tempMenu = (menuItem*)pgm_read_word(&selectedMenuItem);
	static unsigned char blink=100,blink_flag=0;
//	static unsigned char blink_mask=0xFF;
//wdt_reset();	
	if(blink<2)
	{
		blink++;
	}	
	else
	{
		blink_flag=!blink_flag;
		blink=0;
	}

	switch(SELECT)
	{
		case MENU_TIME:
		{

		}
		break;
		
		case MENU_DATE:
		{

		}
		break;

		case MENU_YEAR:
		{

		}
		break;

		case MENU_TUNE_BRIGHTNESS:
		{

		}
		break;

		case MENU_TUNE_HOURS:
		{

		}
		break;

	    case MENU_TUNE_MINUTES:
		{

		}
		break;

		case MENU_TUNE_DAY:
		{

		}
		break;

		case MENU_TUNE_MONTH:
		{

		}
		break;

		case MENU_TUNE_YEAR:
		{

		}
		break;

		default:
		{
		}
		break;
	}

	return (1);
}

uint8_t menuKey(msg_par par) {
	switch (par) 
	{
		case 0: 
		{
			return 1;
		}
		//------------------------
		case KEY_LEFT: 
		{
			switch(SELECT)//пункт меню
			{			
				case MENU_TUNE_TIME://определяем поведение кнопок в этом меню
				{
					time_tune_state=0;
				}
				break;

				case MENU_TUNE_DATE:
				{
					date_tune_state=0;
				}
				break;
				
				default:
				{
					menuChange(PREVIOUS);
				}
				break;				
			}
		}
		break;

		//------------------------
		case KEY_RIGHT: 
		{
			switch(SELECT)//пункт меню
			{			
				case MENU_TUNE_TIME:
				{
					time_tune_state=1;
				}
				break;

				case MENU_TUNE_DATE:
				{
					date_tune_state=1;
				}
				break;
				
				default:
				{
					menuChange(NEXT);
				}
				break;				
			}

		}
		break;
		//------------------------
		case KEY_UP:
		{ 
			switch(SELECT)//пункт меню
			{			
				case MENU_TUNE_BRIGHTNESS:
				{	
					if(brightness>=0xF)
					{
						brightness=0xF;	
					}
					else
					{
						brightness=(brightness+1)&0xF;	
						//I2C_Write_Byte(SLA_ADDR,0x0,brightness);
					}
				}
				break;

				case MENU_TUNE_TIME:
				{
					if(time_tune_state)
					{
						if(clk.hour<23)
						{
							clk.hour++;
						}
						else
						{
							clk.hour=23;	
						}
					}
					else
					{
						if(clk.minute<59)
						{
							clk.minute++;
						}
						else
						{
							clk.minute=59;
						}
					}
				}
				break;

				case MENU_TUNE_DATE:
				{
					if(date_tune_state)
					{
						if(clk.month<12)
						{
							clk.month++;
						}
					}
					else
					{
						if(clk.day<31)
						{
							clk.day++;
						}
					}
				}
				break;

				case MENU_TUNE_YEAR:
				{
					if(clk.year>=99)
					{
						clk.year=99;
					}
					else
					{
						clk.year++;	
					}
				}
				break;
				
				default:
				{
					//menuChange(NEXT);
				}
				break;				
			}			
		}
		break;
		//------------------------
		case KEY_DOWN:
		{
			switch(SELECT)//пункт меню
			{			
				case MENU_TUNE_BRIGHTNESS:
				{

					if(brightness<=0x1)
					{
						brightness=0x1;	
					}
					else
					{
						brightness=(brightness-1)&0xF;	
						I2C_Write_Byte(SLA_ADDR,0x0,brightness);					
					}
				}
				break;

				case MENU_TUNE_TIME:
				{
					if(time_tune_state)
					{
						if(clk.hour>0)
						{
							clk.hour--;
						}
					}
					else
					{
						if(clk.minute>0)
						{
							clk.minute--;
						}
					}				
				}
				break;

				case MENU_TUNE_DATE:
				{
					if(date_tune_state)
					{
						if(clk.month>1)
						{
							clk.month--;
						}
					}
					else
					{
						if(clk.day>1)
						{
							clk.day--;
						}
					}
				}
				break;

				case MENU_TUNE_YEAR:
				{	
					if(clk.year<=0)
					{
						clk.year=0;
					}
					else
					{
						clk.year--;	
					}
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
		case KEY_OK:
		{ // выбор пункта
			switch(SELECT)//пункт меню
			{			
				case MENU_TUNE_TIME:
				{
					StoreTime(&clk,0);
					menuChange(PARENT);
				}
				break;

				case MENU_TUNE_DATE:
				{
					StoreTime(&clk,1);
					menuChange(PARENT);
				}
				break;

				case MENU_TUNE_YEAR:
				{	
					StoreTime(&clk,2);
					menuChange(PARENT);
				}
				break;
				
				default:
				{
					menuChange(CHILD);	
				}
				break;				
			}		
		}
		break;
		//------------------------
		case KEY_GND:// отмена выбора (возврат)
		{
			menuChange(PARENT);
		}
		break;
		//------------------------
		default:
		{
		}
		break;
	}
	//dispMenu(0);
	return (1);
}
//---------------------------------------------------
unsigned char startMenu() 
{
	selectedMenuItem = (menuItem*)&m_s1i1;
	return (0);
}
//--------------------------------------------------

