#ifndef __sai__
#define __sai__

#include <stm32f4xx.h>
#include "codec.h"



/* PLLI2S_VCO = (HSE_VALUE Or HSI_VALUE / PLL_M) * PLLI2S_N
   I2SCLK = PLLI2S_VCO / PLLI2S_R */
#define PLLI2S_N   344
//#define PLLI2S_R   2 // 4ms uses /2 then some other divisor later for 96k?
#define PLLI2S_R   7




// SAI PINS
#define SAI_RCC RCC_AHB1Periph_GPIOE
#define SAI_GPIO GPIOE
#define SAI_MCLK_pin GPIO_Pin_2
#define SAI_SD_B_pin GPIO_Pin_3
#define SAI_FS_pin GPIO_Pin_4
#define SAI_SCK_pin GPIO_Pin_5
#define SAI_SD_A_pin GPIO_Pin_6


 

void SAI_Block_Init(void);
// void climb_the_slopes(void);

#endif

