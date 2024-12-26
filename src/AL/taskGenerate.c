// @author Mahmoud Gamal
// @date YYYY-MM-DD
// @title Task Title

#include "taskGenerate.h"
#include "../MCAL/DAC.h"
#include <FreeRTOS.h>
#include <queue.h>
#include <stdint.h>
#include <task.h>


#include "defs.h"

extern volatile uint16_t sampleDelayTicks;
extern volatile uint16_t sampleIndex;
extern volatile uint16_t samples[N_SAMPLES];

void taskGenerate(void *unused) {
  DAC_init();

  while (1) {
    // Delay between samples based on the configured ticks
    if (sampleDelayTicks > 0) {

      // Output the sample to the DAC
      DAC_write(samples[sampleIndex]);
			
			// Move to next sample
			sampleIndex = (sampleIndex + 1) % N_SAMPLES;

      vTaskDelay(sampleDelayTicks);
			
    } else {
      vTaskDelay(pdMS_TO_TICKS(500)); // wait if not busy to let other tasks run
			
    }
  }
}
