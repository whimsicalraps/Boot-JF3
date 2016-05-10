#include <stm32f4xx.h>

#include "debug.h"

void USART_Config(uint32_t baudrate){
  
  GPIO_InitTypeDef GPIO_InitStruct; // this is for the GPIO pins used as TX and RX
  USART_InitTypeDef USART_InitStruct; // this is for the USART1 initilization
  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
  
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
  
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9| GPIO_Pin_10; // Pins 9 (TX), Pin 10 (RX)
    // yellow goes to PA10 (TX on dongle)
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;       // the pins are configured as alternate function so the USART peripheral has access to them
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;    // this defines the IO speed and has nothing to do with the baudrate!
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;     // this defines the output type as push pull mode (as opposed to open drain)
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;     // this activates the pullup resistors on the IO pins
  GPIO_Init(GPIOA, &GPIO_InitStruct);         // now all the values are passed to the GPIO_Init() function which sets the GPIO registers
  
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1); //
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1); //
  
  USART_InitStruct.USART_BaudRate = baudrate;       // the baudrate is set to the value we passed into this init function
  USART_InitStruct.USART_WordLength = USART_WordLength_8b;// we want the data frame size to be 8 bits (standard)
  USART_InitStruct.USART_StopBits = USART_StopBits_1;   // we want 1 stop bit (standard)
  USART_InitStruct.USART_Parity = USART_Parity_No;    // we don't want a parity bit (standard)
  USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // we don't want flow control (standard)
  USART_InitStruct.USART_Mode = USART_Mode_Tx;      // we want to enable the transmitter
  USART_Init(USART1, &USART_InitStruct);          // again all the properties are passed to the USART_Init function which takes care of all the bit setting

  USART_Cmd(USART1, ENABLE);
}

/* Note: The string has to be passed to the function as a pointer because
 *     the compiler doesn't know the 'string' data type. In standard
 *     C a string is just an array of characters
 * 
 * Note 2: At the moment it takes a volatile char because the received_string variable
 *       declared as volatile char --> otherwise the compiler will spit out warnings
 * */
void USART_putc(USART_TypeDef* USARTx, unsigned char c){
  // wait until data register is empty
  while( !(USARTx->SR & 0x00000040) ); 
  USART_SendData(USARTx, c);
}

void USART_puts(USART_TypeDef* USARTx,  char *s){
  while(*s){
    USART_putc(USARTx, *s);
    s++;
  }
}

void USART_putn(USART_TypeDef* USARTx, uint32_t n){
  uint8_t temp;
  int8_t i;
  
  USART_puts(USARTx, "\n\r0x"); // format for hex

  for(i=7;i>=0;i--) { // process 8 nibbles (count from high to low)
    temp = n >> (i<<2); // shift right by 4*i bits
    temp &= 0x0000000F; // mask for only lowest nibble

    if(temp<10) { // numeric
      USART_putc(USARTx, (char)48+temp); // format for hex    
    } else { // alpha
      USART_putc(USARTx, (char)55+temp); // format for hex
    }
  }
}

void USART_putn16(USART_TypeDef* USARTx, uint16_t n){
  uint8_t temp;
  int8_t i;
  
  USART_puts(USARTx, "\n\r0x"); // format for hex

  for(i=3;i>=0;i--) { // process 4 nibbles (count from high to low)
    temp = n >> (i<<2); // shift right by 4*i bits (ie nibble)
    temp &= 0x000F; // mask for only lowest nibble

    if(temp<10) { // numeric
      USART_putc(USARTx, (char)48+temp); // format for hex    
    } else { // alpha
      USART_putc(USARTx, (char)55+temp); // format for hex
    }
  }
}

void USART_putn8(USART_TypeDef* USARTx, uint8_t n){
  uint8_t temp;
  int8_t i;
  
  USART_puts(USARTx, "\n\r"); // format for hex

  for(i=1;i>=0;i--) { // process 2 nibbles (count from high to low)
    temp = n >> (i<<2); // shift right by 4*i bits (ie. nibble)
    temp &= 0x0F; // mask for only lowest nibble

    if(temp<10) { // numeric
      USART_putc(USARTx, (char)48+temp); // format for hex    
    } else { // alpha
      USART_putc(USARTx, (char)55+temp); // format for hex
    }
  }
}