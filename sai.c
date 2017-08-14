#include <stm32f4xx.h>
#include "sai.h"
#include "dig_inouts.h"
// #include "globals.h"
// #include "slopes.h"
#include "debug.h"
// #include "bootloader.cc"


uint32_t txbuf, rxbuf;


/*
	max CPU time is for sound-sustain-run mode
	w/ FM input & FM knob full CW
	all 6 triggers occuring at a high rate
	ramp at maximum CW
	curve at 9:00

	Block_Size 8 = peak 55%
	Block_Size 6 = peak 58%
	Block_Size 4 = peak xx%
		latency 
	Block_Size 2 = peak 76%
		latency 1.24ms
*/


// These could be int32_t instead (remove the *2) if DMA is converted to full 32bit transfers
	// This would greatly simplify audio_convert() functions
	// They would only need to dump output vals into the DMA buffers, not split/join memory
	// Try it after running in existing setting!!
volatile uint32_t tx_buffer[codec_TX_Block * 2];
volatile uint32_t rx_buffer[codec_RX_Block * 2];

extern uint8_t tr_samp; // sample counter for triggers (up to 128sample block)
extern uint8_t tr_write; // which half should be written to


uint32_t *srcH, *dstH, *srcF, *dstF;

void SAI_EnablePeripheralClocks(void);
void SAI_ConfigPLL(void);
void SAI_EnablePLL(void);
void SAI_ConfigSAI(void);
void SAI_EnableGPIO(void);
void SAI_ConfigDMA(uint32_t *TX_BUFFF, uint32_t *RX_BUFFF);
void SAI_EnableDMA(void);
void SAI_ApplySAI(void);
void SAI_Enable(void);

	SAI_InitTypeDef saiAinit, saiBinit;
	SAI_FrameInitTypeDef saiAframe, saiBframe;
	SAI_SlotInitTypeDef saiAslot, saiBslot;


void SAI_Block_Init(void) {

	SAI_EnablePeripheralClocks();
	SAI_ConfigPLL();
	SAI_EnablePLL();
	SAI_EnableGPIO();
	SAI_ConfigSAI();
	SAI_ApplySAI();
	SAI_ConfigDMA((uint32_t *)tx_buffer, (uint32_t *)rx_buffer);
	SAI_EnableDMA();

	SAI_Enable();
}


//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////




void SAI_EnablePeripheralClocks(void) {
	
	// first deactivate to recover from bootloader
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SAI1, DISABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, DISABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, DISABLE);

	// Enabling clocks for the physical pins & SAI hardware
	// enable clocks: SAI1, SAI-hardware

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SAI1, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);

}

void SAI_ConfigPLL(void) {
		// Assume Clock is 1MHz, so multiply by 344 for 344MHz
		// Set PLLSAIQ to 7 for 344/7 = 49.14285714MHz. Q Must be between 2 and 15.
		// PLLSAIR = 7 (Don't Care > for LCD)
	RCC_PLLI2SConfig(344, 7, 7); // 12/24/48kHz
	//RCC_PLLI2SConfig(429, 2, 2); // 44.1kHz

	// This can divide the clock by 1-32
	// I2S clock frequency = f(PLLI2S_Q) / RCC_PLLI2SDivQ  
	// 49.143Mhz / 1
	RCC_SAIPLLI2SClkDivConfig(1); // 48kHz
	//RCC_SAIPLLI2SClkDivConfig(19); // 44.1kHz
	//RCC_SAIPLLI2SClkDivConfig(2); // 24kHz

	// Configure Block A & B Separately
	RCC_SAIBlockACLKConfig(RCC_SAIACLKSource_PLLI2S);
	RCC_SAIBlockBCLKConfig(RCC_SAIBCLKSource_PLLI2S);
}

void SAI_EnablePLL(void) {
	RCC_PLLI2SCmd(DISABLE); // disarm the PLL
	while(RCC_GetFlagStatus(RCC_FLAG_PLLI2SRDY) == ENABLE) { ;; }
	RCC_PLLI2SCmd(ENABLE); // Start the PLL
	while(RCC_GetFlagStatus(RCC_FLAG_PLLI2SRDY) == DISABLE) { ;; }
}


void SAI_EnableGPIO(void) {
	// Connect pins to alternate function: AF6
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource2, GPIO_AF_SAI1);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource3, GPIO_AF_SAI1);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource4, GPIO_AF_SAI1);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource5, GPIO_AF_SAI1);	
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource6, GPIO_AF_SAI1);	

	GPIO_InitTypeDef gpio;

	// Initialize Struct
	GPIO_StructInit(&gpio);

	// program struct settings
	gpio.GPIO_Mode = GPIO_Mode_AF;
	gpio.GPIO_Speed = GPIO_Speed_50MHz; // This is 'High' Speed. Could use 25 or 100MHz for medium/max speed.
	gpio.GPIO_OType = GPIO_OType_PP; // Fastest & most reliable?
	gpio.GPIO_PuPd = GPIO_PuPd_NOPULL; // Could try pullup apparently?

	// Init SAI pins -- 'OType' doesn't matter for input pin (not outputting)
	gpio.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6;

	// Enable GPIO pins
	GPIO_Init(GPIOE, &gpio);	
}

void SAI_ConfigSAI(void) {
		// SAI Data Setup
	// Ensure SAI & DMA are both deactivated before setting values
	SAI_Cmd(SAI1_Block_A, DISABLE);	
	SAI_DeInit(SAI1); // Does the whole SAI (both blocks)

	// Configure SAI structs
	// Init Block A
	SAI_StructInit(&saiAinit);
	saiAinit.SAI_AudioMode = SAI_Mode_MasterTx; // Master Tx
	saiAinit.SAI_Protocol = SAI_Free_Protocol; // Not AC97 or SPDIF
	saiAinit.SAI_DataSize = SAI_DataSize_24b; // 24bit data in a 32clock slot?
	saiAinit.SAI_FirstBit = SAI_FirstBit_MSB; // MSB first
/**///saiAinit.SAI_ClockStrobing = SAI_ClockStrobing_FallingEdge; // VERY UNCERTAIN ABOUT THIS.
		saiAinit.SAI_ClockStrobing = SAI_ClockStrobing_RisingEdge; // VERY UNCERTAIN ABOUT THIS.
	saiAinit.SAI_Synchro = SAI_Asynchronous; // Async Master, so it sends BCLK & SCK
/**/saiAinit.SAI_OUTDRIV = SAI_OutputDrive_Enabled; // Needs to be ENABLED **BEFORE** enabling audio block
													// But **AFTER** audio block configuration.
	saiAinit.SAI_NoDivider = SAI_MasterDivider_Enabled; // Divider is enabled
	saiAinit.SAI_MasterDivider = 2; // MCLK = Input(192k*256)/(2 * DIVIDER). therefore =2 means /4. hence 48kHz
	saiAinit.SAI_FIFOThreshold = SAI_FIFOThreshold_HalfFull;
	
	SAI_FrameStructInit(&saiAframe);
	saiAframe.SAI_FrameLength = 256;
	saiAframe.SAI_ActiveFrameLength = 128;
	saiAframe.SAI_FSDefinition = SAI_FS_StartFrame; // FS starts new audio frame
	saiAframe.SAI_FSPolarity = SAI_FS_ActiveLow; // FS activates by going low
	saiAframe.SAI_FSOffset = SAI_FS_FirstBit;

	SAI_SlotStructInit(&saiAslot);
	saiAslot.SAI_FirstBitOffset = 1; // First bit in slot is a timing buffer
	saiAslot.SAI_SlotSize = SAI_SlotSize_32b; // Each slot is 32 SCK long
	saiAslot.SAI_SlotNumber = 8; // Eight slots (channels) per frame
	saiAslot.SAI_SlotActive = SAI_SlotActive_0 | SAI_SlotActive_1 | SAI_SlotActive_2 | SAI_SlotActive_3 | SAI_SlotActive_4 | SAI_SlotActive_5 | SAI_SlotActive_6; // 7 slots

	SAI_Cmd(SAI1_Block_B, DISABLE);	

	// Configure SAI structs
	// Init Block B
	SAI_StructInit(&saiBinit);
	saiBinit.SAI_AudioMode = SAI_Mode_SlaveRx; // Slave Rx
	saiBinit.SAI_Protocol = SAI_Free_Protocol; // Not AC97 or SPDIF
	saiBinit.SAI_DataSize = SAI_DataSize_24b; // 24bit data in a 32clock slot?
	saiBinit.SAI_FirstBit = SAI_FirstBit_MSB; // MSB first
/**/saiBinit.SAI_ClockStrobing = SAI_ClockStrobing_RisingEdge; // VERY UNCERTAIN ABOUT THIS.
	saiBinit.SAI_Synchro = SAI_Synchronous; // Async Master, so it sends BCLK & SCK
/**/saiBinit.SAI_OUTDRIV = SAI_OutputDrive_Disabled; // Needs to be ENABLED **BEFORE** enabling audio block
													// But **AFTER** audio block configuration.
	saiBinit.SAI_NoDivider = SAI_MasterDivider_Enabled; // Divider is enabled
	saiBinit.SAI_MasterDivider = 2; // MCLK = Input(192k*256)/(2 * DIVIDER). therefore =2 means /4. hence 48kHz
	saiBinit.SAI_FIFOThreshold = SAI_FIFOThreshold_HalfFull;
	
	SAI_FrameStructInit(&saiBframe);
	saiBframe.SAI_FrameLength = 256;
	saiBframe.SAI_ActiveFrameLength = 128;
	saiBframe.SAI_FSDefinition = SAI_FS_StartFrame; // FS starts new audio frame
	saiBframe.SAI_FSPolarity = SAI_FS_ActiveLow; // FS activates by going low
	saiBframe.SAI_FSOffset = SAI_FS_FirstBit;

	SAI_SlotStructInit(&saiBslot);
	saiBslot.SAI_FirstBitOffset = 1; // First bit in slot is a timing buffer
	saiBslot.SAI_SlotSize = SAI_SlotSize_32b; // Each slot is 32 SCK long
	saiBslot.SAI_SlotNumber = 8; // Eight slots (channels) per frame
/**/saiBslot.SAI_SlotActive = SAI_SlotActive_0 | SAI_SlotActive_1 | SAI_SlotActive_2 | SAI_SlotActive_3; // All 4 slots

}



void SAI_ApplySAI(void) {
		// Initialize SAI with structs
	SAI_Init(SAI1_Block_A, &saiAinit);
	SAI_FrameInit(SAI1_Block_A, &saiAframe);
	SAI_SlotInit(SAI1_Block_A, &saiAslot);

	SAI_Init(SAI1_Block_B, &saiBinit);
	SAI_FrameInit(SAI1_Block_B, &saiBframe);
	SAI_SlotInit(SAI1_Block_B, &saiBslot);
}


void SAI_ConfigDMA(uint32_t *TX_BUFFF, uint32_t *RX_BUFFF) {

	/* save for IRQ svc  */
	txbuf = (uint32_t)&tx_buffer;
	rxbuf = (uint32_t)&rx_buffer;

	srcH = (uint32_t *)(rxbuf); // Create pointers to rx & tx buffers to reference main audio loop
	dstH = (uint32_t *)(txbuf); // These tell the main loop where to find & store codec values.
	//srcH = (int16_t *)&rx_buffer;
	//dstH = (int16_t *)&tx_buffer;

	srcF = (uint32_t *)(rxbuf) + codec_RX_Block;
	dstF = (uint32_t *)(txbuf) + codec_TX_Block;
	//srcF = (int16_t *)&rx_buffer + codec_RX_Block;
	//dstF = (int16_t *)&tx_buffer + codec_TX_Block;


	DMA_InitTypeDef DMA_InitStructure, DMA_InitStructure2;

	/* Configure the TX DMA Stream for SAI1_A */
	SAI_DMACmd(SAI1_Block_A, DISABLE); // Disable Block A DMA Request
	DMA_Cmd(DMA2_Stream1, DISABLE); // Confirm DMA is disabled (in case of reconfiguration)
	DMA_DeInit(DMA2_Stream1);

	DMA_InitStructure.DMA_Channel = DMA_Channel_0;
	//DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&SAI1_Block_A->DR; // memory location of SAI1_A
		DMA_InitStructure.DMA_PeripheralBaseAddr = 0x40015820;

	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)TX_BUFFF;
	DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral; // Transmitting to SAI
	DMA_InitStructure.DMA_BufferSize = (uint32_t)(codec_TX_Block * 2); // (Block_Size * 16) * 2
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; // SAI auto-increments it's pointer, so no need to do it in DMA
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable; // Dump new data into subsequent DMA memory
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word; // Inactive
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Word; // Halfword = 16bit locations
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular; // Circular Buffer
	DMA_InitStructure.DMA_Priority = DMA_Priority_High; // High priority!
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable; // Not using FIFO - just straight DMA
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_1QuarterFull;
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
	DMA_Init(DMA2_Stream1, &DMA_InitStructure);


	/* Configure the RX DMA Stream for SAI_B */
	SAI_DMACmd(SAI1_Block_B, DISABLE); // Disable Block B DMA Request
	DMA_Cmd(DMA2_Stream4, DISABLE);
	DMA_DeInit(DMA2_Stream4);

	DMA_InitStructure2.DMA_Channel = DMA_Channel_1;
	//DMA_InitStructure2.DMA_PeripheralBaseAddr = (uint32_t)&SAI1_Block_B->DR;
		DMA_InitStructure2.DMA_PeripheralBaseAddr = 0x40015840;
	DMA_InitStructure2.DMA_Memory0BaseAddr = (uint32_t)RX_BUFFF;
	DMA_InitStructure2.DMA_DIR = DMA_DIR_PeripheralToMemory;
	DMA_InitStructure2.DMA_BufferSize = (uint32_t)(codec_RX_Block * 2); // (Block_Size * 8) * 2
	DMA_InitStructure2.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure2.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure2.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word;
	DMA_InitStructure2.DMA_MemoryDataSize = DMA_MemoryDataSize_Word;
	DMA_InitStructure2.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStructure2.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure2.DMA_FIFOMode = DMA_FIFOMode_Disable;
	DMA_InitStructure2.DMA_FIFOThreshold = DMA_FIFOThreshold_1QuarterFull;
	DMA_InitStructure2.DMA_MemoryBurst = DMA_MemoryBurst_Single;
	DMA_InitStructure2.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
	DMA_Init(DMA2_Stream4, &DMA_InitStructure2);
}


void SAI_EnableDMA(void) {
	NVIC_InitTypeDef NVIC_InitStructure;



	// Enable the Half & Complete DMA interrupts -> Called when ADC data received
	DMA_ITConfig(DMA2_Stream4, DMA_IT_TC, ENABLE);
	DMA_ITConfig(DMA2_Stream4, DMA_IT_HT, ENABLE);
	DMA_ITConfig(DMA2_Stream4, DMA_IT_TE, ENABLE);
	DMA_ITConfig(DMA2_Stream4, DMA_IT_FE, ENABLE);
	DMA_ITConfig(DMA2_Stream4, DMA_IT_DME, ENABLE);

	// SAI DMA IRQ Channel configuration
	NVIC_InitStructure.NVIC_IRQChannel = DMA2_Stream4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	//NVIC_EnableIRQ(DMA2_Stream4_IRQn);
	//while(NVIC_GetActive(DMA2_Stream4_IRQn)) { asm (""); }
	//while(!NVIC_GetActive(DMA2_Stream4_IRQn)) { asm (""); }

	//uint32_t del;
	//del = 100000; while(del) del--;
//	while(NVIC_GetActive(DMA2_Stream4_IRQn)) { asm (""); }

	// Enable the SAI DMA request
	SAI_DMACmd(SAI1_Block_B, ENABLE); // Enable Block B DMA Request
	SAI_DMACmd(SAI1_Block_A, ENABLE); // Enable Block A DMA Request

		// Enable the I2S DMA Streams
	DMA_Cmd(DMA2_Stream1, ENABLE);
	DMA_Cmd(DMA2_Stream4, ENABLE);
}


void SAI_Enable(void) {
	saiAinit.SAI_OUTDRIV = SAI_OutputDrive_Enabled; // Needs to be ENABLED **BEFORE** enabling audio block
	SAI_Init(SAI1_Block_A, &saiAinit);

	// Enable the SAI (Block B then A)
	SAI_Cmd(SAI1_Block_B, ENABLE); // Enable Block B (Slave)
	while(SAI_GetCmdStatus(SAI1_Block_B) == DISABLE) { ;; }

	SAI_Cmd(SAI1_Block_A, ENABLE); // Then enable Block A (Master)
	while(SAI_GetCmdStatus(SAI1_Block_A) == DISABLE) { ;; }
}








/*void DMA2_Stream4_IRQHandler(void) {
	
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
}*/


