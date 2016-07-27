#ifndef I2C_H
#define I2C_H

#include<avr/io.h>
#include<avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>

//---------------------I2C-------------------------------
#define START 			0x08
#define	MT_SLA_ACK		0x18
#define	MT_SLA_READ_ACK	0x40
#define MT_DATA_ACK		0x28
#define	START_2			0x10
#define	READ_ACK		0x50
#define	READ_NACK		0x58

#define SLA_ADDR		0xD0
#define TMR_ADDR		0xD0

#define ADDR_BRIGHTNESS_DAY			0x8
#define ADDR_BRIGHTNESS_NIGHT		0x10

typedef struct
{
	uint8_t Seconds;
	uint8_t Minutes;
	uint8_t Hours;
	uint8_t Day;
	uint8_t Date;
	uint8_t Month;
	uint8_t Year;
	uint8_t Control;
} stDS1307Time;

enum
{
	REG_SECONDS=0,
	REG_MINUTES,
	REG_HOURS,
	REG_DAY,
	REG_DATE,
	REG_MONTH,
	REG_YEAR,
	REG_CONTROL,

} enDS1307Registers;

//-------------------------------------------------------  
void 	I2C_Init(void);
uint8_t I2C_Read_Byte(uint8_t address,uint8_t address_mem);
void 	I2C_Write_Byte(uint8_t address,uint8_t address_mem, uint8_t data);

void 	I2C_Read_Buf(uint8_t address_mem, void* data, uint8_t data_len);
void 	I2C_Write_Buf(uint8_t address_mem, void* data, uint8_t data_len);

void 	I2C_ReadTime(stDS1307Time *time);
void 	I2C_StoreTime(stDS1307Time *time);
void 	I2C_StoreDate(stDS1307Time *time);
void 	I2C_StoreYear(stDS1307Time *time);

void 	I2C_DS1307Init(stDS1307Time *time);//инициализация часов, установка

#endif
