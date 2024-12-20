// @author Your Name
// @date YYYY-MM-DD
// @title Task Title

#include "UART.h"
#include <LPC214x.h> // Include LPC2148 header file

// Function definitions go here


void UART_init(void)
{
  // Step 1: Enable UART0 and GPIO peripheral
  PINSEL0 |= 0x00000005; // Configure P0.0 as TXD0 and P0.1 as RXD0
	
	/* DLAB = 1, 1 stop bit, 8-bit character length */
  U0LCR = 0x83;          // 8 bits, no parity, 1 stop bit, DLAB=1   
	
	
	U0DLM = 0x00;   /* For baud rate of 9600 with Pclk = 15MHz */
	U0DLL = 0x61;            

	 // Step 3: Configure UART for normal operation
   U0LCR = 0x03; // Disable DLAB (Divisor Latch Access Bit)
	
	 // Step 4: Enable and reset FIFO
   U0FCR = 0x07; // Enable FIFO, reset RX/TX FIFO
}

void UART_receiveLine(uint8_t * buffer, uint16_t bufferSize)
{
	// read on buffer utill you get '\n' or '\r' or reach bufferSize
	// put '\0' after last useful character (inplace of '\n' or '\r' for example)
	
	    uint16_t index = 0; // Initialize index for the buffer

    while (index < (bufferSize - 1)) { // Leave space for the null terminator
        // Wait until data is available in the UART receive buffer
        while (!(U0LSR & 0x01)) {
            // Loop until RDR (Receiver Data Ready) bit is set
        }

        // Read the received character from the UART data register
        uint8_t receivedChar = U0RBR;

        // Check for end-of-line characters
        if (receivedChar == '\n' || receivedChar == '\r') {
            break; // Stop reading if end-of-line is reached
        }

        // Store the character in the buffer
        buffer[index++] = receivedChar;
    }

    // Null-terminate the string
    buffer[index] = '\0';
	
}

void UART_sendLine(uint8_t * buffer, uint16_t stringLength)
{
	// write from buffer stringLength characters
	    for (uint16_t i = 0; i < stringLength; i++) {
        // Wait until the UART transmitter holding register is empty
        while (!(U0LSR & 0x20)) {
            // Loop until the THRE (Transmit Holding Register Empty) bit is set
        }

        // Write the character to the UART transmit holding register
        U0THR = buffer[i];
    }
}
