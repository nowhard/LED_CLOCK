#include "timer1.h"
//--------------------------------------------------
/*void Timer1_Init(void)//������������� timer1
{
	TIMSK|=(1<<TOIE1);//overflow interrupt enable

	TCNT1H=0xFE;
	TCNT1L=0x5E;
	
	return;
}
//--------------------------------------------------
void Timer1_Run(void)//������ timer1
{
	TCCR1B|=((0<<CS12)|(0<<CS11)|(1<<CS10));//FTMR_CLK=FCLK	
}
//--------------------------------------------------
void Timer1_Stop(void)//������� timer1
{
	TCCR1B&=~((1<<CS12)|(1<<CS11)|(1<<CS10));//FTMR_CLK=0	
}
//--------------------------------------------------
void Timer1_Reset(void)//����� timer1
{
	TCNT1H=0xFE;
	TCNT1L=0x5E;
	TCCR1B|=((0<<CS12)|(0<<CS11)|(1<<CS10));//FTMR_CLK=FCLK	
}
//--------------------------------------------------*/
void init_pwm (void)

{

  TCCR1A=(1<<COM1A1)|(1<<WGM10); //�� ������ OC1A �������, ����� OCR1A==TCNT1, ������������ ���

  TCCR1B=(0<<CS10)|(1<<CS11);		 //��������= /1

  OCR1A=0x00;			//��������� ������� �������

}
