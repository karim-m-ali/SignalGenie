// @author Your Name
// @date YYYY-MM-DD
// @title Task Title

#include "ADC.h"
#include <LPC214x.h> // Include LPC2148 header file

// Function definitions go here


void ADC_init(void) {
	
	// Step 1: Configure Pins for ADC Functionality
  // Example: Configure P0.28 for AD0.1 (ADC Channel 1)
  PINSEL1 |= (1 << 24);  // Set bits 24:25 to "01" for AD0.1
  PINSEL1 &= ~(1 << 25); // Clear bit 25

  // Step 2: Set ADC Control Register
  // Bits 7:0: CLKDIV (ADC clock divider)
  // Bit 8: BURST (0 = Single Conversion Mode)
  // Bit 16: PDN (Power Down Mode, 1 = Enable ADC)
  AD0CR = (1 << 1)    // Select AD0.1 channel
        | (15 << 8)   // ADC clock divider (for PCLK / (CLKDIV + 1))
        | (1 << 21);  // Power up the ADC (PDN = 1)
}

void ADC_read(uint16_t * ptrSample) {
	
	// Start ADC conversion for the selected channel
  AD0CR |= (1 << 24); // Start conversion (START = 001)

  // Wait for the conversion to complete
  while (!(AD0DR1 & (1u << 31))) {
      // Wait until the DONE bit (bit 31) in AD0DR1 is set
  }

  // Retrieve the 10-bit result from the ADC data register
  *ptrSample = (AD0DR1 >> 6) & 0x3FF; // Extract bits 6:15 for ADC result
}

