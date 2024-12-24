// @author Your Name
// @date YYYY-MM-DD
// @title Task Title

#ifndef UART_H
#define UART_H

// Function declarations or other header content go here

#include <stdint.h>

void UART_init(void);

void UART_receiveLine(uint8_t * buffer, uint16_t bufferSize);

void UART_sendString(uint8_t * str);

#endif // UART_H
