/*
 * inouts.c - sets up inputs and outputs
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

#include "inouts.h"

void init_inouts(void){
	GPIO_InitTypeDef gpio;


	//Slider LEDs and Lock button LEDs as outputs:
	RCC_AHB1PeriphClockCmd(LED_SLIDER_RCC, ENABLE);

	GPIO_StructInit(&gpio);
	gpio.GPIO_Mode = GPIO_Mode_OUT;
	gpio.GPIO_Speed = GPIO_Speed_2MHz;
	gpio.GPIO_OType = GPIO_OType_PP;
	gpio.GPIO_PuPd = GPIO_PuPd_NOPULL;

	gpio.GPIO_Pin = LED_SLIDER1 | LED_SLIDER2 | LED_SLIDER3 | LED_SLIDER4  | LED_SLIDER5 | LED_SLIDER6 ;
	GPIO_Init(LED_SLIDER_GPIO, &gpio);


	RCC_AHB1PeriphClockCmd(LED_RCC, ENABLE);
	gpio.GPIO_Pin = LED_LOCK1 | LED_LOCK2 | LED_LOCK3 | LED_LOCK4 | LED_LOCK5 | LED_LOCK6;
	GPIO_Init(LED_GPIO, &gpio);

	gpio.GPIO_Pin = LED_RING_OE ;
	GPIO_Init(LED_GPIO, &gpio);


	RCC_AHB1PeriphClockCmd(LOCKJACK_RCC, ENABLE);
	gpio.GPIO_Pin = LOCKJACK_pin;
	GPIO_Init(LOCKJACK_GPIO, &gpio);


	//Rotary encoder switch (button) as input:

	RCC_AHB1PeriphClockCmd(ROTARY_RCC, ENABLE);

	gpio.GPIO_Mode = GPIO_Mode_IN;
	gpio.GPIO_Speed = GPIO_Speed_2MHz;
	gpio.GPIO_PuPd = GPIO_PuPd_UP;
	gpio.GPIO_Pin = ROTARY_SW_pin;
	GPIO_Init(ROTARY_GPIO, &gpio);


	//Lock buttons as inputs

	RCC_AHB1PeriphClockCmd(LOCKBUT_RCC, ENABLE);

	gpio.GPIO_Pin = LOCK1_pin | LOCK2_pin | LOCK3_pin | LOCK4_pin | LOCK5_pin;
	GPIO_Init(LOCKBUT_GPIO, &gpio);

	gpio.GPIO_Pin = LOCK6_pin;
	GPIO_Init(LOCKBUT6_GPIO, &gpio);

	//Rotate Up jack input

	RCC_AHB1PeriphClockCmd(ROT_RCC, ENABLE);

	gpio.GPIO_PuPd = GPIO_PuPd_DOWN;
	gpio.GPIO_Pin = ROTUP_pin;
	GPIO_Init(ROTUP_GPIO, &gpio);


}



const int _lockbutton[6]={LOCK1_pin, LOCK2_pin, LOCK3_pin, LOCK4_pin, LOCK5_pin, LOCK6_pin};
inline uint8_t LOCKBUTTON(uint8_t x){
	if (x!=5) return (!(LOCKBUT_GPIO->IDR & _lockbutton[x]));
	else return (!(LOCKBUT6_GPIO->IDR & _lockbutton[5]));
}

