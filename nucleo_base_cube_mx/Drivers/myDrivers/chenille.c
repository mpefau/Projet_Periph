#include "chenille.h"
#include "main.h"
#include "stm32f1xx_hal.h"
#include "gpio.h"


// definition des variables 
extern	TIM_HandleTypeDef HTim3; 
extern	TIM_HandleTypeDef HTim1; 
extern	GPIO_InitTypeDef GPIOAPB0_Init;	//IB chenille gauche
extern	GPIO_InitTypeDef GPIOAPA10_Init; //IA chenille gauche
extern	GPIO_InitTypeDef GPIOAPA9_Init;	//IA chenille droite
extern	GPIO_InitTypeDef GPIOAPA8_Init; //IB chenille droite
extern	TIM_OC_InitTypeDef OcTIM1CH1;
extern	TIM_OC_InitTypeDef OcTIM1CH2;
extern	TIM_OC_InitTypeDef OcTIM1CH3;
extern	TIM_OC_InitTypeDef OcTIM3CH3;



void InitChenille(void){
	InitGpioChenille();
	initTimerChenille();
}

void InitGpioChenille(void){
	
	__HAL_RCC_GPIOA_CLK_ENABLE(); //activation de l'horloge du GPIOA
	__HAL_RCC_GPIOB_CLK_ENABLE(); //activation de l'horloge du GPIOB


	//Conf GPIO PA8 IA chenille droite
	GPIOAPA8_Init.Pin = GPIO_PIN_8;
	GPIOAPA8_Init.Mode = GPIO_MODE_AF_PP ;
	GPIOAPA8_Init.Pull = GPIO_NOPULL;
	GPIOAPA8_Init.Speed = GPIO_SPEED_MEDIUM;
	HAL_GPIO_Init(GPIOA, &GPIOAPA8_Init);
	
		//Conf GPIO PA9 IB chenille droite
	GPIOAPA9_Init.Pin = GPIO_PIN_9;
	GPIOAPA9_Init.Mode = GPIO_MODE_AF_PP ;
	GPIOAPA9_Init.Pull = GPIO_NOPULL;
	GPIOAPA9_Init.Speed = GPIO_SPEED_MEDIUM;
	HAL_GPIO_Init(GPIOA, &GPIOAPA9_Init);
	
		//Conf GPIO PA10 IA chenille gauche
	GPIOAPA10_Init.Pin = GPIO_PIN_10;
	GPIOAPA10_Init.Mode = GPIO_MODE_AF_PP ;
	GPIOAPA10_Init.Pull = GPIO_NOPULL;
	GPIOAPA10_Init.Speed = GPIO_SPEED_MEDIUM;
	HAL_GPIO_Init(GPIOA, &GPIOAPA10_Init);
	
		//Conf GPIO PA3 IB chenille gauche
	GPIOAPB0_Init.Pin = GPIO_PIN_0;
	GPIOAPB0_Init.Mode = GPIO_MODE_AF_PP ;
	GPIOAPB0_Init.Pull = GPIO_NOPULL;
	GPIOAPB0_Init.Speed = GPIO_SPEED_MEDIUM;
	HAL_GPIO_Init(GPIOB, &GPIOAPB0_Init);
}

void initTimerChenille (void){
	
	//definition des variables parametrant les timers
	int Fsorti = 50; //frequence voulu entre chaque reload a la sortie du timer
	int autoreload = 8999;
	int prescalerDiv = SystemCoreClock/(Fsorti * (autoreload+1)) - 1; //PSC = 159
	float rapportCyclique = 0.50;
	float compareValue = (autoreload + 1) * rapportCyclique - 1; //ici 674
	
	
	//Activation des horloges
	__HAL_RCC_TIM1_CLK_ENABLE(); 	// Activation de l'horloge du timer 1
	__HAL_RCC_TIM3_CLK_ENABLE();	// Activation de l'horloge du timer 3
	
	//Parametrage des Timers en PWM
		//timer1
	HTim1.Instance = TIM1;
	HTim1.Init.Prescaler = prescalerDiv;
	HTim1.Init.Period = autoreload;
	HTim1.Init.CounterMode = TIM_COUNTERMODE_UP;
		//timer3
	HTim3.Instance = TIM3;
	HTim3.Init.Prescaler = prescalerDiv;
	HTim3.Init.Period = autoreload;
	HTim3.Init.CounterMode = TIM_COUNTERMODE_UP;
	
	//affectation des rapports cyclique pour la pwm
		//marche avant
	OcTIM1CH1.OCMode = TIM_OCMODE_PWM1;		//IB chenille droite
	OcTIM1CH1.Pulse= (int) compareValue ;
	OcTIM1CH3.OCMode = TIM_OCMODE_PWM1; 	//IA chenille gauche
	OcTIM1CH3.Pulse= (int) compareValue ;
		//marche arrière
	OcTIM1CH2.OCMode = TIM_OCMODE_PWM1;		//IA chenille droite
	OcTIM1CH2.Pulse= (int) 0;
	OcTIM3CH3.OCMode = TIM_OCMODE_PWM1; 	//IB chenille gauche
	OcTIM3CH3.Pulse= (int) 0;
	
	HAL_TIM_PWM_MspInit(& HTim1); //Configuration du mode du timer en PWM
	HAL_TIM_PWM_Init(&HTim1);
	HAL_TIM_PWM_MspInit(& HTim3); //Configuration du mode du timer en PWM
	HAL_TIM_PWM_Init(&HTim3);
	
	
	//application des configuration pour les différents channel en PWM
	HAL_TIM_PWM_ConfigChannel(&HTim1, &OcTIM1CH1 ,TIM_CHANNEL_1);
	HAL_TIM_PWM_ConfigChannel(&HTim1, &OcTIM1CH2 ,TIM_CHANNEL_2);
	HAL_TIM_PWM_ConfigChannel(&HTim1, &OcTIM1CH3 ,TIM_CHANNEL_3);
	HAL_TIM_PWM_ConfigChannel(&HTim3, &OcTIM3CH3 ,TIM_CHANNEL_3);
	
	
	//lancement des timers
	HAL_TIM_PWM_Start_IT(& HTim1,TIM_CHANNEL_1);
	HAL_TIM_PWM_Start_IT(& HTim1,TIM_CHANNEL_2);
	HAL_TIM_PWM_Start_IT(& HTim1,TIM_CHANNEL_3);
	HAL_TIM_PWM_Start_IT(& HTim3,TIM_CHANNEL_3);
}


void SetVitesseChenille(int speed){
	
	int Fsorti = 50; //frequence voulu entre chaque reload a la sortie du timer
	int autoreload = 8999;
	int prescalerDiv = SystemCoreClock/(Fsorti * (autoreload+1)) - 1; //PSC = 159
	float rapportCyclique = 0.50;
	float compareValue = (autoreload + 1) * rapportCyclique - 1; //ici 674
	
}