#include "stm32f10x.h"
#include "stm32f1xx_hal.h"
#include "bouton.h"
#include "gpio.h"

extern	GPIO_InitTypeDef GPIOPB3_Init;

void initGPIO (){
	
	__HAL_RCC_GPIOB_CLK_ENABLE(); //activation de l'horloge du GPIOB
	
	GPIOPB3_Init.Pin = GPIO_PIN_3;
	GPIOPB3_Init.Mode = GPIO_MODE_IT_RISING;
	GPIOPB3_Init.Pull = GPIO_NOPULL;
	
	HAL_GPIO_Init(GPIOB, &GPIOPB3_Init);
	
	
	HAL_NVIC_SetPriority(EXTI3_IRQn, 2, 0);
	HAL_NVIC_EnableIRQ(EXTI3_IRQn); 

	
	
}

