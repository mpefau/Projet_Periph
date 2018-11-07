#include "InfraRouge.h"

// renvoi un ADC_HandleTypeDef de ADC1
ADC_HandleTypeDef newADC() {
	
	ADC_HandleTypeDef new_adc;
	
	// Configuration de l'ADC
	__HAL_RCC_ADC_CONFIG(RCC_ADCPCLK2_DIV6);
	__ADC1_CLK_ENABLE();
	
	// Création d'une structure d'initialisation de ADC
	ADC_InitTypeDef initADC;
	initADC.DataAlign = ADC_DATAALIGN_RIGHT; // MSB sur le bit 11, LSB sur bit 0
	initADC.ScanConvMode = ADC_SCAN_DISABLE; // On est en mode single channel donc on lit juste le premier
	initADC.ContinuousConvMode = DISABLE; // Mode continuous desactivé
	initADC.NbrOfConversion = 1; // Nombre de channels à lire 
	initADC.DiscontinuousConvMode = ENABLE; // Mode discontinu activé
	initADC.NbrOfDiscConversion = 1;
	initADC.ExternalTrigConv = ADC_SOFTWARE_START; // ADC déclenché par le programme
	
	new_adc.Instance = ADC1;
	new_adc.Init = initADC;
	
	return new_adc;
}

// renvoi un channel 1 avec les bonnes valeurs
ADC_ChannelConfTypeDef newChan(uint32_t channel, uint32_t rank, uint32_t sampletime) {
	ADC_ChannelConfTypeDef new_chan;
	new_chan.Channel = channel;
	new_chan.Rank = rank;
	new_chan.SamplingTime = sampletime; // Nombre de cycle d'horloge par conversion
	
	return new_chan;
}

// renvoi un timer rempli avec les paramètres
TIM_HandleTypeDef newTimer(TIM_TypeDef * TIM, int prescaler,int autoreload) {
	
	TIM_HandleTypeDef new_timer;
	new_timer.Instance = TIM;
	new_timer.Init.Prescaler = prescaler;
	new_timer.Init.Period = autoreload;
	
	return new_timer;
}

void startTimer(TIM_HandleTypeDef * timer) {
	
	// Configuration de timer en Time Base
	HAL_TIM_Base_MspInit(timer);
	// Configuration du mode de fonctionnement de timer
	HAL_TIM_Base_Init(timer);
	// Demarrage de timer
	HAL_TIM_Base_Start(timer);
	
}