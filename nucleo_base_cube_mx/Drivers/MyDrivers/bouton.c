
#include "bouton.h"


<<<<<<< HEAD
extern	GPIO_InitTypeDef GPIOBPB3_Init;

void initBouton (void){
	 
=======
void InitBouton (){
	
>>>>>>> 3023c5c8271a7d6395a45dc14692667824fb5896
	__HAL_RCC_GPIOB_CLK_ENABLE(); //activation de l'horloge du GPIOB
	
	GPIOBPB3_Init.Pin = GPIO_PIN_3;
	GPIOBPB3_Init.Mode = GPIO_MODE_IT_RISING;
	GPIOBPB3_Init.Pull = GPIO_NOPULL;
	
	HAL_GPIO_Init(GPIOB, &GPIOBPB3_Init);
	
	HAL_NVIC_SetPriority(EXTI3_IRQn, 2, 0);
	HAL_NVIC_EnableIRQ(EXTI3_IRQn); 
}

