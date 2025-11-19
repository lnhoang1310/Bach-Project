#ifndef DS1307_H
#define DS1307_H

#include "i2c.h"

#define DS1307_ADDRESS 0x68

typedef struct{
	Soft_I2C_TypeDef* i2c;
	uint8_t address;
	uint8_t hour;
	uint8_t minute;
	uint8_t second;
	uint8_t date;
	uint8_t month;
	uint8_t year;
}DS1307_Typedef;

void DS1307_Init(DS1307_Typedef* rtc, Soft_I2C_TypeDef* _i2c, uint8_t _address);
void DS1307_GetTime(DS1307_Typedef* rtc);
void DS1307_SetTime(DS1307_Typedef* rtc, uint8_t hour, uint8_t minute, uint8_t second, uint8_t date, uint8_t month, uint8_t year);
#endif
