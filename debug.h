#ifndef DEBUG_H_
#define DEBUG_H_

#include <stm32f4xx.h>

void USART_Config(uint32_t baudrate);
void USART_deinit(void);

void USART_putc(USART_TypeDef* USARTx, unsigned char c);
void USART_puts(USART_TypeDef* USARTx,  char *s);
void USART_putn(USART_TypeDef* USARTx, uint32_t n);
void USART_putn16(USART_TypeDef* USARTx, uint16_t n);
void USART_putn8(USART_TypeDef* USARTx, uint8_t n);


#endif /* DEBUG_H_ */
