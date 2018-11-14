
#include "bouton.h"


extern	GPIO_InitTypeDef GPIOBPB3_Init;

void initBouton (void){
	 
	__HAL_RCC_GPIOB_CLK_ENABLE(); //activation de l'horloge du GPIOB
	
	GPIOBPB3_Init.Pin = GPIO_PIN_3;
	GPIOBPB3_Init.Mode = GPIO_MODE_IT_RISING;
	GPIOBPB3_Init.Pull = GPIO_PULLDOWN;
	
	HAL_GPIO_Init(GPIOB, &GPIOBPB3_Init);
	
	
	HAL_NVIC_SetPriority(EXTI3_IRQn, 2, 0);
	HAL_NVIC_EnableIRQ(EXTI3_IRQn); 

	
	
}

