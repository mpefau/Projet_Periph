#include "Servo.h"

void initServos(TIM_HandleTypeDef * Handle) {

	// Rapport cyclique correspondant à la position 0 du servo d'ouverture de la boite
	float rapport_cyclique_ouverture = 0.036;
	
	// Rapport cyclique correspondant à la position 0 du servo patte
	float rapport_cyclique_patte = 0.024;
	
	__HAL_RCC_TIM2_CLK_ENABLE();
	
	// Initialiser le pin PA0 en alternate PP output
	GPIO_InitTypeDef GPIO_PA0;
	GPIO_PA0.Pin = GPIO_PIN_0;
  GPIO_PA0.Mode = GPIO_MODE_AF_PP;
	GPIO_PA0.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_PA0);
	
	// Initialiser le pin PA1 en alternate PP output
	GPIO_InitTypeDef GPIO_PA1;
	GPIO_PA1.Pin = GPIO_PIN_1;
  GPIO_PA1.Mode = GPIO_MODE_AF_PP;
	GPIO_PA1.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_PA1);
	
	// Initialisation du timer en mode PWM
	HAL_TIM_PWM_Init(Handle);
	
	// Creation d'un TIM_OC_InitTypeDef pour configurer la PWM
	initPWM_ouverture.OCMode = TIM_OCMODE_PWM1;
	initPWM_ouverture.Pulse = (int)(rapport_cyclique_ouverture*Handle->Init.Period);
	
	// Creation d'un TIM_OC_InitTypeDef pour configurer la PWM
	initPWM_patte.OCMode = TIM_OCMODE_PWM1;
	initPWM_patte.Pulse = (int)(rapport_cyclique_patte*Handle->Init.Period);

	// Configuration des channels des 2 servos
	HAL_TIM_PWM_ConfigChannel(Handle,&initPWM_ouverture,TIM_CHANNEL_1);
	HAL_TIM_PWM_ConfigChannel(Handle,&initPWM_patte,TIM_CHANNEL_2);

	// Demarrage de la PWM
	HAL_TIM_PWM_Start(Handle,TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(Handle,TIM_CHANNEL_2);
}

void ouvrirBoite (float rapport_cyclique) {
	
	// Creation d'un TIM_OC_InitTypeDef pour configurer la PWM
	initPWM_ouverture.Pulse = (int)(rapport_cyclique*HandleTIM2.Init.Period);

	// Configuration des channels des 2 servos
	HAL_TIM_PWM_ConfigChannel(&HandleTIM2,&initPWM_ouverture,TIM_CHANNEL_1);

	// Demarrage de la PWM
	HAL_TIM_PWM_Start(&HandleTIM2,TIM_CHANNEL_1);
}