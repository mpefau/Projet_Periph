#ifndef SERVO
#define SERVO

#include "stm32f1xx_hal.h"
#include "gpio.h"
#include "main.h"
#include "stm32f1xx.h"

#define ARR_TIM2 14399
#define PSC_TIM2 99

	extern TIM_HandleTypeDef HandleTIM2;
	extern TIM_OC_InitTypeDef initPWM_patte;
	extern TIM_OC_InitTypeDef initPWM_ouverture;

void initServos();

void tourner(float angle);

void ouvrirBoite(float rapport_cyclique);


#endif