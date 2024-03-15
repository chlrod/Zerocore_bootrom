#include "uart.h"

//-----------------------------------------------------------------
// Defines
//-----------------------------------------------------------------
#define ULITE_RX          0x0
    #define ULITE_RX_DATA_SHIFT                  0
    #define ULITE_RX_DATA_MASK                   0xff

#define ULITE_TX          0x4
    #define ULITE_TX_DATA_SHIFT                  0
    #define ULITE_TX_DATA_MASK                   0xff

#define ULITE_STATUS      0x8
    #define ULITE_STATUS_IE                      4
    #define ULITE_STATUS_IE_SHIFT                4
    #define ULITE_STATUS_IE_MASK                 0x1

    #define ULITE_STATUS_TXFULL                  3
    #define ULITE_STATUS_TXFULL_SHIFT            3
    #define ULITE_STATUS_TXFULL_MASK             0x1

    #define ULITE_STATUS_TXEMPTY                 2
    #define ULITE_STATUS_TXEMPTY_SHIFT           2
    #define ULITE_STATUS_TXEMPTY_MASK            0x1

    #define ULITE_STATUS_RXFULL                  1
    #define ULITE_STATUS_RXFULL_SHIFT            1
    #define ULITE_STATUS_RXFULL_MASK             0x1

    #define ULITE_STATUS_RXVALID                 0
    #define ULITE_STATUS_RXVALID_SHIFT           0
    #define ULITE_STATUS_RXVALID_MASK            0x1

#define ULITE_CONTROL     0xc
    #define ULITE_CONTROL_IE                     4
    #define ULITE_CONTROL_IE_SHIFT               4
    #define ULITE_CONTROL_IE_MASK                0x1

    #define ULITE_CONTROL_RST_RX                 1
    #define ULITE_CONTROL_RST_RX_SHIFT           1
    #define ULITE_CONTROL_RST_RX_MASK            0x1

    #define ULITE_CONTROL_RST_TX                 0
    #define ULITE_CONTROL_RST_TX_SHIFT           0
    #define ULITE_CONTROL_RST_TX_MASK            0x1

//-----------------------------------------------------------------
// Locals
//-----------------------------------------------------------------
static volatile uint32_t *m_uart;

//-----------------------------------------------------------------
// init_uart: Initialise UART peripheral
//-----------------------------------------------------------------
void init_uart(uint32_t base_addr, uint32_t baud_rate)           
{
    uint32_t cfg = 0;
    m_uart = (volatile uint32_t *)base_addr;

    // Soft reset
    cfg += (1 << ULITE_CONTROL_RST_RX_SHIFT);
    cfg += (1 << ULITE_CONTROL_RST_TX_SHIFT);

    m_uart[ULITE_CONTROL/4]  = cfg;
}
//-----------------------------------------------------------------
// serial_putchar: Polled putchar
//-----------------------------------------------------------------
int serial_putchar(char c)
{
    // While TX FIFO full
    while (m_uart[ULITE_STATUS/4] & (1 << ULITE_STATUS_TXFULL_SHIFT))
        ;

    m_uart[ULITE_TX/4] = c;

    return 0;
}
//-------------------------------------------------------------
// print_uart: Print string (NULL terminated)
//-------------------------------------------------------------
void print_uart(const char *str)
{
    while (*str)
        serial_putchar(*str++);
}

uint8_t bin_to_hex_table[16] = {
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

void bin_to_hex(uint8_t inp, uint8_t res[2])
{
    res[1] = bin_to_hex_table[inp & 0xf];
    res[0] = bin_to_hex_table[(inp >> 4) & 0xf];
    return;
}

void print_uart_int(uint32_t addr)
{
    int i;
    for (i = 3; i > -1; i--)
    {
        uint8_t cur = (addr >> (i * 8)) & 0xff;
        uint8_t hex[2];
        bin_to_hex(cur, hex);
        serial_putchar(hex[0]);
        serial_putchar(hex[1]);
    }
}

void print_uart_addr(uint64_t addr)
{
    int i;
    for (i = 7; i > -1; i--)
    {
        uint8_t cur = (addr >> (i * 8)) & 0xff;
        uint8_t hex[2];
        bin_to_hex(cur, hex);
        serial_putchar(hex[0]);
        serial_putchar(hex[1]);
    }
}

void print_uart_byte(uint8_t byte)
{
    uint8_t hex[2];
    bin_to_hex(byte, hex);
    serial_putchar(hex[0]);
    serial_putchar(hex[1]);
}