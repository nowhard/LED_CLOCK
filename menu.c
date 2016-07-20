//#include "globals.h"
#include "menu.h"
#include "keyboard.h"
#include "timer1.h"
#include <avr/pgmspace.h>
#include "i2c.h"
#include <avr/wdt.h> 
#include "utilites.h"


typedef struct PROGMEM{
	void       *Next;
	void       *Previous;
	void       *Parent;
	void       *Child;
	uint8_t     Select;
	const char  Text[];
} menuItem;

menuItem* selectedMenuItem; // ������� ����� ����

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
MAKE_MENU(m_s1i4,  NULL_ENTRY,m_s1i3,      NULL_ENTRY, NULL_ENTRY,   MENU_TUNE_BRIGHTNESS,  "");

// ������� ��������� �������
MAKE_MENU(m_s2i1,  NULL_ENTRY,NULL_ENTRY,  m_s1i1,     NULL_ENTRY,   MENU_TUNE_TIME, 		"");
//MAKE_MENU(m_s2i2,  NULL_ENTRY,m_s2i1,	   m_s1i1,     NULL_ENTRY,   MENU_TUNE_MINUTES,		"");
// ������� ��������� ����
MAKE_MENU(m_s3i1,  NULL_ENTRY,NULL_ENTRY,  m_s1i2,     NULL_ENTRY,   MENU_TUNE_DATE, 		"");
//MAKE_MENU(m_s3i2,  NULL_ENTRY,m_s3i1,  	   m_s1i2,     NULL_ENTRY,   MENU_TUNE_MONTH, 		"");
// ������� ��������� ����
MAKE_MENU(m_s4i1,  NULL_ENTRY,NULL_ENTRY,  m_s1i3,     NULL_ENTRY,   MENU_TUNE_YEAR, 		"");


//volatile unsigned char disp_buf[6]={0};//����� �������
//unsigned char mode=0;//����� ����������(����� ����, ����� ������)

//extern volatile unsigned char brightness;
//uint8_t selectMenu(msg_par par);

void Menu_Change(menuItem* NewMenu)
{
	if ((void*)NewMenu == (void*)&NULL_ENTRY)
	  return;

	selectedMenuItem = NewMenu;
}
//------------------------------------
void Menu_Display(stClock *clock) 
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
			I2C_ReadTime(&clock->DS1307Time);
			Time_To_Buf(&clock->DS1307Time, clock->display_buf);

		}
		break;
		
		case MENU_DATE:
		{
			I2C_ReadTime(&clock->DS1307Time);
			Date_To_Buf(&clock->DS1307Time, clock->display_buf);
		}
		break;

		case MENU_YEAR:
		{
			I2C_ReadTime(&clock->DS1307Time);
			Year_To_Buf(&clock->DS1307Time, clock->display_buf);
		}
		break;

		case MENU_TUNE_BRIGHTNESS:
		{

		}
		break;

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
		//------------------------
		case KEY_CODE_A: 
		{
			switch(SELECT)//����� ����
			{			
				case MENU_TUNE_TIME:
				{
					I2C_StoreTime(&clock->DS1307Time);
				}
				break;


				case MENU_TUNE_DATE:
				{
					I2C_StoreDate(&clock->DS1307Time);
				}
				break;


				case MENU_TUNE_YEAR:
				{
					I2C_StoreYear(&clock->DS1307Time);
				}
				break;

				case MENU_TUNE_BRIGHTNESS:
				{

				}
				break;
				
				default:
				{
					
				}
				break;				
			}
			Menu_Change(PREVIOUS);
		}
		break;

		//------------------------
		case KEY_CODE_B: 
		{

		}
		break;
		//------------------------
		case KEY_CODE_C:
		{ 
			switch(SELECT)//����� ����
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

				case MENU_TUNE_BRIGHTNESS:
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
			switch(SELECT)//����� ����
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

				case MENU_TUNE_BRIGHTNESS:
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
		case KEY_CODE_AB:
		{ 
			Menu_Change(CHILD);		
		}
		break;
		//------------------------
		case KEY_CODE_CD:
		{
			Menu_Change(PARENT);
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

