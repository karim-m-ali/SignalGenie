// @author Ahmed Elwakad


#include "../MCAL/GPIO.h"
#include "KS0108_interface.h"

#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>

#include <stdint.h>


#define GET_BIT(VAR,BIT)  ((VAR >> BIT) & 1)

static KS0108_config_t* glcd_config = NULL;


//function to set the databus with a value
static void KS0108_setDB(uint8_t data){
	uint8_t i;
	for(i=0;i<8;i++){
		GPIO_setPinLevel(glcd_config->data_port,glcd_config->DB[i],(GPIO_OUTPUT_t)GET_BIT(data,i));
	}
}


void KS0108_sendCommand(uint8_t cmd, uint8_t chip) {
   GPIO_setPinLevel(glcd_config->control_port, glcd_config->DI,GPIO_LOW); // Command mode
   GPIO_setPinLevel(glcd_config->control_port, glcd_config->RW,GPIO_LOW); // Write mode

    if (chip == 1) {
        GPIO_setPinLevel(glcd_config->control_port, glcd_config->C1,GPIO_HIGH);
        GPIO_setPinLevel(glcd_config->control_port, glcd_config->C2,GPIO_LOW);
    } else if (chip == 2) {
        GPIO_setPinLevel(glcd_config->control_port, glcd_config->C1,GPIO_LOW);
        GPIO_setPinLevel(glcd_config->control_port, glcd_config->C2,GPIO_HIGH);
    }

    KS0108_setDB(cmd);       // Put command on data bus
    GPIO_setPinLevel(glcd_config->control_port, glcd_config->EN,GPIO_HIGH);    // Pulse enable
    vTaskDelay(1);
    GPIO_setPinLevel(glcd_config->control_port, glcd_config->EN,GPIO_LOW);
		vTaskDelay(1);
}

// Function to send data to the KS0108
void KS0108_sendData(uint8_t data, uint8_t chip) {
   GPIO_setPinLevel(glcd_config->control_port, glcd_config->DI,GPIO_HIGH); // data mode
   GPIO_setPinLevel(glcd_config->control_port, glcd_config->RW,GPIO_LOW); // Write mode

    if (chip == 1) {
        GPIO_setPinLevel(glcd_config->control_port, glcd_config->C1,GPIO_HIGH);
        GPIO_setPinLevel(glcd_config->control_port, glcd_config->C2,GPIO_LOW);
    } else if (chip == 2) {
        GPIO_setPinLevel(glcd_config->control_port, glcd_config->C1,GPIO_LOW);
        GPIO_setPinLevel(glcd_config->control_port, glcd_config->C2,GPIO_HIGH);
    }

    KS0108_setDB(data);       // Put data on data bus
    GPIO_setPinLevel(glcd_config->control_port, glcd_config->EN,GPIO_HIGH);    // Pulse enable
    vTaskDelay(1);
    GPIO_setPinLevel(glcd_config->control_port, glcd_config->EN,GPIO_LOW);
		vTaskDelay(1);
}



// Function to initialize the KS0108
void KS0108_init(KS0108_config_t* config) {
     uint8_t i; 
	
	  glcd_config = config;
	  //configure the control directions
	  GPIO_setPinDirection(glcd_config->control_port,glcd_config->C1,GPIO_OUTPUT);
    GPIO_setPinDirection(glcd_config->control_port,glcd_config->C2,GPIO_OUTPUT);
    GPIO_setPinDirection(glcd_config->control_port,glcd_config->EN,GPIO_OUTPUT);
    GPIO_setPinDirection(glcd_config->control_port,glcd_config->RST,GPIO_OUTPUT);
    GPIO_setPinDirection(glcd_config->control_port,glcd_config->RW,GPIO_OUTPUT);
	  GPIO_setPinDirection(glcd_config->control_port,glcd_config->DI,GPIO_OUTPUT);
	  
	  //configure the data bus directions
	  for(i=0;i<8;i++){
			GPIO_setPinDirection(glcd_config->data_port,glcd_config->DB[i],GPIO_OUTPUT);
		}

    // Reset the LCD
   //initalizing the screen
		GPIO_setPinLevel(glcd_config->control_port , glcd_config->RST,GPIO_LOW);    // Reset LCD
    vTaskDelay(pdMS_TO_TICKS(10));
    GPIO_setPinLevel(glcd_config->control_port , glcd_config->RST,GPIO_HIGH);     // Release reset
    

    // Turn off both halves of the display
    KS0108_sendCommand(0x3E, 1);
    KS0108_sendCommand(0x3E, 2);

    // Turn on both halves of the display
    KS0108_sendCommand(0x3F, 1);
    KS0108_sendCommand(0x3F, 2);
}

// Function to clear the screen 
void KS0108_clearScreen(void) {
	uint8_t page ;
	uint8_t col;
    for ( page = 0; page < 8; page++) {
        KS0108_sendCommand((uint8_t)(0xB8 + page), 1); // Set page address (left half)
        KS0108_sendCommand((uint8_t)(0xB8 + page), 2); // Set page address (right half)
        KS0108_sendCommand(0x40, 1);        // Set column address to 0 (left half)
        KS0108_sendCommand(0x40, 2);        // Set column address to 0 (right half)

        for (col = 0; col < 64; col++) {
            KS0108_sendData(0x00, 1); // Fill left half with pattern
            KS0108_sendData(0x00, 2); // Fill right half with pattern
        }
    }
}

void KS0108_setPixel(int x, int y) {
    int chip = (x < 64) ? 1 : 2;
	  int page = y / 8;
	  uint8_t bit_pos = 1 << (y % 8);
    x = (x < 64) ? x : x - 64;
    
    KS0108_sendCommand(0xB8 + page, chip);  // Set page
    KS0108_sendCommand(0x40 + x, chip);    // Set column
    KS0108_sendData(bit_pos, chip);        // Write pixel
}



// Function to clear a column on the screen
void  KS0108_clearColumn(uint8_t col) {
	  uint8_t chip = (col < 64) ? 1 : 2; // Determine which chip to use
    uint8_t chip_x = col % 64;         // Calculate column within the chip
	  uint8_t page;

    if (col >= 128) return; // Out of bounds check

    for ( page = 0; page < 8; page++) {
         KS0108_sendCommand(0xB8 + page, chip);  // Set page address
         KS0108_sendCommand(0x40 + chip_x, chip); // Set column address
         KS0108_sendData(0x00, chip);            // Write 0x00 to clear the column
    }
}


