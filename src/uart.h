#ifndef __SERIAL_H__
#define __SERIAL_H__

#include <stdint.h>

//-----------------------------------------------------------------
// Prototypes
//-----------------------------------------------------------------
void init_uart(uint32_t base_addr, uint32_t baud_rate);
int  serial_putchar(char c);
void print_uart(const char *str);

void print_uart_int(uint32_t addr);
void print_uart_addr(uint64_t addr);
void print_uart_byte(uint8_t byte);

#endif