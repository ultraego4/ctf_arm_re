CC = arm-none-eabi-gcc 

CFLAGS = -c -mcpu=cortex-m3 -mthumb -O0 -g3 -Wall

LDFLAGS = -T stm32f103rb.ld -Map=stm32f103rb.map -nostartfiles


SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

all: firmware.elf firmware.bin


# compile
%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

# assembling omitted, no rule needed so far

# link
firmware.elf: $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $@

# gen bin
firmware.bin: firmware.elf
	$(OBJCOPY) -O binary $< $@

clean:
	rm -rf *.o *.elf *.bin *.map

.PHONY: all clean

