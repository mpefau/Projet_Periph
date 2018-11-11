//ce driver permet de gérer le bouton exterieur de la boite 


#ifndef BOUTON_C
#define BOUTON_C


#include "stm32f1xx_hal.h"
#include "gpio.h"

extern GPIO_InitTypeDef GPIOBPB3_Init;

// Bouton sur PB3
void initBouton (void);




#endif
