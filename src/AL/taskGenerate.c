// @author Mahmoud Gamal
// @date YYYY-MM-DD
// @title Task Title

#include "taskGenerate.h"
#include "../MCAL/DAC.h"
#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>
#include <stdint.h>

#define N_ARRAY 1000
#define N_QUEUE 100
#define SAMPLE_INCREMENT 10

extern volatile QueueHandle_t queueSamplesToPlot;

extern volatile uint16_t arraySamplesToGenerate[N_ARRAY];

extern volatile uint16_t ticksDelayAfterGenerate;
extern volatile uint16_t ticksDelayAfterCapture;

void taskGenerate(void *unused) {
		 uint16_t currentSample = 0;

     DAC_init();
	
	while (1) {
        // Generate a sample
        currentSample = (currentSample + SAMPLE_INCREMENT) % 1024; // Keep values within 10-bit range
        
        // Output the sample to the DAC
        DAC_write(currentSample);
        
        // Optionally send the sample to the plot queue
        if (queueSamplesToPlot != NULL) {
            xQueueSend(queueSamplesToPlot, &currentSample, portMAX_DELAY);
        }

        // Delay between samples based on the configured ticks
        if (ticksDelayAfterGenerate > 0) {
            vTaskDelay(ticksDelayAfterGenerate);
        }
	}
}


