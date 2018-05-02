#ifndef __codec__
#define __codec__

#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
//#include "stm32f4xx_spi.h"
#include "stm32f4xx_rcc.h"

/*-----------------------------------
Hardware Configuration defines parameters
-----------------------------------------*/                 

// SPI peripheral
#define CODEC_SPI_GPIO_CLOCK           RCC_AHB1Periph_GPIOD
#define CODEC_SPI_GPIO 				   GPIOD
#define CODEC_NSS_PIN				   GPIO_Pin_4
#define CODEC_SCK_PIN 				   GPIO_Pin_5
#define CODEC_MOSI_PIN 				   GPIO_Pin_6
#define CODEC_RESET_PIN				   GPIO_Pin_7

/* I2S peripheral configuration defines */
#define CODEC_I2S                      SPI2
#define CODEC_I2S_EXT                  I2S2ext
#define CODEC_I2S_CLK                  RCC_APB1Periph_SPI2
#define CODEC_I2S_ADDRESS              0x4000380C
#define CODEC_I2S_EXT_ADDRESS          0x4000340C
#define CODEC_I2S_GPIO_AF              GPIO_AF_SPI2
#define CODEC_I2S_IRQ                  SPI2_IRQn
#define CODEC_I2S_EXT_IRQ              SPI2_IRQn
//#define CODEC_I2S_GPIO_CLOCK           (RCC_AHB1Periph_GPIOC | RCC_AHB1Periph_GPIOB)
#define CODEC_I2S_WS_PINSRC            GPIO_PinSource12
#define CODEC_I2S_SCK_PINSRC           GPIO_PinSource13
#define CODEC_I2S_SDI_PINSRC           GPIO_PinSource14
#define CODEC_I2S_SDO_PINSRC           GPIO_PinSource15
#define CODEC_I2S_MCK_PINSRC           GPIO_PinSource6
//#define CODEC_I2S_MCK_GPIO             GPIOC
#define AUDIO_I2S_IRQHandler           SPI2_IRQHandler
#define AUDIO_I2S_EXT_IRQHandler       SPI2_IRQHandler


/*----------------------------------------------------------------------------*/

/* High Layer codec functions */
void Codec_Init(void);
void Codec_GPIO_deInit(void);

/* Low layer codec functions */
//void     Codec_CtrlInterface_Init(void);
//void     Codec_AudioInterface_Init(uint32_t AudioFreq);
//uint32_t     Codec_Reset(void);
//uint32_t Codec_WriteRegister(uint8_t RegisterAddr, uint16_t RegisterValue);
//void init_i2s_clkin(void);

#endif
