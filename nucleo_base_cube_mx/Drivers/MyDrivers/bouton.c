#include "stm32f10x.h"
#include "stm32f1xx_hal.h"
#include "bouton.h"
#include "gpio.h"



void initGPIO (GPIO_InitTypeDef GPIOPin){
	__HAL_RCC_GPIOB_CLK_ENABLE(); //activation de l'horloge du GPIOB
	
	HAL_GPIO_Init(GPIOB, &GPIOPin);
	
}

void initTimer2(void){
	extern TIM_HandleTypeDef HTim2;
	int Fsorti = 20; //frequence voulu entre chaque reload a la sortie du timer
	int autoreload = 9000;
	int prescalerDiv = SystemCoreClock/(Fsorti * (autoreload+1)) - 1;

	
	__HAL_RCC_TIM2_CLK_ENABLE(); // Activation de l'horloge du timer 
	
	//Conf Timer How to use This driver 41.2.2 (UM1850)
	HTim2.Instance = TIM2;
	HTim2.Init.Prescaler = prescalerDiv;
	HTim2.Init.Period = autoreload;
	HTim2.Init.CounterMode = TIM_COUNTERMODE_UP;

	HAL_TIM_Base_MspInit(& HTim2); //Configuration du mode du timer en Time Base
	HAL_TIM_Base_Init(& HTim2); //configure the TIM in the desired functionning mode
	HAL_NVIC_SetPriority(TIM2_IRQn, 2, 0); //configuration priorite de l'it
	HAL_NVIC_EnableIRQ(TIM2_IRQn); //autorisation de la demande d'interruption par le timer 2
	HAL_TIM_Base_Start_IT(& HTim2); //activation de l'interruption au niveau du timer

	HAL_TIM_Base_Start(& HTim2); //demarrage du TIM2
}

