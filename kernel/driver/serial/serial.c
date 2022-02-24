#include "serial.h"
#include <arch/i386/ports.h>
#include <stdbool.h>

// base port addresses for the serial ports
#define SERIAL_COM1_BASE 0x3F8
#define SERIAL_COM2_BASE 0x2F8
#define SERIAL_COM3_BASE 0x3E8
#define SERIAL_COM4_BASE 0x2E8
#define SERIAL_COM5_BASE 0x5F8
#define SERIAL_COM6_BASE 0x4F8
#define SERIAL_COM7_BASE 0x5E8
#define SERIAL_COM8_BASE 0x4E8

// serial ports are calculated relative to their base port
// because all serial outputs have the ports in the same order
//

#define SERIAL_DATA_PORT(base) (base)
#define SERIAL_FIFO_COMMAND_PORT(base) (base + 2)
#define SERIAL_LINE_COMMAND_PORT(base) (base + 3)
#define SERIAL_MODEM_COMMAND_PORT(base) (base + 4)
#define SERIAL_LINE_STATUS_PORT(base) (base + 5)

/* SERIAL_LINE_ENABLE_DLAB:
 * Tells the serial port to expect first the highest 8 bits of the divisor on the data port,
 * then the lowest 8 bits will follow
 * Pretty much just enables writing to the internal divisor register
 */
#define SERIAL_LINE_ENABLE_DLAB 0x80

static bool com1_initialized = false;

/** serial_configure_baud_rate:
 *  Sets the speed of the data being sent. The default speed of a serial
 *  port is 115200 bits/s. The argument is a divisor of that number, hence
 *  the resulting speed becomes (115200 / divisor) bits/s.
 *
 *  @param com      The COM port to configure
 *  @param divisor  The divisor
 */
void serial_configure_baud_rate(unsigned short com, unsigned short divisor)
{
    // enable writing to the divisor register
    outportb(SERIAL_LINE_COMMAND_PORT(com), SERIAL_LINE_ENABLE_DLAB);

    // write the highest 8 bits
    outportb(SERIAL_DATA_PORT(com), (divisor >> 8) & 0x00ff);

    // followed by the lowest
    outportb(SERIAL_DATA_PORT(com), divisor & 0x00ff);
}

/** serial_configure_line:
 *  Configures the line of the given serial port. The port is set to have a
 *  data length of 8 bits, no parity bits, one stop bit and break control
 *  disabled.
 *
 *  @param com  The serial port to configure
 */
void serial_configure_line(unsigned short com)
{
    /* Bit:     | 7 | 6 | 5 4 3 | 2 | 1 0 |
     * Content: | d | b | prty  | s | dl  |
     * Value:   | 0 | 0 | 0 0 0 | 0 | 1 1 | = 0x03
     */
    outportb(SERIAL_LINE_COMMAND_PORT(com), 0x03); // 8 bit length, no parity, 1 stop bit, disable dividor access and no break control
}

/** serial_configure_queue:
 * Configures the FIFO queue for a certain serial port.
 *
 * Port Settings
 * Bit:     | 7 6 | 5  | 4 | 3   | 2   | 1   | 0 |
 * Content: | lvl | bs | r | dma | clt | clr | e |
 * Default: | 1 1 | 0  | 0 | 0   | 1   | 1   | 1 | = 0xC7
 */
void serial_configure_queue(unsigned short com)
{
    outportb(SERIAL_FIFO_COMMAND_PORT(com), 0xC7);
}

/**
 * @brief Sets a default modem value for a given serial port.
 *
 * serial_configure_modem sets a default value for a given serial port.
 *
 * Bit:     | 7 | 6 | 5  | 4  | 3   | 2   | 1   | 0   |
 * Content: | r | r | af | lb | ao2 | ao1 | rts | dtr |
 * Default: | 0 | 0 | 0  | 0  | 0   | 0   | 1   | 1   | = 0x03
 * @param com - The serial port's base port number.
 */
void serial_configure_modem(unsigned short com)
{
    outportb(SERIAL_MODEM_COMMAND_PORT(com), 0x03);
}

/** serial_is_transmit_fifo_empty:
 *  Checks whether the transmit FIFO queue is empty or not for the given COM
 *  port.
 *
 *  @param  com The COM port
 *  @return 0 if the transmit FIFO queue is not empty
 *          1 if the transmit FIFO queue is empty
 */
int serial_is_transmit_fifo_empty(unsigned int com)
{
    /* 0x20 = 0010 0000 */
    return inportb(SERIAL_LINE_STATUS_PORT(com)) & 0x20;
}

void initialize_serial()
{
    serial_configure_baud_rate(SERIAL_COM1_BASE, 3);
    serial_configure_line(SERIAL_COM1_BASE);
    serial_configure_queue(SERIAL_COM1_BASE);
    serial_configure_modem(SERIAL_COM1_BASE);
    com1_initialized = true;
}

// writes a character to the serial port.
void serial_write_char(char c)
{
    if (!com1_initialized)
        initialize_serial();

    if(c == '\n') {
        serial_write_char('\r');
    }

    // wait for the fifo queue to be cleared.
    while(serial_is_transmit_fifo_empty(SERIAL_COM1_BASE) == 0);

    // output character to the serial port
    outportb(SERIAL_DATA_PORT(SERIAL_COM1_BASE), c);
}