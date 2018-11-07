#ifndef IR
#define IR

#include "stm32f1xx_hal.h"
#include "main.h"
#include "gpio.h"
#include "stm32f1xx.h"

// renvoi un ADC_HandleTypeDef de ADC1
ADC_HandleTypeDef newADC();

// renvoi un ADC_ChannelConfTypeDef avec les bonnes valeurs
ADC_ChannelConfTypeDef newChan(uint32_t channel, uint32_t rank, uint32_t sample_time);

// renvoi un timer rempli avec les paramètres
TIM_HandleTypeDef newTimer(TIM_TypeDef * TIM, int prescaler,int autoreload);

// configure le mode de fonctionnement du timer en TIM_Base et fait démarrer le timer
void startTimer(TIM_HandleTypeDef * timer);

#endif