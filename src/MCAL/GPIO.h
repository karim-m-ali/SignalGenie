// @author Ahmed Elwakad
// @date YYYY-MM-DD
// @title Task Title

#ifndef GPIO_H
#define GPIO_H

// Function declarations or other header content go here

#include <stdint.h>

typedef enum{
	GPIO_PORT0,
  GPIO_PORT1	
}GPIO_PORT_t;

typedef enum{
	GPIO_INPUT,
  GPIO_OUTPUT	
}GPIO_t;

typedef enum{
	GPIO_LOW,
  GPIO_HIGH
}GPIO_OUTPUT_t;


void GPIO_setPinDirection(GPIO_PORT_t port, uint8_t pin, GPIO_t isOutput);

void GPIO_setPinLevel(GPIO_PORT_t port, uint8_t pin, GPIO_OUTPUT_t isHigh);

#endif // GPIO_H
