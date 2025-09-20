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

flash: build/firmware.elf
	openocd -f interface/stlink.cfg -f target/stm32f1x.cfg \
	-c "program build/firmware.elf verify reset exit"

gdb: build/firmware.elf
	arm-none-eabi-gdb $< \
	-ex "target extended-remote | openocd -f interface/stlink.cfg -f target/stm32f1x.cfg -c 'gdb_port pipe'" \
	-ex "monitor reset halt"

strip: build/firmware.elf
	arm-none-eabi-strip --strip-all -o build/firmware_stripped.elf build/firmware.elf

.PHONY: all clean flash gdb

