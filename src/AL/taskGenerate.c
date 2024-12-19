// @author Your Name
// @date YYYY-MM-DD
// @title Task Title

#include "taskGenerate.h"



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

void taskGenerate(void *unused) {
	while (1) {
				// vTaskDelay(pdMS_TO_TICKS(100)); // delay for 100 ms for example

	}
}

// Function definitions go here
