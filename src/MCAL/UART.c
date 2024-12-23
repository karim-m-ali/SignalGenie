#include "UART.h"
#include <LPC214x.h> // Include LPC2148 header file



void UART_init(void)
{
	PINSEL0 = 0x5;  /* Select TxD for P0.0 and RxD for P0.1 */
	U0LCR = 0x83; /* 8 bits, no Parity, 1 Stop bit | DLAB set to 1 */
	U0DLL = 110;
	U0DLM = 1;   
	U0FDR = 0xF1; /* MULVAL=15(bits - 7:4) , DIVADDVAL=0(bits - 3:0)*/
	U0LCR &= 0x0F; // Set DLAB=0 to lock MULVAL and DIVADDVAL
	//BaudRate is now ~9600 and we are ready for UART communication! 
}


void UART_receiveLine(uint8_t *buffer, uint16_t bufferSize)
{
    uint16_t index = 0;
    uint8_t receivedChar;

    while (index < (bufferSize - 1))
			{
        while( (U0LSR & 0x01) == 0) {} // Wait until data is available
        receivedChar = U0RBR;       // Read received character

        if (receivedChar == '\n' || receivedChar == '\r')
					{
            break; // Stop on end-of-line characters
					}
        buffer[index++] = receivedChar;
     }

    buffer[index] = '\0'; // Null-terminate the string
		
}


void UART_sendLine(uint8_t *buffer, uint16_t stringLength)
{
    uint16_t i;

    for (i = 0; i < stringLength; i++)
	{
		while( ( ((U0LSR & 0x20) == 0) && (U0LSR & 0x40) == 0) )  {} // Wait until the THRE flag is set
		while (!(U0LSR & (1<<5))); // wait till the THR is empty
		U0THR = buffer[i];         // Transmit the character
   }
}

 
