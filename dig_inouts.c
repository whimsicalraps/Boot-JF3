#include "dig_inouts.h"
//#include "globals.h"
#include "debug.h"

extern __IO uint16_t adc_buffer[NUM_ADCS];

uint8_t check_run(void);

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

	// RUN: OUT SIG -> use an #ifdef v2
		RCC_AHB1PeriphClockCmd(RS_RCC, ENABLE);
		gpio.GPIO_Mode = GPIO_Mode_OUT;
		gpio.GPIO_OType = GPIO_OType_PP;
		gpio.GPIO_PuPd = GPIO_PuPd_NOPULL;
		gpio.GPIO_Pin = RUN_SIG_pin;
		GPIO_Init(RS_GPIO, &gpio);
}

void deinit_inouts(void){
	GPIO_DeInit(RS_GPIO);
	GPIO_DeInit(TR_GPIO);
	GPIO_DeInit(MODE_GPIO);
	RCC_AHB1PeriphClockCmd(TR_RCC, DISABLE);
	RCC_AHB1PeriphClockCmd(MODE_RCC, DISABLE);
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

	out += check_run();
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
	// USART_putn8(USART1, out);
	return out;
}

uint8_t check_run(void)
{
	uint8_t expected = 0;
	uint8_t match_count = 0;
	uint8_t high_count = 0;

	for( uint8_t i=0; i<16; i++ ){
		expected ^= 1;
		(expected)
		    ? GPIO_SetBits( RS_GPIO, RUN_SIG_pin )
		    : GPIO_ResetBits( RS_GPIO, RUN_SIG_pin );
		
		volatile uint32_t delay_count = 20;
		while( delay_count ){ delay_count--; }

		uint8_t now = GPIO_ReadInputDataBit( MODE_GPIO, RUN_MODE_pin );

		high_count  += now; // how many high readings

		match_count += !(expected ^ now); // how many flipped matches

	}
	//USART_putn8(USART1, match_count); // 8
	//USART_putn8(USART1, high_count);  // 0

	if( match_count >= 0x0A ){
		// V2 hardware. no run present
		return 0;
	}
	if( high_count >= 0x0A){
		// V1 hardware. no run present
		return 0;
	}
	return 1; // hw version unknown, but RUN is present
}
