#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>

#include <stdint.h>

#include "AL/taskGenerate.h"
#include "AL/taskCapture.h"
#include "AL/taskPlot.h"
#include "AL/taskTerminal.h"

#define N_ARRAY 1000
#define N_QUEUE 100

volatile QueueHandle_t queueSamplesToPlot = NULL;

volatile uint16_t arraySamplesToGenerate[N_ARRAY];

volatile uint16_t ticksDelayAfterGenerate = 0;
volatile uint16_t ticksDelayAfterCapture = 0;

int main(void) {
		// Create queues
		queueSamplesToPlot = xQueueCreate(N_QUEUE, sizeof(uint16_t));
	
    // Create tasks
		xTaskCreate(taskCapture, "taskCapture", 2000, NULL, tskIDLE_PRIORITY + 2, NULL);
		xTaskCreate(taskGenerate, "taskGenerate", 2000, NULL, tskIDLE_PRIORITY + 2, NULL);
	  xTaskCreate(taskPlot, "taskPlot", 2000, NULL, tskIDLE_PRIORITY + 1, NULL);
		xTaskCreate(taskTerminal, "taskTerminal", 2000, NULL, tskIDLE_PRIORITY, NULL);
	
    // Start the FreeRTOS scheduler
    vTaskStartScheduler();
}
