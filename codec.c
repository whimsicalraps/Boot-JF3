#include <stm32f4xx.h>
#include "codec.h"

void Codec_GPIO_Init(void);
void codec_bitbang(void);
void firstBit(void);
void bitB(uint16_t state);

/**
  * @brief  Inserts a delay time (not accurate timing).
  * @param  nCount: specifies the delay time length.
  * @retval None
  */
static void Delay( __IO uint32_t nCount)
{   for (; nCount != 0; nCount--);
}


void Codec_Init(void)
{
    Codec_GPIO_Init();   
    /* Configure the AD1938 peripheral */
    // Using manual bitbang due to no 24bit capable SPI peripheral
    codec_bitbang();
}

void Codec_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    /* Enable SPI GPIO clocks */
    RCC_AHB1PeriphClockCmd(CODEC_SPI_GPIO_CLOCK, ENABLE);

    /* CODEC_SPI pin configuration -------------------------------------*/
    GPIO_InitStructure.GPIO_Pin = CODEC_NSS_PIN | CODEC_SCK_PIN | CODEC_MOSI_PIN | CODEC_RESET_PIN; 
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // can we slow this down for lower current draw?
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
    GPIO_Init(CODEC_SPI_GPIO, &GPIO_InitStructure);
}


// OWN ROLLED SPI DRIVER
void codec_bitbang(){
 
    volatile uint16_t del;

    GPIO_SetBits(GPIOD, GPIO_Pin_7); //!RST HIGH therefore not in reset, running normally

    Delay(10000);

    GPIO_ResetBits(GPIOD, GPIO_Pin_6); // MOSI low
    GPIO_ResetBits(GPIOD, GPIO_Pin_5); // CCLK low


    GPIO_SetBits(GPIOD, GPIO_Pin_4); // CLATCH high
    Delay(1000);
    //NSS on D:4 (CLATCH)
    //SCK on D:5 (CCLK)
    //MOSI on D:6 (CIN)



    // 129: clock PLL from DLR and remove MCLK (turn off MCLK output in SAI too)
    // 179: DBCLK generated internally (no BCLK line required) lower noise
    // 253: ABCLK generated internally
    // 



    firstBit();
        // 00000000: Register Address 0 = PLL & Clock Control 0
    bitB(0);
    bitB(0);
    bitB(0);
    bitB(0);    
    bitB(0);
    bitB(0);
    bitB(0);
    bitB(0);
        // 10011000
    bitB(1);
    bitB(0);
/**/bitB(0); // change to 1 for DLRCLK as PLL clock source (lower noise than MCLK)
        // could then remove 
    bitB(1);
    bitB(1);
    bitB(0);
    bitB(0);
    bitB(0);
    // end of SPI frame
    GPIO_SetBits(GPIOD, GPIO_Pin_4); // CLATCH high
    Delay(1000);



    firstBit();
        // 00000010: Register Address 2 = DAC Control 0
    bitB(0);
    bitB(0);
    bitB(0);
    bitB(0);    
    bitB(0);
    bitB(0);
    bitB(1);
    bitB(0);
        // 01000000
    bitB(0);
    bitB(1);
    bitB(0);
    bitB(0);
    bitB(0);    
    bitB(0);
    bitB(0);
    bitB(0);
    // end of SPI frame
    GPIO_SetBits(GPIOD, GPIO_Pin_4); // CLATCH high
    Delay(1000);



    firstBit();
        // 00000011: Register Address 3 = DAC Control 1
    bitB(0);
    bitB(0);
    bitB(0);
    bitB(0);    
    bitB(0);
    bitB(0);
    bitB(1);
    bitB(1);
        // 00000100
    bitB(0);
/**/bitB(0); // set for DBCLK internal generation (no BCLK at all for lower noise)
    bitB(0);
    bitB(0);    
    bitB(0);
    bitB(1);
    bitB(0);
    bitB(0);
    // end of SPI frame
    GPIO_SetBits(GPIOD, GPIO_Pin_4); // CLATCH high
    Delay(1000);



    firstBit();
    // 00000100: Register Address 4 = DAC Control 2
    bitB(0);
    bitB(0);
    bitB(0);
    bitB(0);    
    bitB(0);
    bitB(1);
    bitB(0);
    bitB(0);
    // 00100000
    bitB(0);
    bitB(0);
    bitB(1); // inverted DAC output due to inverting opamp config
    bitB(0);
    bitB(0);
    bitB(0);
    bitB(0);
    bitB(0);
    // end of SPI frame
    GPIO_SetBits(GPIOD, GPIO_Pin_4); // CLATCH high
    Delay(1000);



    firstBit();
        // 00001111: Register Address 15 = ADC Control 1
    bitB(0);
    bitB(0);
    bitB(0);
    bitB(0);    
    bitB(1);
    bitB(1);
    bitB(1);
    bitB(1);
        // 00100000
    bitB(0);
    bitB(0);
    bitB(1);
    bitB(0);
    bitB(0);    
    bitB(0);
    bitB(0);
    bitB(0);
    // end of SPI frame
    GPIO_SetBits(GPIOD, GPIO_Pin_4); // CLATCH high
    Delay(1000);



    firstBit();
        // 00010000: Register Address 16 = ADC Control 2
    bitB(0);
    bitB(0);
    bitB(0);
    bitB(1);
    bitB(0);    
    bitB(0);
    bitB(0);
    bitB(0);
        // 00100000
/**/bitB(0); // set for internally generated ABCLK
    bitB(0);
    bitB(1);
    bitB(0);
    bitB(0);
    bitB(0);
    bitB(0);
    bitB(0);
    // end of SPI frame
    GPIO_SetBits(GPIOD, GPIO_Pin_4); // CLATCH high
}

void firstBit(void) {
    GPIO_ResetBits(GPIOD, GPIO_Pin_4); // CLATCH low
 // 00001000 Global Address. Last bit is 0 for write (setup)
    bitB(0);
    bitB(0);
    bitB(0);
    bitB(0);    
    bitB(1);
    bitB(0);
    bitB(0);
    bitB(0);
}

void bitB(uint16_t state) {
    if(state == 0) {
    GPIO_ResetBits(GPIOD, GPIO_Pin_6);
        Delay(10);
        GPIO_SetBits(GPIOD, GPIO_Pin_5); // CCLK HIGH
        Delay(10);
        GPIO_ResetBits(GPIOD, GPIO_Pin_5); // CCLK LOW
    } else {
        GPIO_SetBits(GPIOD, GPIO_Pin_6);
        Delay(10);
        GPIO_SetBits(GPIOD, GPIO_Pin_5); // CCLK HIGH
        Delay(10);
        GPIO_ResetBits(GPIOD, GPIO_Pin_5); // CCLK LOW

    }
}