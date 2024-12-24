// @author Karim M. Ali
// @date YYYY-MM-DD
// @title Task Title

#include "taskTerminal.h"

#include "MCAL/UART.h"

#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>

#include <stdint.h>

#define N_ARRAY 1000
#define N_QUEUE 100

#define N_BUFFER 100


extern volatile QueueHandle_t queueSamplesToPlot;

extern volatile uint16_t arraySamplesToGenerate[N_ARRAY];

extern volatile uint16_t ticksDelayAfterGenerate;
extern volatile uint16_t ticksDelayAfterCapture;

// Function definitions go here

uint8_t buffer[N_BUFFER]="ABCDEFGHIJKLMNOPQRSTUVWXYZ             ";

void taskTerminal(void *unused) {
	ticksDelayAfterGenerate = 0;
	ticksDelayAfterCapture = 0;
	
	
	UART_init();
	//buffer[0]=0x61;
	buffer[0]=0xaa;
		buffer[0]='A';

	//buffer[1]=0x8c;//'A' 0x61  0011 0001 --> 1000 1100
	while (1) {
		UART_sendString("\n\rEnter: ");
		UART_receiveLine(buffer, N_BUFFER);
		UART_sendString(buffer);
		vTaskDelay(pdMS_TO_TICKS(100));
	}
}
