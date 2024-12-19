// @author Your Name
// @date YYYY-MM-DD
// @title Task Title

#include "taskTerminal.h"


#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>

#include <stdint.h>

#define N_ARRAY 1000
#define N_QUEUE 100

extern volatile QueueHandle_t queueSamplesToPlot;

extern volatile uint16_t arraySamplesToGenerate[N_ARRAY];

extern volatile uint16_t ticksDelayAfterGenerate;
extern volatile uint16_t ticksDelayAfterCapture;

// Function definitions go here

void taskTerminal(void *unused) {
	while (1) {
	}
}
