// @author Ahmed Elwakad
// @date YYYY-MM-DD
// @title Task Title

#include "taskPlot.h"
#include "../HAL/KS0108.h"


#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>

#include <stdint.h>


extern volatile QueueHandle_t queueSamplesToPlot;


// Function definitions go here

void taskPlot(void *param) {
	uint16_t value_buffer;
	static uint8_t column_counter=0;
	KS0108_init((KS0108_config_t*)param);
	KS0108_clearScreen();
	
	while (1) {
		vTaskDelay(pdMS_TO_TICKS(2)); 
		if(xQueueReceive(queueSamplesToPlot,&value_buffer,portMAX_DELAY)==pdPASS){ //check if there is a value in the queue
       		KS0108_clearColumn(column_counter);  //clear the current column 
		     	KS0108_setPixel(column_counter,(value_buffer/64)+32); //set the new value for the column
			
			    column_counter= (column_counter + 1) % 128 ; //the new value for the counter

			
		}
        
	}
}
