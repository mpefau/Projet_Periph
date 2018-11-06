#ifndef IR
#define IR

#include "stm32f1xx_hal.h"

// renvoi un ADC_HandleTypeDef de ADC1
ADC_HandleTypeDef newADC();

// renvoi un channel 1 avec les bonnes valeurs
ADC_ChannelConfTypeDef newChan(uint32_t channel, uint32_t rank, uint32_t sample_time);

#endif