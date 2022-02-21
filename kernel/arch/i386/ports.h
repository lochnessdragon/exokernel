#pragma once
// C Definitions for port.asm
// Methods for taking data from and pushing data to a port. Defined in ports.asm
unsigned char inportb (unsigned short id);
/** outportb:
*  Sends the given data to the given I/O port. Defined in io.s
*
*  @param port The I/O port to send the data to
*  @param data The data to send to the I/O port
*/
void outportb (unsigned short id, unsigned char value);
