SUBSRCS := \
main.c usart.c

SUBSRCS := $(addprefix src/, $(SUBSRCS))

SRCS += $(SUBSRCS)

OBJS += $(SUBSRCS:%.c=%.o)

DEPS += $(SUBSRCS:%.c=%.d)

src/%.o: src/%.c
	@echo 'Building file: $@'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -DSIM=$(SIM) -Wall -Wextra -g2 -gstabs -O2 -fpack-struct -fshort-enums \
	-ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields \
	-mmcu=$(MCU) -DF_CPU=$(FREQ)UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $@'
	@echo ' '
