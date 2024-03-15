XLEN ?= 32
CROSSCOMPILE ?= riscv32-unknown-linux-gnu-
CC = ${CROSSCOMPILE}gcc
PYTHON=python

my_dir := /home/chlord/workspace/tool/Zerocore_bootrom

ifeq ($(XLEN), 64)
CFLAGS = -Os -ggdb -march=rv64imac -mabi=lp64 -Wall -mcmodel=medany -mexplicit-relocs
else
CFLAGS = -O2 -ggdb  -march=rv32ima_zicsr -mabi=ilp32 -W -Wall -mcmodel=medany -mexplicit-relocs -fno-builtin
endif

CCASFLAGS = -mcmodel=medany -mexplicit-relocs
LDFLAGS = -nostdlib -nodefaultlibs -nostartfiles

INCLUDES = -I./ -I./src

SRCS_C = src/main.c src/uart.c src/spi.c src/sd.c src/gpt.c
#SRCS_C = src/main.c src/uart.c
SRCS_ASM = startup.S
OBJS_C = $(SRCS_C:.c=.o)
OBJS_S = $(SRCS_ASM:.S=.o)

MAIN = bootrom_$(XLEN).elf
MAIN_BIN = $(MAIN:.elf=.bin)
MAIN_IMG = $(MAIN:.elf=.img)
MAIN_SV = $(MAIN:.elf=.sv)

#DTB = cv$(XLEN)a6.dtb

#.PHONY: clean

$(MAIN): $(OBJS_C) $(OBJS_S) linker.lds
	$(CC) $(CFLAGS) $(LDFLAGS) $(INCLUDES) -Tlinker.lds $(OBJS_S) $(OBJS_C) -o $(MAIN)
	@echo "LD    >= $(MAIN)"

%.img: %.bin
	dd if=$< of=$@ bs=128

%.bin: %.elf
	$(CROSSCOMPILE)objcopy -O binary $< $@

%.o: %.c
	@$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@
	@echo "CC    <= $<"

%.o: %.S
	@$(CC) $(CFLAGS) $(CCASFLAGS) $(INCLUDES) -c $<  -o $@
	@echo "CC    <= $<"

#%.dtb: %.dts
#	dtc -I dts $< -O dtb -o $@

%.sv: %.img
	$(PYTHON) gen_rom/gen_rom.py $<
	cd ..
	@echo "PYTHON >= $(MAIN_SV)"

clean:
	$(RM) $(OBJS_C) $(OBJS_S) $(MAIN) $(MAIN_BIN) $(MAIN_IMG)					   	&&\
	rm  bootrom_32.* test.*

#all: $(MAIN) $(MAIN_BIN) $(MAIN_IMG) $(MAIN_SV)
all: $(MAIN) $(MAIN_BIN)
	echo "zero stage bootloader has been compiled!"

$(my_dir)/sim/custom-tests/tools/bootrom_32.coe:
	cd $(my_dir)/sim/custom-tests/tools 											&&\
	cp $(my_dir)/bootrom/bootrom_32.elf ./ 											&&\
    riscv64-unknown-linux-gnu-objdump -x -D bootrom_32.elf > bootrom_32.asm 				&&\
	riscv64-unknown-linux-gnu-objcopy -O verilog bootrom_32.elf bootrom_32.hex 			&&\
	./hex2coe bootrom_32.hex bootrom_32.coe 80000000 bootrom_32.data.coe 88000000
coe_gen:$(my_dir)/sim/custom-tests/tools/bootrom_32.coe

$(my_dir)/sim/custom-tests/tools/test.coe:
	cd $(my_dir)/sim/custom-tests/tools 											&&\
	cp $(my_dir)/bootrom/bootrom_32.elf ./ 											&&\
    riscv64-unknown-linux-gnu-objdump -x -D bootrom_32.elf > test.asm 					&&\
	riscv64-unknown-linux-gnu-objcopy -O verilog bootrom_32.elf test.hex 					&&\
	./hex2coe test.hex test.coe 80000000 test.data.coe 88000000
test_gen:$(my_dir)/sim/custom-tests/tools/test.coe

# DO NOT DELETE THIS LINE -- make depend needs it
