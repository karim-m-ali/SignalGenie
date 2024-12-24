// @author Your Name
// @date YYYY-MM-DD
// @title Task Title

#include "taskCapture.h"
#include "../MCAL/ADC.h"

#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>

#include <stdint.h>

#define N_ARRAY 1000
#define N_QUEUE 100

extern volatile QueueHandle_t queueSamplesToPlot;

extern volatile uint16_t ticksDelayAfterCapture;

// Function definitions go here


void taskCapture(void *unused)
{
	uint16_t sample = 0;
	
	while (1)
		{
			if(ticksDelayAfterCapture > 0)
			{
				ADC_read(&sample);
        if (xQueueSend(queueSamplesToPlot, &sample, portMAX_DELAY) == pdPASS) {
					// Data was successfully sent to the queue
					}
				vTaskDelay(ticksDelayAfterCapture);
			} 
			else
			{
				vTaskDelay(pdMS_TO_TICKS(500)); // wait if not busy to let other tasks run
			}
		}
}
