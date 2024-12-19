// @author Your Name
// @date YYYY-MM-DD
// @title Task Title

#include "GLCD.h"

#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>


#include <stdint.h>

#include "MCAL/GPIO.h"
// Function definitions go here

void GLCD_init(void) {
		// GPIO_setPinDirection(..)
		// vTaskDelay(pdMS_TO_TICKS(100)); // delay for 100 ms for example
}

void GLCD_clearColumn(uint8_t column) {}

void GLCD_setPixel(uint8_t row, uint8_t column) {}

