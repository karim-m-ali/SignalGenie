// @author Ahmed Elwakad
// @date YYYY-MM-DD
// @title Task Title

#include "taskPlot.h"
#include "../HAL/KS0108.h"
#include "../MCAL/GPIO.h"

#include <FreeRTOS.h>
#include <queue.h>
#include <task.h>

#include <stdint.h>


#include "defs.h"

extern volatile uint16_t sampleDelayTicks;
extern volatile uint16_t sampleIndex;
extern volatile uint16_t samples[N_SAMPLES];

static uint16_t sampleIndexPrev = 0xFFFF;

// Function definitions go here

void taskPlot(void *param) {
  uint8_t column_counter = 0;

  KS0108_config_t config;
  config.control_port = GPIO_PORT0;
  config.data_port = GPIO_PORT0;
  config.RST = 10;
  config.DB[7] = 11;
  config.DB[6] = 12;
  config.DB[5] = 13;
  config.DB[4] = 14;
  config.DB[3] = 15;
  config.DB[2] = 16;
  config.DB[1] = 17;
  config.DB[0] = 18;
  config.EN = 19;
  config.RW = 20;
  config.DI = 21;
  config.C2 = 22;
  config.C1 = 23;

  KS0108_init(&config);
  KS0108_clearScreen();

  while (1) {
    if (sampleDelayTicks > 0) { // check if we are generating now
			if (sampleIndexPrev == sampleIndex) {
				continue;
			}
			sampleIndexPrev = sampleIndex;

      KS0108_clearColumn(column_counter); // clear the current column
			
			// set the new value for the column
      KS0108_setPixel(column_counter, samples[sampleIndex] * 63 / 1023);

			// the new value for the counter
      column_counter = (column_counter + 1) % 128;
			
    } else {
      vTaskDelay(pdMS_TO_TICKS(500)); // wait if not busy to let other tasks run
    }
  }
}
