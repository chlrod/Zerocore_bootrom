#include "uart.h"
#include "spi.h"
#include "sd.h"
#include "gpt.h"
#include "smp.h"

int main()
{   
    init_uart(0x10000000, 9600);
    print_uart("Hello World!\r\n");
    
    int res = gpt_find_boot_partition((uint8_t *)0x80000000UL, 2 * 16384);

    return 0;
    // __asm__ volatile(
    // "li a3, 0x12;"
    // "li t1, 0x13;"
    // "li t2, 0x14;"
    // "li t3, 0x15;"
    // "li a4, 0x80001200;"
    // "li a5, 0x13000000;"

    // "sw a3, 0(a4);"
    // "sw t1, 4(a4);"
    // "sw t2, 8(a4);"
    // "sw t3, 12(a4);"
    // "sw a3, 16(a4);"
    // "sw t1, 20(a4);"
    // "sw t2, 24(a4);"
    // "sw t3, 28(a4);"
    // "sw a3, 32(a4);"
    // "sw t1, 36(a4);"
    // "sw t2, 40(a4);"
    // "sw t3, 44(a4);"

    // "lw a6, 0(a4);"
    // "lw a6, 4(a4);"
    // "lw a6, 8(a4);"
    // "lw a6, 12(a4);"
    // "lw a6, 16(a4);"
    // "lw a6, 20(a4);"
    // "lw a6, 24(a4);"
    // "lw a6, 28(a4);"
    // "lw a6, 32(a4);"
    // "lw a6, 36(a4);"
    // "lw a6, 40(a4);"
    // "lw a6, 44(a4);"

    // "nop;"
    // "nop;"
    // "nop;"
    // "nop;"

    // "sw a3, 0(a5);"
    // "sw t1, 4(a5);"
    // "sw t2, 8(a5);"
    // "sw t3, 12(a5);"
    // "sw a3, 16(a5);"
    // "sw t1, 20(a5);"
    // "sw t2, 24(a5);"
    // "sw t3, 28(a5);"
    // "sw a3, 32(a5);"
    // "sw t1, 36(a5);"
    // "sw t2, 40(a5);"
    // "sw t3, 44(a5);"

    // "lw a6, 0(a5);"
    // "lw a6, 4(a5);"
    // "lw a6, 8(a5);"
    // "lw a6, 12(a5);"
    // "lw a6, 16(a5);"
    // "lw a6, 20(a5);"
    // "lw a6, 24(a5);"
    // "lw a6, 28(a5);"
    // "lw a6, 32(a5);"
    // "lw a6, 36(a5);"
    // "lw a6, 40(a5);"
    // "lw a6, 44(a5);"

    // "nop;"
    // "nop;"
    // "nop;"
    // "nop;"

    // "sw a3, 0(a4);"
    // "sw t1, 0(a5);"
    // "sw t2, 4(a4);"
    // "sw t3, 4(a5);"
    // "sw a3, 8(a4);"
    // "sw t1, 8(a5);"
    // "sw t2, 16(a4);"
    // "sw t3, 16(a4);"
    // "sw a3, 20(a5);"
    // "sw t1, 20(a5);"
    // "sw t2, 24(a4);"
    // "sw t3, 24(a5);"

    // "lw a6, 0(a4);"
    // "lw a6, 0(a5);"
    // "lw a6, 4(a4);"
    // "lw a6, 4(a5);"
    // "lw a6, 8(a4);"
    // "lw a6, 8(a5);"
    // "lw a6, 16(a4);"
    // "lw a6, 16(a4);"
    // "lw a6, 20(a5);"
    // "lw a6, 20(a5);"
    // "lw a6, 24(a4);"
    // "lw a6, 24(a5);"

    // "nop;"
    // "nop;"
    // "nop;"
    // "nop;"

    // "sw a3, 0(a4);"
    // "sw t1, 4(a4);"
    // "lw a6, 0(a4);"
    // "lw a6, 4(a4);"

    // "sw a3, 0(a5);"
    // "sw t1, 4(a5);"
    // "lw a6, 0(a5);"
    // "lw a6, 4(a5);"

    // "sw a3, 0(a4);"
    // "sw t1, 0(a5);"
    // "lw a6, 0(a4);"
    // "lw a6, 0(a5);"

    // "nop;"
    // "nop;"
    // "nop;"
    // "nop;"

    // "li s0, 0x50000000;"
    // "jr s0");

    // while (1) ;
}
/*
void handle_trap(void)
{
    // print_uart("trap\r\n");
}
*/
