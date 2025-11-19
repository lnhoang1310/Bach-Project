#ifndef INC_SERVO_H
#define INC_SERVO_H

#include "stm32f1xx.h"
#define MIN_PULSE_WIDTH 1136
#define MAX_PULSE_WIDTH 2281

typedef struct{
	TIM_HandleTypeDef *htim;
	uint32_t Channel;
	uint8_t Angle;
}Servo_TypeDef;

void Servo_Set(Servo_TypeDef* servo, uint8_t angle);
void Servo_Init(Servo_TypeDef *servo, TIM_HandleTypeDef* htim, uint32_t channel);
#endif
