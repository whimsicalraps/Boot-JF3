/*
 * inouts.h - sets up inputs and outputs
 *
 * Copyright 2015 Dan Green
 *
 * Author: Dan Green (danngreen1@gmail.com)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 * See http://creativecommons.org/licenses/MIT/ for more information.
 *
 * -----------------------------------------------------------------------------
 */
#ifndef INOUTS_H_
#define INOUTS_H_

#include "stm32f4xx.h"

#define ROTARY_GPIO GPIOD
#define ROTARY_RCC RCC_AHB1Periph_GPIOD

#define ROTARY_SW_pin GPIO_Pin_9
#define ROTARY_SW (!(ROTARY_GPIO->IDR & ROTARY_SW_pin))

#define LOCKBUT_RCC (RCC_AHB1Periph_GPIOD | RCC_AHB1Periph_GPIOG)

#define LOCK1_pin GPIO_Pin_12
#define LOCK2_pin GPIO_Pin_0
#define LOCK3_pin GPIO_Pin_1
#define LOCK4_pin GPIO_Pin_2
#define LOCK5_pin GPIO_Pin_3
#define LOCKBUT_GPIO GPIOD

#define LOCKBUT6_GPIO GPIOG
#define LOCK6_pin GPIO_Pin_15


#define LED_SLIDER_RCC RCC_AHB1Periph_GPIOG
#define LED_SLIDER_GPIO GPIOG
#define LED_SLIDER_OFF(x) LED_SLIDER_GPIO->BSRRH = x
#define LED_SLIDER_ON(x) LED_SLIDER_GPIO->BSRRL = x

#define LED_SLIDER1 GPIO_Pin_9
#define LED_SLIDER2 GPIO_Pin_10
#define LED_SLIDER3 GPIO_Pin_11
#define LED_SLIDER4 GPIO_Pin_12
#define LED_SLIDER5 GPIO_Pin_13
#define LED_SLIDER6 GPIO_Pin_14

#define LED_RING_OE GPIO_Pin_4

#define LED_RCC RCC_AHB1Periph_GPIOE
#define LED_GPIO GPIOE
#define LED_OFF(x) LED_GPIO->BSRRH = x
#define LED_ON(x) LED_GPIO->BSRRL = x

#define LED_LOCK1 GPIO_Pin_5
#define LED_LOCK2 GPIO_Pin_0
#define LED_LOCK3 GPIO_Pin_1
#define LED_LOCK4 GPIO_Pin_2
#define LED_LOCK5 GPIO_Pin_3
#define LED_LOCK6 GPIO_Pin_6

#define ROT_RCC RCC_AHB1Periph_GPIOC

#define ROTUP_pin GPIO_Pin_15
#define ROTUP_GPIO GPIOC
#define ROTUP (ROTUP_GPIO->IDR & ROTUP_pin)

#define LOCKJACK_pin GPIO_Pin_7
#define LOCKJACK_GPIO GPIOB
#define LOCKJACK_RCC RCC_AHB1Periph_GPIOB

#define LOCKJACK_OFF LOCKJACK_GPIO->BSRRH = LOCKJACK_pin
#define LOCKJACK_ON LOCKJACK_GPIO->BSRRL = LOCKJACK_pin


void init_inouts(void);


#endif /* INOUTS_H_ */
