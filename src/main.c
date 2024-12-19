#include <FreeRTOS.h>
#include <task.h>

// Helper macro to set up pins for toggling
#define SET_PIN_DIRECTION(pin)    (IO0DIR |= (1 << pin))
#define CLEAR_PIN(pin)            (IO0CLR |= (1 << pin))
#define TOGGLE_PIN(pin)           (IO0PIN ^= (1 << pin))

// Task to toggle pin P0.3 every 100 milliseconds
void toggleP0_3Task(void *unused) {
    SET_PIN_DIRECTION(3);    // Set P0.3 as output
    CLEAR_PIN(3);            // Ensure P0.3 starts in a low state
    
    while (1) {
        TOGGLE_PIN(3);       // Toggle P0.3
        vTaskDelay(pdMS_TO_TICKS(100)); // Delay 100ms
    }
}

// Task to toggle pin P0.5 every 200 milliseconds
void toggleP0_5Task(void *unused) {
    SET_PIN_DIRECTION(5);    // Set P0.5 as output
    CLEAR_PIN(5);            // Ensure P0.5 starts in a low state
    
    while (1) {
        TOGGLE_PIN(5);       // Toggle P0.5
        vTaskDelay(pdMS_TO_TICKS(200)); // Delay 200ms
    }
}

int main(void) {
    // Create tasks
    xTaskCreate(toggleP0_3Task, "ToggleP0_3", 300, NULL, tskIDLE_PRIORITY, NULL);
    xTaskCreate(toggleP0_5Task, "ToggleP0_5", 300, NULL, tskIDLE_PRIORITY, NULL);

    // Start the FreeRTOS scheduler
    vTaskStartScheduler();
}
