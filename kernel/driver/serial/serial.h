#ifndef _SERIAL_H
#define _SERIAL_H

void initialize_serial();
void serial_write_char(char c);

// serial config functions
void serial_configure_baud_rate(unsigned short com, unsigned short divisor);
// configures the serial line with the default configuration
void serial_configure_line(unsigned short com);
// configures the queue for the serial line
void serial_configure_queue(unsigned short com);
// configures the modem settings for a serial port
void serial_configure_modem(unsigned short com);

#endif // _SERIAL_H