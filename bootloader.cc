// Bootloader.cc
// Copyright 2012 Olivier Gillet.
//
// Author: Olivier Gillet (ol.gillet@gmail.com)
// Modified for SMR project: Dan Green (danngreen1@gmail.com) 2015

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
// See http://creativecommons.org/licenses/MIT/ for more information.

#include "stm32f4xx.h"

#include "system.h"

#include <cstring>

#include "../stmlib/dsp/dsp.h"
#include "../stmlib/utils/ring_buffer.h"
#include "../stmlib/system/bootloader_utils.h"
#include "../stmlib/system/flash_programming.h"
#include "../stmlib/system/system_clock.h"

//#include "../stm-audio-bootloader/qpsk/packet_decoder.h"
//#include "../stm-audio-bootloader/qpsk/demodulator.h"
#include "../stm_audio_bootloader/fsk/packet_decoder.h"
#include "../stm_audio_bootloader/fsk/demodulator.h"


extern "C" {
#include <stddef.h> /* size_t */
#include "dig_inouts.h"
#include "adc.h"
#include "debug.h"
#include "codec.h"
#include "sai.h"
// #include "pca9685_driver.h"

#define delay(x)						\
do {							\
  register unsigned int i;				\
  for (i = 0; i < x; ++i)				\
    __asm__ __volatile__ ("nop\n\t":::"memory");	\
} while (0)

}

#define MAX24f 8388607.0f

// const int LED_LOCK[6]={LED_LOCK1, LED_LOCK2, LED_LOCK3, LED_LOCK4, LED_LOCK5, LED_LOCK6};
// const uint32_t slider_led[6]={LED_SLIDER1, LED_SLIDER2, LED_SLIDER3, LED_SLIDER4, LED_SLIDER5, LED_SLIDER6};
// #define ALL_SLIDERS (LED_SLIDER1|LED_SLIDER2|LED_SLIDER3|LED_SLIDER4|LED_SLIDER5|LED_SLIDER6)
// #define ALL_LOCK_LEDS (LED_LOCK1| LED_LOCK2| LED_LOCK3| LED_LOCK4| LED_LOCK5| LED_LOCK6)

using namespace driver_system;
using namespace stmlib;
using namespace stm_audio_bootloader;


const float kSampleRate = 48000.0;
__IO uint16_t adc_buffer[NUM_ADCS]; // ADC data array

//const float kModulationRate = 6000.0; //QPSK 6000
//const float kBitRate = 12000.0; //QPSK 12000
uint32_t kStartExecutionAddress =		0x08008000;
uint32_t kStartReceiveAddress = 		0x08040000;
uint32_t EndOfMemory =					0x0807FFFC;

extern "C" {

void HardFault_Handler(void) { while (1); }
void MemManage_Handler(void) { while (1); }
void BusFault_Handler(void) { while (1); }
void UsageFault_Handler(void) { while (1); }
void NMI_Handler(void) { }
void SVC_Handler(void) { }
void DebugMon_Handler(void) { }
void PendSV_Handler(void) { }

// void process_audio_block(int32_t *input, int32_t *output, uint16_t size){}


}
System sys;
PacketDecoder decoder;
Demodulator demodulator;

uint16_t packet_index;
uint16_t old_packet_index=0;
uint8_t slider_i=0;

uint8_t g_error;

enum UiState {
  UI_STATE_WAITING,
  UI_STATE_RECEIVING,
  UI_STATE_ERROR,
  UI_STATE_WRITING
};
volatile UiState ui_state;

extern "C" {

inline void *memcpy(void *dest, const void *src, size_t n)
{
    char *dp = (char *)dest;
    const char *sp = (const char *)src;
    while (n--)
        *dp++ = *sp++;
    return dest;
}


uint32_t out_mask[6] = {0,0,0,0,0,0};

void LEDUp(uint8_t ch) {
	out_mask[ch] = MAX24f;
}
void LEDDown(uint8_t ch) {
	out_mask[ch] = 0;
}
void LEDLevel(uint8_t ch, uint32_t lev) {
	out_mask[ch] = lev;
}
void LEDAll(uint8_t state) {

	if(!state) {
		for(uint8_t i=0;i<6;i++) {
			out_mask[i] = 0;
		}
	} else {
		for(uint8_t i=0;i<6;i++) {
			out_mask[i] = MAX24f;
		}
	}
		
}

void update_slider_LEDs(void){
	static uint16_t dly=0;
	uint16_t fade_speed=800;

	if (ui_state == UI_STATE_RECEIVING){
		if (packet_index>old_packet_index){
			old_packet_index=packet_index;
			// LED_SLIDER_OFF(ALL_SLIDERS);
			// LED_SLIDER_ON(slider_led[slider_i]);
			// LEDUp(1);
			// if (++slider_i>=6) {slider_i=0;}

			//FSK only?
/*
			if (((packet_index/6) % (78*2) )<78){
				LEDUp(2);
				// LEDDriver_set_one_LED((packet_index/6) % 78, 500);
			} else {
				LEDDown(2);
				// LEDDriver_set_one_LED((packet_index/6) % 78, 0);
			}*/
		}
		LEDDown(3);
		LEDDown(5);
		if(dly++==fade_speed) {
			dly=0; // reset
		}
		LEDLevel(4, dly << 13);

	} else if (ui_state == UI_STATE_WRITING){

		LEDDown(4);
		LEDDown(5);
		if(dly++==fade_speed) {
			dly=0; // reset
		}
		LEDLevel(3, dly << 13);

	} else if (ui_state == UI_STATE_WAITING){

		LEDDown(3);
		LEDDown(4);
		if(dly++==fade_speed) {
			dly=0; // reset
		}
		LEDLevel(5, dly << 13);
	}
}

uint16_t check_speed(void){
	return !!SPEED_MODE;
}

uint16_t State=0;
uint16_t manual_exit_primed;
uint8_t exit_updater;

void check_button(void){
	uint16_t t;

	//Button depressed: ROTARY_SW=true, released: ROTARY_SW=false
	//Depressed adds a 0, released adds a 1

	t = 0xe000 | check_speed(); // returns 0/1 for 0xe000 or 0xe001
	State=(State<<1) | t;

	if (State == 0xff00)  	//Released event (depressed followed by released)
		manual_exit_primed=1;

	if (State == 0xe00f){ 				 //Depressed event (released followed by a bunch of depressed)
		if (packet_index==0 && manual_exit_primed==1)
			exit_updater=1;
	}

}


void SysTick_Handler() {
	system_clock.Tick();  // Tick global ms counter.
	update_slider_LEDs();
	check_button();
}

uint16_t discard_samples = 8000;

void process_audio_block(uint32_t *input, uint32_t *output, uint16_t size){
	uint8_t sample;
	static uint8_t last_sample=0;
	int32_t t;
	int32_t mask[6];
	// LEDUp(5);

	for(t=1;t<6;t++) {
		mask[t] = out_mask[t];
	}

	// size = codec_RX_Block
	while (size) {
		size-=4;

		*input++;
		*input++;
		*input++;
		// ^ skip first 3 inputs, and use 4th (RUN) >>

		t=-(int32_t)(*input << 8);
		// t = t<<1; // double volume

		if (last_sample==1){
			if (t < -3000) {
				sample=0;
			} else {
				sample=1;
			}
		} else {
			if (t > 4000) {
				sample=1;
			} else {
				sample=0;
			}
		}
		last_sample=sample;


		// if (sample) {LOCKJACK_ON;}
		// else {LOCKJACK_OFF;}

		if (!discard_samples) {
			demodulator.PushSample(sample);
		} else {
			--discard_samples;
		}

		// first 6 outs show LEDs
		if(sample) {
			*output++ = 0x7FFFFF;
		} else {
			*output++ = 0;
		}
		*output++ = mask[1];
		*output++ = mask[2];
		*output++ = mask[3];
		*output++ = mask[4];
		*output++ = mask[5];

		// last out sends audio
		if (ui_state == UI_STATE_ERROR) {
			*output++=0;
		} else {
			*output++=*input;
		}

		*input++; // just 1 for RUN

	}

	// out_mask[1] = discard_samples << 10;

	// convert_32b_to_dac(codec_TX_Block, buf_[0], buf_[1], buf_[2], buf_[3], buf_[4], buf_[5], buf_all, output);

	// LEDDown(5);
}

extern uint32_t *srcH, *dstH, *srcF, *dstF;
void DMA2_Stream4_IRQHandler(void) {
	
	if (DMA_GetITStatus(DMA2_Stream4, DMA_IT_HTIF4) != RESET) {        

        	process_audio_block(srcH, dstH, codec_RX_Block); // Run the main audio loop! First half

		DMA_ClearITPendingBit(DMA2_Stream4, DMA_IT_HTIF4);
		while(DMA_GetITStatus(DMA2_Stream4, DMA_IT_HTIF4) != RESET) { ;; }
	} else if (DMA_GetITStatus(DMA2_Stream4, DMA_IT_TCIF4) != RESET) {

        	process_audio_block(srcF, dstF, codec_RX_Block); // Second half of DMA

		DMA_ClearITPendingBit(DMA2_Stream4, DMA_IT_TCIF4);
		while(DMA_GetITStatus(DMA2_Stream4, DMA_IT_TCIF4) != RESET) { ;; }
	} else if (DMA_GetITStatus(DMA2_Stream4, DMA_IT_TEIF4) != RESET) {
		DMA_ClearITPendingBit(DMA2_Stream4, DMA_IT_TEIF4);
		while(DMA_GetITStatus(DMA2_Stream4, DMA_IT_TEIF4) != RESET) { ;; }
	} else if (DMA_GetITStatus(DMA2_Stream4, DMA_IT_FEIF4) != RESET) {
		DMA_ClearITPendingBit(DMA2_Stream4, DMA_IT_FEIF4);
		while(DMA_GetITStatus(DMA2_Stream4, DMA_IT_FEIF4) != RESET) { ;; }
	} else if (DMA_GetITStatus(DMA2_Stream4, DMA_IT_DMEIF4) != RESET) {
		DMA_ClearITPendingBit(DMA2_Stream4, DMA_IT_DMEIF4);
		while(DMA_GetITStatus(DMA2_Stream4, DMA_IT_DMEIF4) != RESET) { ;; }
	}
}

}

static uint32_t current_address;
static uint32_t kSectorBaseAddress[] = {
  0x08000000,
  0x08004000,
  0x08008000,
  0x0800C000,
  0x08010000,
  0x08020000,
  0x08040000,
  0x08060000,
  0x08080000,
  0x080A0000,
  0x080C0000,
  0x080E0000
};
const uint32_t kBlockSize = 16384;
const uint16_t kPacketsPerBlock = kBlockSize / kPacketSize;
uint8_t recv_buffer[kBlockSize];


inline void CopyMemory(uint32_t src_addr, uint32_t dst_addr, size_t size) {

	FLASH_Unlock();
	FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR |
				  FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR|FLASH_FLAG_PGSERR);

	for (size_t written = 0; written < size; written += 4) {

		//check if dst_addr is the start of a sector (in which case we should erase the sector)
		for (int32_t i = 0; i < 12; ++i) {
			if (dst_addr == kSectorBaseAddress[i]) {
				// LED_ON(LED_LOCK[i % 6]);
				FLASH_EraseSector(i * 8, VoltageRange_3);
				// LED_OFF(LED_LOCK[i % 6]);
			}
		}

		//Boundary check
		if (dst_addr > (kStartReceiveAddress-4)) //Do not overwrite receive buffer
			break;

		//Program the word
		FLASH_ProgramWord(dst_addr, *(uint32_t*)src_addr);

		src_addr += 4;
		dst_addr += 4;
	}

}


inline void ProgramPage(const uint8_t* data, size_t size) {
	LEDUp(4);
	// USART_putn8(USART1, 1);

	FLASH_Unlock();
	FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR |
				  FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR|FLASH_FLAG_PGSERR);
	// USART_putn8(USART1, 1);
	for (int32_t i = 0; i < 12; ++i) {
		if (current_address == kSectorBaseAddress[i]) {
		  FLASH_EraseSector(i * 8, VoltageRange_3);
		}
	}
	// USART_putn8(USART1, 2);
	const uint32_t* words = static_cast<const uint32_t*>(static_cast<const void*>(data));
	for (size_t written = 0; written < size; written += 4) {
		FLASH_ProgramWord(current_address, *words++);
		current_address += 4;
		if (current_address>=EndOfMemory){
			ui_state = UI_STATE_ERROR;
			g_error=1;
			break;
		}
	}
	// USART_putn8(USART1, 3);

	LEDDown(4);
}

void init_audio_in(){

	//QPSK or Codec
	Codec_Init();
	do {register unsigned int i; for (i = 0; i < 1000000; ++i) __asm__ __volatile__ ("nop\n\t":::"memory");} while (0);
	SAI_Block_Init();
	do {register unsigned int i; for (i = 0; i < 1000000; ++i) __asm__ __volatile__ ("nop\n\t":::"memory");} while (0);

}

void Init() {
	sys.Init(0);
	system_clock.Init();

	USART_Config(115200); // Configure debugger
	USART_puts(USART1, "\n\rBoot");

	init_inouts(); // UPDATE THIS FUNCTION TO CHECK USART PINS not switches
	uint32_t i = ADC1_Init((uint16_t *)adc_buffer); // init ADC converters
	delay(10000);

}
/*
void LED_ring_startup(void){
	uint16_t i;
	uint32_t dly;
	uint8_t trail=8;

	LED_ON(LED_RING_OE); //actually turns the LED ring off
	LEDDriver_Init(5);
	for (i=0;i<26;i++)	LEDDriver_setRGBLED(i,0);
	LED_OFF(LED_RING_OE); //actually turns the LED ring on

	for (i=0;i<77+trail;i++){
		if (i<77) LEDDriver_set_one_LED(i, 500);
		delay(300000);
		if (i>=trail) LEDDriver_set_one_LED(i-trail, 0);
	}
}*/

void InitializeReception() {


	//FSK

	decoder.Init();
	decoder.Reset();

	demodulator.Init(16, 8, 4);
	demodulator.Sync();



	//QPSK
	/*
	decoder.Init(20000);
	demodulator.Init(
	 kModulationRate / kSampleRate * 4294967296.0,
	 kSampleRate / kModulationRate,
	 2.0 * kSampleRate / kBitRate);
	demodulator.SyncCarrier(true);
	decoder.Reset();
*/

	current_address = kStartReceiveAddress;
	packet_index = 0;
	old_packet_index = 0;
	slider_i = 0;
	ui_state = UI_STATE_WAITING;
}


int main(void) {
	uint32_t symbols_processed=0;
	uint32_t dly=0, button_debounce=0;
	uint8_t i;

//	InitializeReception(); //QPSK
	Init();
	InitializeReception(); //FSK

	dly=0x20;
	while(dly--){
		// button_debounce += read_speed();
		button_debounce += check_boot();
	}
	// check_boot_verbose();
	exit_updater = (button_debounce>0x10) ? 0 : 1;

	if (!exit_updater){
		init_audio_in(); //QPSK or Codec
		sys.StartTimers(); // this is div1000 perhaps causes weird shit due to 180MHz clock?
	}
	LEDAll(0);
	button_debounce = 0;
	dly=0x20;
	while(dly--){
		button_debounce += check_boot();
	}
	exit_updater = (button_debounce>0x10) ? 0 : 1;

	manual_exit_primed=0;


		// LEDUp(3);

	while (!exit_updater) {
		g_error = 0;

		while (demodulator.available() && !g_error && !exit_updater) {
			uint8_t symbol = demodulator.NextSymbol();
			PacketDecoderState state = decoder.ProcessSymbol(symbol);
			symbols_processed++;

			switch (state) {
				case PACKET_DECODER_STATE_OK:
				{
					ui_state = UI_STATE_RECEIVING;
					memcpy(recv_buffer + (packet_index % kPacketsPerBlock) * kPacketSize, decoder.packet_data(), kPacketSize);
					++packet_index;
					if ((packet_index % kPacketsPerBlock) == 0) {
						ui_state = UI_STATE_WRITING;
						USART_puts(USART1, "\n\rwarningggg");
						ProgramPage(recv_buffer, kBlockSize);
						decoder.Reset();
						demodulator.Sync(); //FSK
						//demodulator.SyncCarrier(false);//QPSK
					} else {
						decoder.Reset(); //FSK

						//demodulator.SyncDecision();//QPSK
					}
				}
				break;

				case PACKET_DECODER_STATE_ERROR_SYNC:
					LEDUp(2); // light LED 3N
					// LED_ON(LED_LOCK[2]);
					g_error = 1;
					// USART_puts(USART1, "\n\rSYNC");

					break;

				case PACKET_DECODER_STATE_ERROR_CRC:
					LEDUp(1); // light LED 4N
					g_error = 1;
					// USART_puts(USART1, "\n\rCRC");
					break;

				case PACKET_DECODER_STATE_END_OF_TRANSMISSION:
					exit_updater = 1;
					LEDAll(0);
					LEDUp(2);

					USART_puts(USART1, "\n\rEOT");
					//Copy from Receive buffer to Execution memory

					CopyMemory(kStartReceiveAddress, kStartExecutionAddress, (current_address-kStartReceiveAddress));

					// USART_puts(USART1, "\n\rCPY");
					LEDAll(1);

					break;

				default:
					break;
			}
		}
		if (g_error) {
			ui_state = UI_STATE_ERROR;

			// USART_puts(USART1, "\n\rERROR");
			LEDUp(5);
			while (check_speed()){;}
			// USART_puts(USART1, "\n\rWAIT");

			LEDDown(5);
			while (check_speed()){;}
			// USART_puts(USART1, "\n\rRST");

			LEDAll(0);

			// startup animation

			InitializeReception();
			manual_exit_primed=0;
			exit_updater=0;
		}
	}
	USART_puts(USART1, "\n\rEXIT");

	// LEDAll(0);
	// do {register unsigned int i; for (i = 0; i < 1000000; ++i) __asm__ __volatile__ ("nop\n\t":::"memory");} while (0);

	// USART_puts(USART1, "\n\r2MAIN");
	// do {register unsigned int i; for (i = 0; i < 1000000; ++i) __asm__ __volatile__ ("nop\n\t":::"memory");} while (0);
	
	// manually deinit all io (in reverse order)
	SAI_Block_deInit();
	// Codec_GPIO_deInit();
	ADC1_deinit();
	// deinit_inouts();
	// USART_deinit();

	Uninitialize();
	JumpTo(kStartExecutionAddress);

}