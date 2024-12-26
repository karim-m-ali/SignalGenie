// @author Karim M. Ali
// @date YYYY-MM-DD
// @title Task Title

#include "taskTerminal.h"

#include "MCAL/UART.h"

#include <FreeRTOS.h>
#include <queue.h>
#include <task.h>

#include <math.h>

#include <stdint.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>


#include "defs.h"

volatile uint16_t sampleDelayTicks = 0;
volatile uint16_t sampleIndex      = 0;
volatile uint16_t samples[N_SAMPLES];

uint8_t buffer[N_BUFFER];
uint16_t i;
uint32_t hz;

double x;

void preprocessCommand(char *str);

void taskTerminal(void *unused) {	
	sampleDelayTicks = 0;

  UART_init();

  while (1) {
    // Prompting user
    UART_sendString((uint8_t *)">> ");
    UART_receiveLine(buffer, N_BUFFER);

    // Preprocessing
    preprocessCommand((char *)buffer);

    if (buffer[0] == '\0') { // Skip if user entered nothing
      continue;
    }

    // Interpreting
    if (strcmp((char *)buffer, "help") == 0) {        // Help
      UART_sendString((uint8_t *)"HELP:");
      UART_endLine();
      UART_sendString((uint8_t *)">> sin(e)");
      UART_endLine();
      UART_sendString((uint8_t *)">> squ(are)");
      UART_endLine();
      UART_sendString((uint8_t *)">> saw(tooth)");
      UART_endLine();
      UART_sendString((uint8_t *)">> tri(angle)");
      UART_endLine();
      UART_sendString((uint8_t *)">> freq [+ve integer in Hz]");
      UART_endLine();
      UART_sendString((uint8_t *)">> stop");
      UART_endLine();

    } else if (strcmp((char *)buffer, "stop") == 0) { // Stop
      sampleDelayTicks = 0;
      UART_sendString((uint8_t *)"OK:  stopped gen");

    } else if (strstr((char *)buffer, "sin") != NULL) { // Sine
      sampleDelayTicks = 0;
      UART_sendString((uint8_t *)"OK:  preparing sine..");
			UART_endLine();
			
			for (i = 0; i < N_SAMPLES; i++) {
				x = (double)i / (double)N_SAMPLES;
				x = 0.5 + 0.5 * sin(2.0 * 3.14159 * x);
				x *= 1023.0;
				samples[i] = 1023 - (uint16_t)x;
			}
			
			sampleDelayTicks = pdMS_TO_TICKS(3);
			UART_sendString((uint8_t *)"OK:  generating..");
			
    } else if (strstr((char *)buffer, "squ") != NULL) { // Square
      sampleDelayTicks = 0;
      UART_sendString((uint8_t *)"OK:  preparing square..");
			UART_endLine();
			
			for (i = 0; i < N_SAMPLES; i++) {
				x = (i <= N_SAMPLES / 2 ? 1023.0 : 0.0 );
				samples[i] = 1023 - (uint16_t)x;
			}
			
			sampleDelayTicks = pdMS_TO_TICKS(3);
			UART_sendString((uint8_t *)"OK:  generating..");
			
    } else if (strstr((char *)buffer, "saw") != NULL) { // Sawtooth
      sampleDelayTicks = 0;
      UART_sendString((uint8_t *)"OK:  preparing sawtooth..");
			UART_endLine();
			
			for (i = 0; i < N_SAMPLES; i++) {
				x = (double)i / (double)(N_SAMPLES - 1);
				x *= 1023.0;
				samples[i] = 1023 - (uint16_t)x;
			}
			
			sampleDelayTicks = pdMS_TO_TICKS(3);
			UART_sendString((uint8_t *)"OK:  generating..");
			
    } else if (strstr((char *)buffer, "tri") != NULL) { // Triangle
      sampleDelayTicks = 0;
      UART_sendString((uint8_t *)"OK:  preparing triangle..");
			UART_endLine();
			
			for (i = 0; i < N_SAMPLES; i++) {
				x = (double)i / (double)(N_SAMPLES - 1);
				if (i < N_SAMPLES / 2) {
			    x *= 2.0;
				} else {
					x = 1.0 - (x - 0.5) * 2.0;
				}
				x *= 1023.0;
				samples[i] = 1023 - (uint16_t)x;
			}
			
			sampleDelayTicks = pdMS_TO_TICKS(3);
			UART_sendString((uint8_t *)"OK:  generating..");
			
    } else if (sscanf((char*)buffer, "freq %u", &hz) == 1) { // Freq
			hz *= N_SAMPLES;
			if (hz < 1) {
				UART_sendString((uint8_t *)"ERR: freq must be >= 1");
			} else {
				hz = pdMS_TO_TICKS(1000.0 / hz);
				if (hz < 1) {
					UART_sendString((uint8_t *)"ERR: freq exceeds limit");
				} else {
					UART_sendString((uint8_t *)"OK:  frequency is set!");
					sampleDelayTicks = hz;
				}
		  }

    } else {                                                 // Error
      UART_sendString((uint8_t *)"ERR: incorrect or incomplete command");
    }

    UART_endLine();
    UART_endLine();
  }
}

void preprocessCommand(char *str) {
  uint16_t i, j, isToken = 0;

  i = 0; // Reading index
  j = 0; // Writing index

  for (; str[i] != '\0'; i++) {
    if (isalpha(str[i]) ||
        isdigit(str[i])) { // Accepting either letters or digits
      str[j++] = tolower(str[i]);
      isToken = 1;
    } else if (isToken) { // Putting a single space after each token
      isToken = 0;
      str[j++] = ' ';
    }
  }
  if (!isToken) { // Removing the trailing space if exists
    j--;
  }
  str[j] = '\0';
}
