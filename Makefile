BINARYNAME = bootloader

COMBO = combo
MAINAPP_HEX = ../JF3/main.hex

STARTUP = startup_stm32f4xx.s
SYSTEM = system_stm32f4xx.c
#LOADFILE = stm32f427.ld
LOADFILE = stm32_boot.ld

F_CPU          = 180000000L

DEVICE = stm32/device
CORE = stm32/core
PERIPH = stm32/periph

BUILDDIR = build

SOURCES += $(wildcard $(PERIPH)/src/*.c)
SOURCES += $(DEVICE)/src/$(STARTUP)
SOURCES += $(DEVICE)/src/$(SYSTEM)
SOURCES += $(wildcard *.cc)
SOURCES += $(wildcard *.c)
SOURCES += $(STMLIB)/system/bootloader_utils.cc
SOURCES += $(STMLIB)/system/system_clock.cc

OBJECTS = $(addprefix $(BUILDDIR)/, $(addsuffix .o, $(basename $(SOURCES))))

OBJECTS += ../stmlib/system/bootloader_utils.o ../stmlib/system/system_clock.o ../stm-audio-bootloader/fsk/packet_decoder.o


INCLUDES += -I$(DEVICE)/include \
			-I$(CORE)/include \
			-I$(PERIPH)/include \
			-I\

ELF = $(BUILDDIR)/$(BINARYNAME).elf
HEX = $(BUILDDIR)/$(BINARYNAME).hex
BIN = $(BUILDDIR)/$(BINARYNAME).bin

ARCH = arm-none-eabi
CC = $(ARCH)-gcc
CXX = $(ARCH)-g++
LD = $(ARCH)-ld
AS = $(ARCH)-as
OBJCPY = $(ARCH)-objcopy
OBJDMP = $(ARCH)-objdump
GDB = $(ARCH)-gdb
FLASH = st-flash

ARCHFLAGS = -mlittle-endian -mthumb -mthumb-interwork -mcpu=cortex-m4 -mfloat-abi=soft -mfpu=fpv4-sp-d16 

CFLAGS = -g2 -Os $(ARCHFLAGS) 
CFLAGS +=  -I. -DARM_MATH_CM4 -D'__FPU_PRESENT=1' -DF_CPU=$(F_CPU) -DSTM32F4XX   
CFLAGS += -DUSE_STDPERIPH_DRIVER  $(INCLUDES) 
CFLAGS +=  -fsingle-precision-constant -Wdouble-promotion 	

CPPFLAGS = $(CFLAGS) -fno-exceptions

#AFLAGS  = -mlittle-endian -mthumb -mcpu=cortex-m4 
AFLAGS  = $(ARCHFLAGS)

LDSCRIPT = $(DEVICE)/$(LOADFILE)
#LFLAGS  = -Map $(BINARYNAME).map -nostartfiles -T $(LDSCRIPT)
LFLAGS  = -Wl,-Map=$(BUILDDIR)/$(BINARYNAME).map -Wl,--gc-sections \
	-T $(LDSCRIPT) \
	-I.

SIZE_LIMIT = 16000

all: Makefile $(BIN) $(HEX)
	
echox:
	echo $(OBJECTS)
	
$(BIN): $(ELF)
	$(OBJCPY) -O binary $< $@
	$(OBJDMP) -x --syms $< > $(addsuffix .dmp, $(basename $<))
	ls -l $@ $<

$(HEX): $(ELF)
	$(OBJCPY) --output-target=ihex $< $@

$(ELF): $(OBJECTS)
#	$(LD) $(LFLAGS) -o $@ $(OBJECTS)
	$(CC) $(LFLAGS) -o $@ $(OBJECTS)

$(BUILDDIR)/%.o: %.cc
	mkdir -p $(dir $@)
	$(CXX) -c $(CPPFLAGS) $< -o $@

$(BUILDDIR)/%.o: %.c
	mkdir -p $(dir $@)
#	$(CC) -c $(CFLAGS) $< -o $@
	$(CC) $(CFLAGS) -std=c99 -c -o $@ $<

$(BUILDDIR)/%.o: %.s
	mkdir -p $(dir $@)
	$(AS) $(AFLAGS) $< -o $@ > $(addprefix $(BUILDDIR)/, $(addsuffix .lst, $(basename $<)))


flash: $(BIN)
	$(FLASH) write $(BIN) 0x08000000

combo_flash: combo
	$(FLASH) write $(COMBO).bin 0x08000000

combo: $(COMBO).bin

$(COMBO).bin: $(HEX)
	cat  $(MAINAPP_HEX) $(HEX) | \
	awk -f ../stmlib/programming/merge_hex.awk > $(COMBO).hex
	$(OBJCPY) -I ihex -O binary $(COMBO).hex $(COMBO).bin


clean:
	rm -rf build
	
wav: fsk-wav

qpsk-wav: $(BIN)
	cd .. && python stm-audio-bootloader/qpsk/encoder.py \
		-t stm32f4 -s 48000 -b 12000 -c 6000 -p 256 \
		SMR/$(BIN)


fsk-wav: $(BIN)
	cd .. && python stm-audio-bootloader/fsk/encoder.py \
		-s 48000 -b 16 -n 8 -z 4 -p 256 -g 16384 -k 1100 \
		SMR/$(BIN)
	
