// @author Your Name
// @date YYYY-MM-DD
// @title Task Title

#ifndef GPIO_H
#define GPIO_H

// Function declarations or other header content go here

#include <stdint.h>

void GPIO_setPinDirection(uint8_t port, uint8_t pin, uint8_t isOutput);

void GPIO_setPinLevel(uint8_t port, uint8_t pin, uint8_t isHigh);

#endif // GPIO_H
