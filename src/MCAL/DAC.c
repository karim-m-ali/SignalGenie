// @author Mahmoud Gamal
// @date YYYY-MM-DD
// @title Task Title

#include "DAC.h"
#include <lpc213x.h>

void DAC_init(void) {
  // Set bits 18:19 to 10 for AOUT (DAC)
  PINSEL1 |= (1 << 18);
  // Clear bit 19
  PINSEL1 &= ~(1 << 19);
}

void DAC_write(uint16_t sample) { DACR = (sample & 0x3FF) << 6; }
