#include "Servo.h"

// Initialise les servomoteurs de la boite.
// Servo permettant d'ouvrir la boîte : pin A0
// Servo permettant d'appuyer sur le bouon à l'aide d'une patte : pin A1
//
void initServos() {
	
		// Initialisation de TIM2 avec une periode de 20 ms
	__HAL_RCC_TIM2_CLK_ENABLE();
	HandleTIM2.Instance = TIM2;

	HandleTIM2.Init.Prescaler = PSC_20MS; // 0x0063
	HandleTIM2.Init.Period = ARR_20MS; // 0x383F
	
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
	HAL_TIM_PWM_Init(&HandleTIM2);
	
	// Creation d'un TIM_OC_InitTypeDef pour configurer la PWM
	initPWM_ouverture.OCMode = TIM_OCMODE_PWM1;
	
	// Creation d'un TIM_OC_InitTypeDef pour configurer la PWM
	initPWM_patte.OCMode = TIM_OCMODE_PWM1;

	// Mettre les servos en position initiale
	bouger_couvercle(RC_FERMETURE_BOITE);
	bouger_patte(RC_PATTE_RENTREE);
}

// Fait tourner le servo qui ouvre/ferme la boite
// Peut être appelée avec RC_OUVERTURE_BOITE ou RC_FERMETURE_BOITE 
// pour ouvrir ou fermer la boîte.
void bouger_couvercle (float rapport_cyclique) {
	
	// Creation d'un TIM_OC_InitTypeDef pour configurer la PWM
	initPWM_ouverture.Pulse = (int)(rapport_cyclique*HandleTIM2.Init.Period);

	// Configuration des channels des 2 servos
	HAL_TIM_PWM_ConfigChannel(&HandleTIM2,&initPWM_ouverture,TIM_CHANNEL_1);

	// Demarrage de la PWM
	HAL_TIM_PWM_Start(&HandleTIM2,TIM_CHANNEL_1);
	
}

// Fait tourner le servo qui rentre/sort la patte
// Peut être appelée avec RC_PATTE_RENTREE ou RC_PATTE_SORTIE
// pour rentrer ou sortir la patte.
void bouger_patte(float rapport_cyclique) {
	
	// Creation d'un TIM_OC_InitTypeDef pour configurer la PWM
	initPWM_patte.Pulse = (int)(rapport_cyclique*HandleTIM2.Init.Period);

	// Configuration des channels des 2 servos
	HAL_TIM_PWM_ConfigChannel(&HandleTIM2,&initPWM_patte,TIM_CHANNEL_2);

	// Demarrage de la PWM
	HAL_TIM_PWM_Start(&HandleTIM2,TIM_CHANNEL_2);
	
}