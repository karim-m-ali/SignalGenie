// @author Ahmed Elwakad

#ifndef KS0108_INTERFACE_H
#define KS0108_INTERFACE_H

#include "../MCAL/GPIO.h"
#include <stdint.h>

typedef struct {
  GPIO_PORT_t control_port;
  GPIO_PORT_t data_port;
  uint8_t DI;
  uint8_t RW;
  uint8_t EN;
  uint8_t C1;
  uint8_t C2;
  uint8_t RST;
  uint8_t DB[8];
} KS0108_config_t;

void KS0108_init(KS0108_config_t *config);
void KS0108_sendCommand(uint8_t cmd, uint8_t chip);
void KS0108_sendData(uint8_t data, uint8_t chip);
void KS0108_clearScreen(void);
void KS0108_setPixel(int x, int y);
void KS0108_clearColumn(uint8_t col);
#endif
