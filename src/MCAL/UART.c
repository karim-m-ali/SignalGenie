// @author Your Name
// @date YYYY-MM-DD
// @title Task Title

#include "UART.h"

// Function definitions go here


void UART_init(void) {}

void UART_receiveLine(uint8_t * buffer, uint16_t bufferSize) {
	// read on buffer utill you get '\n' or '\r' or reach bufferSize
	// put '\0' after last useful character (inplace of '\n' or '\r' for example)
}

void UART_sendLine(uint8_t * buffer, uint16_t stringLength) {
	// write from buffer stringLength characters
}
