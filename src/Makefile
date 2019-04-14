CC=arm-none-eabi-gcc

CFLAGS = \
	-marm -fpic -Wall -fno-common -fno-builtin -ffreestanding -nostdinc	\
	-fno-strict-aliasing -mno-thumb-interwork -fno-stack-protector -fno-toplevel-reorder	\
	-Wstrict-prototypes -Wno-format-nonliteral -Wno-format-security -nostdlib

SRCS = \
	boot.c		\
	gpio.c		\
	uart.c

TARGET = boot
SD_CARD_PATH = /dev/sdb

all	:
	${CC} ${CFLAGS} ${SRCS} -o ${TARGET}.elf -T ${TARGET}.lds -Wl,-N
	arm-none-eabi-objcopy -O binary ${TARGET}.elf ${TARGET}.bin
	mksunxiboot ${TARGET}.bin ${TARGET}.sunxi

write	:
	sudo dd if=${TARGET}.sunxi of=${SD_CARD_PATH} bs=1024 seek=8
	sync; sync; sync;
	sync; sync; sync;

clean	:
	rm -f ${TARGET}.elf ${TARGET}.bin ${TARGET}.sunxi

