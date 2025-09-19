CC = arm-none-eabi-gcc 

CFLAGS = -c -mcpu=cortex-m3 -mthumb -O0 -g3 -Wall

LDFLAGS = -T ld/stm32f103rb.ld -Wl,-Map=build/stm32f103rb.map -nostartfiles


SRCS = $(wildcard src/*.c)
OBJS = $(patsubst src/%.c,build/%.o,$(SRCS))


all: build/firmware.elf build/firmware.bin

# compile
build/%.o: src/%.c
	$(CC) $(CFLAGS) $< -o $@

# assembling omitted, no rule needed so far

# link
build/firmware.elf: $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $@

# gen bin
build/firmware.bin: build/firmware.elf
	arm-none-eabi-objcopy -O binary $< $@

clean:
	rm -rf build/*

.PHONY: all clean

