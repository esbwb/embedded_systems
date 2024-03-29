SRCS :=

OBJS :=

DEPS :=

CFLAGS = \
-Wall -Wextra -g2 -gstabs -O2 -fpack-struct -fshort-enums \
-ffunction-sections -fdata-sections -std=gnu99 -funsigned-char \
-funsigned-bitfields -mmcu=$(MCU) -DF_CPU=$(FREQ)UL

LFLAGS = -Wl,-Map,$(MAP)

LIBS :=

ELF := es.elf

LSS := es.lss

HEX := es.hex

EEP := es.eep

MAP := es.map

MCU := atmega328p

FREQ := 16000000

#Set this to 1 to define simulation symbols
SIM := 0

#Path to simulavr binary
SIMULAVR := ./simulavr

SIM_READ := 0x22,

SIM_WRITE := 0x20,

#Determins whether we use avr-libc stdio (for printf)
WITH_STDIO := 1

ifeq ($(SIM),1)
CFLAGS += -DSIM
endif

ifeq ($(WITH_STDIO),1)
CFLAGS += -DWITH_STDIO
LFLAGS += -Wl,-u,vfprintf
LIBS += -lprintf_min
endif

.DEFAULT_GOAL := all

include src/Makefile

-include $(DEPS)

all: $(ELF) $(LSS) $(HEX) $(EEP)

$(ELF): $(OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc $(LFLAGS) -mmcu=$(MCU) -o $(ELF) $(OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

$(LSS): $(ELF)
	@echo 'Invoking: AVR Create Extended Listing'
	avr-objdump -h -S "$<"  > "$@"
	@echo 'Finished building: $@'
	@echo ' '

$(HEX): $(ELF)
	@echo 'Create Flash image (ihex format)'
	avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex "$<"  "$@"
	@echo 'Finished building: $@'
	@echo ' '

$(EEP): $(ELF)
	@echo 'Create eeprom image (ihex format)'
	avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex "$<" "$@"
	@echo 'Finished building: $@'
	@echo ' '

printsize: $(ELF)
	@echo 'Invoking: Print Size'
	avr-size --format=avr --mcu=$(MCU) "$<"
	@echo 'Finished building: $@'
	@echo ' '

avrdude: $(ELF)
	@echo 'Invoking: AVRDude'
	avrdude -carduino -pm328p -Uflash:w:$(HEX):a -P /dev/ttyACM*
	@echo 'Finished building: $@'
	@echo ' '

simulavr: $(ELF)
	@echo 'Invoking: simulavr'
	$(SIMULAVR) -f $(ELF) -d atmega328 -R $(SIM_READ)- -W $(SIM_WRITE)- -T exit
	@echo ' '

clean:
	rm -rfv $(OBJS) $(DEPS) $(ELF) $(LSS) $(HEX) $(EEP) $(MAP)

.PHONY: all clean
