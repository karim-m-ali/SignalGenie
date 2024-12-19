// @author Your Name
// @date YYYY-MM-DD
// @title Task Title

#ifndef GLCD_H
#define GLCD_H

#include <stdint.h>

// Function declarations or other header content go here

void GLCD_init(void);

void GLCD_clearColumn(uint8_t column);

void GLCD_setPixel(uint8_t row, uint8_t column);

#endif // GLCD_H
