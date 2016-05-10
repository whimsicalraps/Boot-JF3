#ifndef INOUTS_H_
#define INOUTS_H_

#include <stm32f4xx.h>


// HARDWARE PERIPHERAL CLOCK FOR SWITCHES
#define MODE_RCC (RCC_AHB1Periph_GPIOD)
#define MODE_GPIO GPIOD

	// RUN SENSE
#define RUN_MODE_pin GPIO_Pin_8
#define RUN_MODE ((MODE_GPIO->IDR & RUN_MODE_pin))

	// TRANSIENT / SUSTAIN / CYCLE MODE
#define TRANS_MODE_pin GPIO_Pin_9
#define TRANS_MODE ((MODE_GPIO->IDR & TRANS_MODE_pin))
#define CYCLE_MODE_pin GPIO_Pin_10
#define CYCLE_MODE ((MODE_GPIO->IDR & CYCLE_MODE_pin))

	// SPEED SETTING
#define SPEED_MODE_pin GPIO_Pin_11
#define SPEED_MODE ((MODE_GPIO->IDR & SPEED_MODE_pin))



// HARDWARE PERIPHERAL CLOCK FOR TRIGGER INPUTS
#define TR_RCC (RCC_AHB1Periph_GPIOC)
#define TR_GPIO GPIOC

#define TR_1_pin GPIO_Pin_6
#define TR_2_pin GPIO_Pin_7
#define TR_3_pin GPIO_Pin_8
#define TR_4_pin GPIO_Pin_9
#define TR_5_pin GPIO_Pin_10
#define TR_6_pin GPIO_Pin_11

// ADC
#define ADC_GPIO GPIOA

#define NUM_ADCS 7

#define TIME_POT 0
#define INTONE_POT 1
#define RAMP_POT 2
#define INTONE_CV 3
#define TIME_CV 4
#define FM_POT 5
#define CURVE_POT 6


// SAI PINS
#define SAI_RCC RCC_AHB1Periph_GPIOE
#define SAI_GPIO GPIOE
#define SAI_MCLK_pin GPIO_Pin_2
#define SAI_SD_B_pin GPIO_Pin_3
#define SAI_FS_pin GPIO_Pin_4
#define SAI_SCK_pin GPIO_Pin_5
#define SAI_SD_A_pin GPIO_Pin_6


void init_inouts(void);
uint8_t read_speed(void);
uint8_t check_boot(void);
// uint8_t check_boot_verbose(void);

#endif /* INOUTS_H_ */