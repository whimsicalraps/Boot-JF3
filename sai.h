#ifndef __sai__
#define __sai__

#include <stm32f4xx.h>
#include "codec.h"



/* PLLI2S_VCO = (HSE_VALUE Or HSI_VALUE / PLL_M) * PLLI2S_N
   I2SCLK = PLLI2S_VCO / PLLI2S_R */
#define PLLI2S_N   344
//#define PLLI2S_R   2 // 4ms uses /2 then some other divisor later for 96k?
#define PLLI2S_R   7

#define Block_Size 8
// Use these two to define Buffer sizes, rather than hard-setting bytes
 // This allows Block Size to be changed easily
 // 16 & 8x multipliers are appropriate for the amount of input data
#define codec_RX_Block (Block_Size * 4) // 4 adc samples per frame
#define codec_TX_Block (Block_Size * 7) // 7 dac samples per frame


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

