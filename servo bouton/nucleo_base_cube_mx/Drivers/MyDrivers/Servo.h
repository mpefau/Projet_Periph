#ifndef SERVO
#define SERVO

#include "stm32f1xx_hal.h"
#include "gpio.h"
#include "main.h"
#include "stm32f1xx.h"

#define ARR_20MS 14399
#define PSC_20MS 99

// Rapports cyclique des différentes commandes PWM des servos
//1312 pour appuyer sur le bouton et 341 pour etre dans la boite
//
#define RC_FERMETURE_BOITE 0.036
#define RC_OUVERTURE_BOITE 0.075
#define RC_PATTE_RENTREE 0.0234
#define RC_PATTE_SORTIE 0.091

	extern TIM_HandleTypeDef HandleTIM2;
	extern TIM_OC_InitTypeDef initPWM_patte;
	extern TIM_OC_InitTypeDef initPWM_ouverture;

// Initialise les servomoteurs de la boite.
// Servo permettant d'ouvrir la boîte : pin A0
// Servo permettant d'appuyer sur le bouon à l'aide d'une patte : pin A1
void initServos();

// Fait tourner le servo qui ouvre/ferme la boite
// Peut être appelée avec RC_OUVERTURE_BOITE ou RC_FERMETURE_BOITE 
// pour ouvrir ou fermer la boîte.
void bouger_couvercle(float rapport_cyclique);

// Fait tourner le servo qui rentre/sort la patte
// Peut être appelée avec RC_PATTE_RENTREE ou RC_PATTE_SORTIE
// pour rentrer ou sortir la patte.
void bouger_patte(float rapport_cyclique);


#endif