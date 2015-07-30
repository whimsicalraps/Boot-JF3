# Makefile for STM32F4
# 11-10-2011 E. Brombaugh
# 2014-07-25 D Green

PROJECT = bootloader

COMBO = combo
MAINAPP_HEX = ../smrf-p6/main.hex

# Object files
OBJECTS = 	startup_stm32f429_439xx.o system_stm32f4xx.o \
			bootloader.o inouts.o bootloader_utils.o system_clock.o system.o led_driver.o \
			mem.o misc.o stm32f4xx_flash.o stm32f4xx_gpio.o stm32f4xx_rcc.o stm32f4xx_tim.o stm32f4xx_i2c.o \
			encoding/fsk/packet_decoder.o 
#			stm32f4xx_spi.o stm32f4xx_dma.o codec.o i2s.o encoding/qpsk/demodulator.o
		
			
 
# Linker script
LDSCRIPT = stm32f429xx.ld

# -finline-functions, -funswitch-loops, -fpredictive-commoning, -fgcse-after-reload, -ftree-vectorize

ARCHFLAGS = -mlittle-endian -mthumb -mthumb-interwork -mcpu=cortex-m4 -mfloat-abi=soft -mfpu=fpv4-sp-d16 
F_CPU          = 168000000L

CFLAGS = -g2 -Os $(ARCHFLAGS)
CFLAGS +=  -I. -DARM_MATH_CM4 -D'__FPU_PRESENT=1' -DF_CPU=$(F_CPU)
CFLAGS +=  -fsingle-precision-constant -Wdouble-promotion 	-L'/Users/design/4ms/stm32/gcc-arm-none-eabi-4_8-2014q2/lib/gcc/arm-none-eabi/4.8.4' \
	-L'/Users/design/4ms/stm32/gcc-arm-none-eabi-4_8-2014q2/arm-none-eabi/lib'


CPPFLAGS      = -fno-exceptions


AFLAGS  = $(ARCHFLAGS)
#LFLAGS  = -Map $(PROJECT).map -nostartfiles -T $(LDSCRIPT)
LFLAGS  = -Wl,-Map=$(PROJECT).map -Wl,--gc-sections \
	-T $(LDSCRIPT) \
	-I.

# Executables
ARCH = arm-none-eabi
CC = $(ARCH)-gcc
CXX = $(ARCH)-g++
LD = $(ARCH)-ld
AS = $(ARCH)-as
OBJCPY = $(ARCH)-objcopy
OBJDMP = $(ARCH)-objdump
GDB = $(ARCH)-gdb

CPFLAGS = -O binary
ODFLAGS	= -x --syms

FLASH = st-flash

# Targets
all: $(PROJECT).bin

clean:
	-rm -f $(OBJECTS) *.lst *.elf *.bin *.map *.dmp

flash: stlink_flash

stlink_flash: $(PROJECT).bin
	$(FLASH) write $(PROJECT).bin 0x08000000

combo_flash: combo
	$(FLASH) write $(COMBO).bin 0x08000000
	
$(PROJECT).hex: $(PROJECT).elf 
	$(OBJCPY) -O ihex $< $@
		

# ------------------------------------------------------------------------------
# Bootloader merging
# ------------------------------------------------------------------------------

combo: $(COMBO).bin

$(COMBO).bin:  $(MAINAPP_HEX) $(PROJECT).hex
	cat  $(MAINAPP_HEX) $(PROJECT).hex | \
	awk -f util/merge_hex.awk > $(COMBO).hex
	$(OBJCPY) -I ihex -O binary $(COMBO).hex $(COMBO).bin


$(PROJECT).bin: $(PROJECT).elf 
	$(OBJCPY) $(CPFLAGS) $(PROJECT).elf $(PROJECT).bin
	$(OBJDMP) $(ODFLAGS) $(PROJECT).elf > $(PROJECT).dmp
	$(OBJCPY) -O ihex $(PROJECT).elf $(PROJECT).hex
	ls -l $(PROJECT).elf $(PROJECT).bin $(PROJECT).hex

$(PROJECT).elf: $(OBJECTS) $(LDSCRIPT)
	$(CC) $(LFLAGS) -o $(PROJECT).elf $(OBJECTS)
	#$(LD) $(LFLAGS) -o $(PROJECT).elf $(OBJECTS)

startup_stm32f4xx.o: startup_stm32f4xx.s
	$(AS) $(AFLAGS) startup_stm32f4xx.s -o startup_stm32f4xx.o > startup_stm32f4xx.lst
	
%.o: %.cc
	$(CXX) -c $(CFLAGS) $(CPPFLAGS) $< -o $@


%.o: %.c %.h
	$(CC) $(CFLAGS) -std=c99 -c -o $@ $<

