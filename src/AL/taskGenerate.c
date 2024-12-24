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


extern volatile uint16_t arraySamplesToGenerate[N_ARRAY];

extern volatile uint16_t ticksDelayAfterGenerate;

uint16_t sample = 0, sampleIndex = 0;

void taskGenerate(void *unused) {

  DAC_init();
	
	while (1) {
        // Delay between samples based on the configured ticks
        if (ticksDelayAfterGenerate > 0) {
					  sampleIndex = (sampleIndex + 1) % N_ARRAY;
		
						sample = arraySamplesToGenerate[sampleIndex];
					
					  // Output the sample to the DAC
					  DAC_write(sample);
					
            vTaskDelay(ticksDelayAfterGenerate);
        } else {
					vTaskDelay(pdMS_TO_TICKS(500));  // wait if not busy to let other tasks run
				}
	}
}


