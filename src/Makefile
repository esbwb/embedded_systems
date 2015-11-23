SUBSRCS := \
main.c usart.c

SUBSRCS := $(addprefix src/, $(SUBSRCS))

SRCS += $(SUBSRCS)

OBJS += $(SUBSRCS:%.c=%.o)

DEPS += $(SUBSRCS:%.c=%.d)

src/%.o: src/%.c
	@echo 'Building file: $@'
	@echo 'Invoking: AVR Compiler'
	avr-gcc $(CFLAGS) -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $@'
	@echo ' '
