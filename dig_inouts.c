#include "dig_inouts.h"
//#include "globals.h"
#include "debug.h"

extern __IO uint16_t adc_buffer[NUM_ADCS];

void init_inouts(void){
	GPIO_InitTypeDef gpio;

	// Set up Inputs:
	// Enable switch input clock
	RCC_AHB1PeriphClockCmd(MODE_RCC, ENABLE);
	// Enable trigger input clock
	RCC_AHB1PeriphClockCmd(TR_RCC, ENABLE);


	// Initialize Struct
	GPIO_StructInit(&gpio);
	gpio.GPIO_Mode = GPIO_Mode_IN;
	gpio.GPIO_Speed = GPIO_Speed_2MHz;
	gpio.GPIO_PuPd = GPIO_PuPd_UP;

	// Init SWITCH pins
	gpio.GPIO_Pin = TRANS_MODE_pin | CYCLE_MODE_pin | SPEED_MODE_pin;
	GPIO_Init(MODE_GPIO, &gpio);

	// Init RUN pin (no pullup due to always active state)
	gpio.GPIO_PuPd = GPIO_PuPd_NOPULL;
	gpio.GPIO_Pin = RUN_MODE_pin;
	GPIO_Init(MODE_GPIO, &gpio);

	// Init Trigger pins (still no pullup as transistor buffered)
	gpio.GPIO_Pin = TR_1_pin | TR_2_pin | TR_3_pin | TR_4_pin | TR_5_pin | TR_6_pin;
	GPIO_Init(TR_GPIO, &gpio);
}

uint8_t read_speed(void){
	uint8_t out;

	if(SPEED_MODE){
		out = 1;
	} else {
		out = 0;
	}
	return out;
}

uint8_t check_boot(void){
	// require following conditions to load into bootloader
		// RUN jack present
		// sound mode
		// cycle mode
		// All pots @maximum (>4000?)
	static uint8_t out = 0;

	out = 0;

	// param_read_switches();

	out += !RUN_MODE;
	out += (SPEED_MODE > 0);
	out += !TRANS_MODE;

	out += (adc_buffer[TIME_POT] <= 50);
	out += (adc_buffer[INTONE_POT] <= 50);
	out += (adc_buffer[RAMP_POT] <= 50);
	out += (adc_buffer[FM_POT] <= 50);
	out += (adc_buffer[CURVE_POT] <= 50);

	// only return '1' if all 8 states match
	if(out > 7) {
		out = 1;
	} else {
		out = 0;
	}
	return out;
}
/*
uint8_t check_boot_verbose(void){
	// require following conditions to load into bootloader
		// RUN jack present
		// sound mode
		// cycle mode
		// All pots @maximum (>4000?)
	static uint8_t out = 0;

	out = 0;

	// param_read_switches();

	out += !RUN_MODE;
	USART_putn8(USART1, out);
	out += (SPEED_MODE > 0);
	USART_putn8(USART1, out);
	out += !TRANS_MODE;
	USART_putn8(USART1, out);

	out += (adc_buffer[TIME_POT] <= 500);
	USART_putn8(USART1, out);
	out += (adc_buffer[INTONE_POT] <= 500);
	USART_putn8(USART1, out);
	out += (adc_buffer[RAMP_POT] <= 500);
	USART_putn8(USART1, out);
	out += (adc_buffer[FM_POT] <= 500);
	USART_putn8(USART1, out);
	out += (adc_buffer[CURVE_POT] <= 500);
	USART_putn8(USART1, out);

	// only return '1' if all 8 states match
	if(out > 7) {
		out = 1;
	} else {
		out = 0;
	}
	return out;
}*/