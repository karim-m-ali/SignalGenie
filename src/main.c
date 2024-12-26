// @author Karim M. Ali
// @date YYYY-MM-DD
// @title Task Title

#include <FreeRTOS.h>
#include <queue.h>
#include <task.h>

#include <stdint.h>

#include "AL/taskGenerate.h"
#include "AL/taskPlot.h"
#include "AL/taskTerminal.h"


int main(void) {
  // Create tasks
  xTaskCreate(taskGenerate, "taskGenerate", 300, NULL, tskIDLE_PRIORITY, NULL);
  xTaskCreate(taskPlot,     "taskPlot",     300, NULL, tskIDLE_PRIORITY, NULL);
  xTaskCreate(taskTerminal, "taskTerminal", 1000, NULL, tskIDLE_PRIORITY, NULL);

  // Start the scheduler
  vTaskStartScheduler();
}
