// @author El Sherif Adel
// @date YYYY-MM-DD
// @title Task Title

#include "UART.h"
#include <LPC214x.h> // Include LPC2148 header file

#define PCLK 60000000 // Peripheral clock in Hz
#define BAUD_RATE 9600
#define DIVISOR PCLK / (16 * BAUD_RATE)

static void UART_sendCharacter(uint8_t ch) {
  while (!(U0LSR & (1 << 5))) {
    // wait untill the THR is empty
  }
  U0THR = ch; // Transmit the character
}

void UART_init(void) {
  PINSEL0 = 0x5; /* Select TxD for P0.0 and RxD for P0.1 */
  U0LCR = 0x83;  /* 8 bits, no Parity, 1 Stop bit | DLAB set to 1 */
  U0DLL = DIVISOR & 0xFF;
  U0DLM = (DIVISOR >> 8) & 0xFF;
  U0LCR = 0x03; // Disable DLAB and set 8-bit character length
}

void UART_receiveLine(uint8_t *buffer, uint16_t bufferSize) {
  uint16_t index = 0;
  uint8_t receivedChar;

  while (index < bufferSize) {
    while ((U0LSR & 0x01) == 0) {
      // Wait until data is available
    }
    receivedChar = U0RBR;             // Read received character
    UART_sendCharacter(receivedChar); // Echo back the character
    if (receivedChar == '\n' || receivedChar == '\r') {
      buffer[index] = '\0';
      break; // Stop on end-of-line characters
    }
    buffer[index++] = receivedChar;
    if (receivedChar == '\b' && index >= 2) { // Backspace
      index -= 2;
    }
  }

  buffer[bufferSize - 1] = '\0'; // Null-terminate the string
}

void UART_sendString(uint8_t *str) {
  uint16_t i;

  for (i = 0; i < str[i] != '\0'; i++) {
    UART_sendCharacter(str[i]);
  }
}

void UART_endLine(void) { UART_sendCharacter('\r'); }
