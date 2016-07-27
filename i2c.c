#include "i2c.h"
#define I2C_PORT PORTC
#define I2C_DDR	 DDRC	
#define I2C_SCL	 5
#define I2C_SDA	 4
//---------------------I2C_INIT------------------------------------
void I2C_Init(void)
{
	I2C_PORT |= (1<<I2C_SCL)|(1<<I2C_SDA);	// Включим подтяжку на ноги, вдруг юзер на резисторы пожмотился
	I2C_DDR &=~((1<<I2C_SCL)|(1<<I2C_SDA));
	TWBR = 0x20;         			// Настроим битрейт
	TWSR = 0x00;
}
//---------------------I2C_WRITE------------------------------------

void I2C_Write(unsigned char address,unsigned char address_reg, unsigned char data)
{
	TWCR=(1<<TWINT)|(1<<TWSTA)|(1<<TWEN);//START
	
	while(!(TWCR&(1<<TWINT)));//...wait for start

	if((TWSR&0xF8)!=START)//result
	{
		TWCR=(1<<TWINT)|(1<<TWSTO)|(1<<TWEN);//STOP
		return;
	}

	TWDR=address;//address+write
	
	TWCR=(1<<TWINT)|(1<<TWEN);//transfer address

	while(!(TWCR&(1<<TWINT)));//...wait for start

	if((TWSR&0xF8)!=MT_SLA_ACK)//result
	{
		TWCR=(1<<TWINT)|(1<<TWSTO)|(1<<TWEN);//STOP
		return;
	}
	
	TWDR=(unsigned char)address_reg;//address+write
	
	TWCR=(1<<TWINT)|(1<<TWEN);//transfer address

	while(!(TWCR&(1<<TWINT)));//...wait for start

	if((TWSR&0xF8)!=MT_DATA_ACK)//result
	{
		TWCR=(1<<TWINT)|(1<<TWSTO)|(1<<TWEN);//STOP
		return;
	}

	TWDR=data;//address+write
	
	TWCR=(1<<TWINT)|(1<<TWEN);//transfer address

	while(!(TWCR&(1<<TWINT)));//...wait for start

	if((TWSR&0xF8)!=MT_DATA_ACK)//result
	{
		TWCR=(1<<TWINT)|(1<<TWSTO)|(1<<TWEN);//STOP
		return;
	}

	TWCR=(1<<TWINT)|(1<<TWSTO)|(1<<TWEN);//STOP

}
//---------------------I2C_READ------------------------------------

unsigned char I2C_Read(unsigned char address,unsigned char address_reg)
{

uint8_t reg;

TWCR=(1<<TWINT)|(1<<TWSTA)|(1<<TWEN);//START
	
	while(!(TWCR&(1<<TWINT)));//...wait for start

	if((TWSR&0xF8)!=START)//result
	{
		TWCR=(1<<TWINT)|(1<<TWSTO)|(1<<TWEN);//STOP
		return 0;
	}

	TWDR=address;//address+write
	
	TWCR=(1<<TWINT)|(1<<TWEN);//transfer address

	while(!(TWCR&(1<<TWINT)));//...wait for start

	if((TWSR&0xF8)!=MT_SLA_ACK)//result
	{
		TWCR=(1<<TWINT)|(1<<TWSTO)|(1<<TWEN);//STOP
		return 0;
	}
	
	TWDR=address_reg;//
	
	TWCR=(1<<TWINT)|(1<<TWEN);//transfer address

	while(!(TWCR&(1<<TWINT)));//...wait for start

	if((TWSR&0xF8)!=MT_DATA_ACK)//result
	{
		TWCR=(1<<TWINT)|(1<<TWSTO)|(1<<TWEN);//STOP
		return 0;
	}


//------------------read---------------------
TWCR=(1<<TWINT)|(1<<TWSTA)|(1<<TWEN);//START2
	
	while(!(TWCR&(1<<TWINT)));//...wait for start

	if((TWSR&0xF8)!=START_2)//result
	{
		TWCR=(1<<TWINT)|(1<<TWSTO)|(1<<TWEN);//STOP
		return 0;
	}


	
	TWDR=address+1;//address+read
	
	TWCR=(1<<TWINT)|(1<<TWEN);//transfer address

	while(!(TWCR&(1<<TWINT)));//...wait for start

	if((TWSR&0xF8)!=MT_SLA_READ_ACK)//result
	{
		TWCR=(1<<TWINT)|(1<<TWSTO)|(1<<TWEN);//STOP	
		return 0;
	}

    
	

	TWCR=(1<<TWINT)|(1<<TWEN);//read & nack

	while(!(TWCR&(1<<TWINT)));//...wait for start
	
	if((TWSR&0xF8)!=READ_NACK)
	{
		TWCR=(1<<TWINT)|(1<<TWSTO)|(1<<TWEN);//STOP
		return 0;
		
	}
	reg=TWDR;
    
	
	TWCR=(1<<TWINT)|(1<<TWSTO)|(1<<TWEN);//STOP

	return reg;

}
//-----------------------------------------------------------
void 	I2C_Read_Buf(uint8_t address_mem, void* data, uint8_t data_len)
{
	uint8_t i=0;

	for(i=0;i<data_len;i++)
	{
		((uint8_t*)data)[i]=I2C_Read(TMR_ADDR,address_mem+i);
	}
}

void 	I2C_Write_Buf(uint8_t address_mem, void* data, uint8_t data_len)
{
	uint8_t i=0;

	for(i=0;i<data_len;i++)
	{
		I2C_Write(TMR_ADDR,address_mem+i,((uint8_t*)data)[i]);
	}
}
//------------------------------------------------------------
void I2C_ReadTime(stDS1307Time *time)
{	
	time->Seconds	=I2C_Read(TMR_ADDR,REG_SECONDS);
	_delay_us(100);
	time->Minutes	=I2C_Read(TMR_ADDR,REG_MINUTES);
	_delay_us(100);
	time->Hours		=I2C_Read(TMR_ADDR,REG_HOURS);
	_delay_us(100);
	time->Day		=I2C_Read(TMR_ADDR,REG_DAY);
	_delay_us(100);
	time->Date		=I2C_Read(TMR_ADDR,REG_DATE);
	_delay_us(100);
	time->Month		=I2C_Read(TMR_ADDR,REG_MONTH);
	_delay_us(100);
	time->Year		=I2C_Read(TMR_ADDR,REG_YEAR);
	_delay_us(100);
	time->Control	=I2C_Read(TMR_ADDR,REG_CONTROL);
	_delay_us(100);
}
//----------------------------------------------------------
void I2C_DS1307Init(stDS1307Time *time)//инициализация часов, установка
{
	uint8_t reg;

	reg=I2C_Read(TMR_ADDR,REG_SECONDS);
	_delay_us(1000);

	if((reg&0x80)!=0)
	{
		I2C_Write(TMR_ADDR,REG_HOURS,(1<<4)+2);
		_delay_us(100);


		I2C_Write(TMR_ADDR,REG_MINUTES,(0<<4)+0); 
		_delay_us(100);


		I2C_Write(TMR_ADDR,REG_SECONDS,0x0); 
		_delay_us(100);
	}
}
//---------------------------------------------------
void I2C_StoreTime(stDS1307Time *time)
{
	I2C_Write(TMR_ADDR,REG_HOURS,time->Hours);
	_delay_us(100);

	I2C_Write(TMR_ADDR,REG_MINUTES,time->Minutes); 
	_delay_us(100);

	I2C_Write(TMR_ADDR,REG_SECONDS,0x0); 
	_delay_us(100);
}
//--------------------------------------------------------
void I2C_StoreDate(stDS1307Time *time)
{
	I2C_Write(TMR_ADDR,REG_MONTH,time->Month);
	_delay_us(100);

	I2C_Write(TMR_ADDR,REG_DATE,time->Date); 
	_delay_us(100);	
}
//--------------------------------------------------------
void I2C_StoreYear(stDS1307Time *time)
{
	I2C_Write(TMR_ADDR,REG_YEAR,time->Year); 
	_delay_us(100);
}
